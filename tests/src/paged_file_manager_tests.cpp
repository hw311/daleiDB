#include <string>
#include <cstdio>
#include <fstream>

#include "catch.hpp"
#include "paged_file_manager.hpp"
#include "file_manager_exception.hpp"

TEST_CASE("PagedFileManager is a singleton", "[PagedFileManager]") {
  using daleiDB::file_manager::PagedFileManager;

  PagedFileManager& paged_file_manager_1 = PagedFileManager::Instance();
  PagedFileManager& paged_file_manager_2 = PagedFileManager::Instance();

  CAPTURE(&paged_file_manager_1, &paged_file_manager_2);

  REQUIRE(&paged_file_manager_1 == &paged_file_manager_2);
}

TEST_CASE("Files can be created and destroyed properly",
          "[file][PagedFileManager]") {
  using daleiDB::file_manager::PagedFileManager;

  const std::string file_name = "test_file.tmp";
  PagedFileManager& paged_file_manager = PagedFileManager::Instance();

  SECTION("Creating an non-existent file should succeed") {
    remove(file_name.c_str());

    REQUIRE_NOTHROW(paged_file_manager.CreateFile(file_name));
    REQUIRE(std::ifstream(file_name));

    remove(file_name.c_str());
  }

  SECTION("Creating an existing file should fail") {
    using daleiDB::file_manager::exception::FileAlreadyExists;

    remove(file_name.c_str());
    std::fstream file(file_name, std::fstream::out);
    CHECK(file.good());

    REQUIRE_THROWS_AS(paged_file_manager.CreateFile(file_name),
                      FileAlreadyExists);

    remove(file_name.c_str());
  }

  SECTION("Destroying an existing file should succeed") {
    remove(file_name.c_str());
    std::fstream file(file_name, std::fstream::out);
    CHECK(file.good());
    
    // Close file before destroy, required by Windows
    CHECK_NOTHROW(file.close());

    REQUIRE_NOTHROW(paged_file_manager.DestroyFile(file_name));
    REQUIRE_FALSE(std::ifstream(file_name));
  }

  SECTION("Destroying an non-existent file should fail") {
    using daleiDB::file_manager::exception::FileNotFound;

    remove(file_name.c_str());

    REQUIRE_THROWS_AS(paged_file_manager.DestroyFile(file_name), FileNotFound);
  }
}

TEST_CASE("Files can be opened and closed properly by PagedFileManager",
          "[file][PagedFileManager]") {
  using daleiDB::file_manager::PagedFileManager;
  using daleiDB::file_manager::FileHandle;

  std::string file_name = "test_file.tmp";
  PagedFileManager& paged_file_manager = PagedFileManager::Instance();
  FileHandle file_handle;

  SECTION("Openning an existing file should succeed") {
    remove(file_name.c_str());
    CHECK_NOTHROW(paged_file_manager.CreateFile(file_name));
    CHECK(std::ifstream(file_name));

    REQUIRE_NOTHROW(paged_file_manager.OpenFile(file_name, &file_handle));

    remove(file_name.c_str());
  }

  SECTION("Openning an non-existent file should fail") {
    using daleiDB::file_manager::exception::FileNotFound;

    remove(file_name.c_str());

    REQUIRE_THROWS_AS(paged_file_manager.OpenFile(file_name, &file_handle),
                      FileNotFound);
  }

  SECTION("Openning a file with a file handle in use should fail") {
    using daleiDB::file_manager::exception::FileHandleInUse;

    remove(file_name.c_str());
    CHECK_NOTHROW(paged_file_manager.CreateFile(file_name));
    CHECK(std::ifstream(file_name));
    CHECK_NOTHROW(paged_file_manager.OpenFile(file_name, &file_handle));
    CHECK(file_handle.Opened());

    REQUIRE_THROWS_AS(paged_file_manager.OpenFile(file_name, &file_handle),
                      FileHandleInUse);

    remove(file_name.c_str());
  }

  SECTION("Closing a file handle should succeed") {
    remove(file_name.c_str());
    CHECK_NOTHROW(paged_file_manager.CreateFile(file_name));
    CHECK(std::ifstream(file_name));
    CHECK_NOTHROW(paged_file_manager.OpenFile(file_name, &file_handle));
    CHECK(file_handle.Opened());

    REQUIRE_NOTHROW(paged_file_manager.CloseFile(&file_handle));

    remove(file_name.c_str());
  }
}
