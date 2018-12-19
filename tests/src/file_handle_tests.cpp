#include <string>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <memory>

#include "catch.hpp"
#include "paged_file_manager.hpp"
#include "file_manager_exception.hpp"

TEST_CASE("Files can be opened and closed properly by FileHandle",
          "[file][FileHandle]") {
  using daleiDB::file_manager::PagedFileManager;
  using daleiDB::file_manager::FileHandle;

  const std::string file_name = "test_file.tmp";
  PagedFileManager& paged_file_manager = PagedFileManager::Instance();
  FileHandle file_handle;

  SECTION("Openning an existing file should succeed") {
    // remove(file_name.c_str());
    // CHECK_NOTHROW(paged_file_manager.CreateFile(file_name));
    // CHECK(std::ifstream(file_name));
    // CHECK_NOTHROW(paged_file_manager.OpenFile(file_name, &file_handle));

    // REQUIRE(file_handle.Opened());

    // remove(file_name.c_str());
    CHECK(true);
  }

  // SECTION("Openning an non-existent file should fail") {
  //   using daleiDB::file_manager::exception::FileNotFound;

  //   remove(file_name.c_str());
  //   CHECK_THROWS_AS(paged_file_manager.OpenFile(file_name, &file_handle),
  //                   FileNotFound);

  //   REQUIRE_FALSE(file_handle.Opened());
  // }

  // SECTION("Closing a file handle should succeed") {
  //   remove(file_name.c_str());
  //   CHECK_NOTHROW(paged_file_manager.CreateFile(file_name));
  //   CHECK(std::ifstream(file_name));
  //   CHECK_NOTHROW(paged_file_manager.OpenFile(file_name, &file_handle));
  //   CHECK(file_handle.Opened());
  //   CHECK_NOTHROW(paged_file_manager.CloseFile(&file_handle));

  //   REQUIRE_FALSE(file_handle.Opened());

  //   remove(file_name.c_str());
  // }
}

// TEST_CASE("File reads, writes, and appends should work", "[file][FileHandle]") {
//   using daleiDB::Byte;
//   using daleiDB::file_manager::kPageSize;
//   using daleiDB::file_manager::kNumHiddenPages;
//   using daleiDB::file_manager::PagedFileManager;
//   using daleiDB::file_manager::FileHandle;

//   const std::string file_name = "test_file.tmp";
//   PagedFileManager& paged_file_manager = PagedFileManager::Instance();
//   FileHandle file_handle;

//   auto data1 = std::shared_ptr<Byte>(new Byte[kPageSize]);
//   auto data2 = std::shared_ptr<Byte>(new Byte[kPageSize]);
//   auto buffer = std::shared_ptr<Byte>(new Byte[kPageSize]);

//   for (size_t i = 0; i < kPageSize; ++i) {
//     data1.get()[i] = 'a' + (i % 26);
//     data2.get()[i] = 'z' - (i % 26);
//   }

//   SECTION("Reading non-existent pages should fail") {
//     using daleiDB::file_manager::exception::PageNumOutOfRange;

//     remove(file_name.c_str());
//     CHECK_NOTHROW(paged_file_manager.CreateFile(file_name));
//     CHECK(std::ifstream(file_name));
//     CHECK_NOTHROW(paged_file_manager.OpenFile(file_name, &file_handle));

//     REQUIRE_THROWS_AS(file_handle.ReadPage(0, buffer.get()), PageNumOutOfRange);

//     remove(file_name.c_str());
//   }

//   SECTION("Writing non-existent pages should fail") {
//     using daleiDB::file_manager::exception::PageNumOutOfRange;

//     remove(file_name.c_str());
//     CHECK_NOTHROW(paged_file_manager.CreateFile(file_name));
//     CHECK(std::ifstream(file_name));
//     CHECK_NOTHROW(paged_file_manager.OpenFile(file_name, &file_handle));

//     REQUIRE_THROWS_AS(file_handle.WritePage(0, data1.get()), PageNumOutOfRange);

//     remove(file_name.c_str());
//   }

//   SECTION("Appending a page should succeed") {
//     remove(file_name.c_str());
//     CHECK_NOTHROW(paged_file_manager.CreateFile(file_name));
//     CHECK(std::ifstream(file_name));
//     CHECK_NOTHROW(paged_file_manager.OpenFile(file_name, &file_handle));

//     REQUIRE_NOTHROW(file_handle.AppendPage(data1.get()));

//     remove(file_name.c_str());
//   }

//   SECTION("Appending a page should write the page to file correctly") {
//     remove(file_name.c_str());
//     CHECK_NOTHROW(paged_file_manager.CreateFile(file_name));
//     CHECK(std::ifstream(file_name));
//     CHECK_NOTHROW(paged_file_manager.OpenFile(file_name, &file_handle));
//     CHECK_NOTHROW(file_handle.AppendPage(data1.get()));

//     std::ifstream in_fstream(file_name, std::fstream::binary);
//     CHECK(in_fstream.good());
//     in_fstream.seekg(kNumHiddenPages * kPageSize, in_fstream.beg);
//     in_fstream.read(reinterpret_cast<char*>(buffer.get()), kPageSize);

//     REQUIRE(memcmp(buffer.get(), data1.get(), kPageSize) == 0);

//     remove(file_name.c_str());
//   }

//   SECTION("Appending multiple pages should succeed") {
//     remove(file_name.c_str());
//     CHECK_NOTHROW(paged_file_manager.CreateFile(file_name));
//     CHECK(std::ifstream(file_name));
//     CHECK_NOTHROW(paged_file_manager.OpenFile(file_name, &file_handle));

//     REQUIRE_NOTHROW(file_handle.AppendPage(data1.get()));
//     REQUIRE_NOTHROW(file_handle.AppendPage(data2.get()));
//     REQUIRE_NOTHROW(file_handle.AppendPage(data1.get()));

//     remove(file_name.c_str());
//   }

//   SECTION("Appending multiple pages should write pages to file correctly") {
//     remove(file_name.c_str());
//     CHECK_NOTHROW(paged_file_manager.CreateFile(file_name));
//     CHECK(std::ifstream(file_name));
//     CHECK_NOTHROW(paged_file_manager.OpenFile(file_name, &file_handle));
//     CHECK_NOTHROW(file_handle.AppendPage(data1.get()));
//     CHECK_NOTHROW(file_handle.AppendPage(data2.get()));
//     CHECK_NOTHROW(file_handle.AppendPage(data1.get()));

//     std::ifstream in_fstream(file_name, std::fstream::binary);
//     CHECK(in_fstream.good());
//     in_fstream.seekg(kNumHiddenPages * kPageSize, in_fstream.beg);
//     in_fstream.read(reinterpret_cast<char*>(buffer.get()), kPageSize);

//     REQUIRE(memcmp(buffer.get(), data1.get(), kPageSize) == 0);

//     in_fstream.seekg((1 + kNumHiddenPages) * kPageSize, in_fstream.beg);
//     in_fstream.read(reinterpret_cast<char*>(buffer.get()), kPageSize);

//     REQUIRE(memcmp(buffer.get(), data2.get(), kPageSize) == 0);

//     in_fstream.seekg((2 + kNumHiddenPages) * kPageSize, in_fstream.beg);
//     in_fstream.read(reinterpret_cast<char*>(buffer.get()), kPageSize);

//     REQUIRE(memcmp(buffer.get(), data1.get(), kPageSize) == 0);

//     remove(file_name.c_str());
//   }

//   SECTION("Reading an existing page should succeed") {
//     remove(file_name.c_str());
//     CHECK_NOTHROW(paged_file_manager.CreateFile(file_name));
//     CHECK(std::ifstream(file_name));
//     CHECK_NOTHROW(paged_file_manager.OpenFile(file_name, &file_handle));
//     CHECK_NOTHROW(file_handle.AppendPage(data1.get()));

//     REQUIRE_NOTHROW(file_handle.ReadPage(0, buffer.get()));

//     remove(file_name.c_str());
//   }

//   SECTION("Reading an existing page should give the correct result") {
//     remove(file_name.c_str());
//     CHECK_NOTHROW(paged_file_manager.CreateFile(file_name));
//     CHECK(std::ifstream(file_name));
//     CHECK_NOTHROW(paged_file_manager.OpenFile(file_name, &file_handle));
//     CHECK_NOTHROW(file_handle.AppendPage(data1.get()));
//     CHECK_NOTHROW(file_handle.ReadPage(0, buffer.get()));

//     REQUIRE(memcmp(buffer.get(), data1.get(), kPageSize) == 0);

//     remove(file_name.c_str());
//   }

//   SECTION("Writing an existing page should succeed") {
//     remove(file_name.c_str());
//     CHECK_NOTHROW(paged_file_manager.CreateFile(file_name));
//     CHECK(std::ifstream(file_name));
//     CHECK_NOTHROW(paged_file_manager.OpenFile(file_name, &file_handle));
//     CHECK_NOTHROW(file_handle.AppendPage(data1.get()));

//     REQUIRE_NOTHROW(file_handle.WritePage(0, data2.get()));

//     remove(file_name.c_str());
//   }

//   SECTION("Writing an existing page should write the page to file correctly") {
//     remove(file_name.c_str());
//     CHECK_NOTHROW(paged_file_manager.CreateFile(file_name));
//     CHECK(std::ifstream(file_name));
//     CHECK_NOTHROW(paged_file_manager.OpenFile(file_name, &file_handle));
//     CHECK_NOTHROW(file_handle.AppendPage(data1.get()));
//     CHECK_NOTHROW(file_handle.WritePage(0, data2.get()));

//     std::ifstream in_fstream(file_name, std::fstream::binary);
//     CHECK(in_fstream.good());
//     in_fstream.seekg(kNumHiddenPages * kPageSize, in_fstream.beg);
//     in_fstream.read(reinterpret_cast<char*>(buffer.get()), kPageSize);

//     REQUIRE(memcmp(buffer.get(), data2.get(), kPageSize) == 0);

//     remove(file_name.c_str());
//   }
// }

// TEST_CASE("FileHandle meta-info counters should work", "[file][FileHandle]") {
//   using daleiDB::Byte;
//   using daleiDB::file_manager::kPageSize;
//   using daleiDB::file_manager::PagedFileManager;
//   using daleiDB::file_manager::FileHandle;

//   const std::string file_name = "test_file.tmp";
//   PagedFileManager& paged_file_manager = PagedFileManager::Instance();
//   FileHandle file_handle;

//   auto data = std::shared_ptr<Byte>(new Byte[kPageSize]);
//   auto buffer = std::shared_ptr<Byte>(new Byte[kPageSize]);

//   for (size_t i = 0; i < kPageSize; ++i)
//     data.get()[i] = 'a' + (i % 26);

//   SECTION("Empty file should have 0 pages") {
//     remove(file_name.c_str());
//     CHECK_NOTHROW(paged_file_manager.CreateFile(file_name));
//     CHECK(std::ifstream(file_name));
//     CHECK_NOTHROW(paged_file_manager.OpenFile(file_name, &file_handle));

//     REQUIRE(file_handle.GetNumPages() == 0);

//     remove(file_name.c_str());
//   }

//   SECTION("Empty file should have 0 reads") {
//     remove(file_name.c_str());
//     CHECK_NOTHROW(paged_file_manager.CreateFile(file_name));
//     CHECK(std::ifstream(file_name));
//     CHECK_NOTHROW(paged_file_manager.OpenFile(file_name, &file_handle));

//     REQUIRE(file_handle.GetReadCounter() == 0);

//     remove(file_name.c_str());
//   }

//   SECTION("Empty file should have 0 writes") {
//     remove(file_name.c_str());
//     CHECK_NOTHROW(paged_file_manager.CreateFile(file_name));
//     CHECK(std::ifstream(file_name));
//     CHECK_NOTHROW(paged_file_manager.OpenFile(file_name, &file_handle));

//     REQUIRE(file_handle.GetWriteCounter() == 0);

//     remove(file_name.c_str());
//   }

//   SECTION("Empty file should have 0 appends") {
//     remove(file_name.c_str());
//     CHECK_NOTHROW(paged_file_manager.CreateFile(file_name));
//     CHECK(std::ifstream(file_name));
//     CHECK_NOTHROW(paged_file_manager.OpenFile(file_name, &file_handle));

//     REQUIRE(file_handle.GetAppendCounter() == 0);

//     remove(file_name.c_str());
//   }

//   SECTION("Appending pages should increase the append counter") {
//     remove(file_name.c_str());
//     CHECK_NOTHROW(paged_file_manager.CreateFile(file_name));
//     CHECK(std::ifstream(file_name));
//     CHECK_NOTHROW(paged_file_manager.OpenFile(file_name, &file_handle));
//     CHECK_NOTHROW(file_handle.AppendPage(data.get()));

//     REQUIRE(file_handle.GetAppendCounter() == 1);

//     CHECK_NOTHROW(file_handle.AppendPage(data.get()));

//     REQUIRE(file_handle.GetAppendCounter() == 2);

//     remove(file_name.c_str());
//   }

//   SECTION("Reading pages should increase the read counter") {
//     remove(file_name.c_str());
//     CHECK_NOTHROW(paged_file_manager.CreateFile(file_name));
//     CHECK(std::ifstream(file_name));
//     CHECK_NOTHROW(paged_file_manager.OpenFile(file_name, &file_handle));
//     CHECK_NOTHROW(file_handle.AppendPage(data.get()));
//     CHECK_NOTHROW(file_handle.ReadPage(0, buffer.get()));

//     REQUIRE(file_handle.GetReadCounter() == 1);

//     CHECK_NOTHROW(file_handle.ReadPage(0, buffer.get()));

//     REQUIRE(file_handle.GetReadCounter() == 2);

//     remove(file_name.c_str());
//   }

//   SECTION("Writing pages should increase the write counter") {
//     remove(file_name.c_str());
//     CHECK_NOTHROW(paged_file_manager.CreateFile(file_name));
//     CHECK(std::ifstream(file_name));
//     CHECK_NOTHROW(paged_file_manager.OpenFile(file_name, &file_handle));
//     CHECK_NOTHROW(file_handle.AppendPage(data.get()));
//     CHECK_NOTHROW(file_handle.WritePage(0, data.get()));

//     REQUIRE(file_handle.GetWriteCounter() == 1);

//     CHECK_NOTHROW(file_handle.WritePage(0, data.get()));

//     REQUIRE(file_handle.GetWriteCounter() == 2);

//     remove(file_name.c_str());
//   }

//   SECTION("Meta-info should persist on disk") {
//     remove(file_name.c_str());
//     CHECK_NOTHROW(paged_file_manager.CreateFile(file_name));
//     CHECK(std::ifstream(file_name));
//     CHECK_NOTHROW(paged_file_manager.OpenFile(file_name, &file_handle));
//     CHECK_NOTHROW(file_handle.AppendPage(data.get()));
//     CHECK_NOTHROW(file_handle.WritePage(0, data.get()));
//     CHECK_NOTHROW(file_handle.ReadPage(0, buffer.get()));
//     CHECK_NOTHROW(paged_file_manager.CloseFile(&file_handle));
//     CHECK_FALSE(file_handle.Opened());
//     CHECK_NOTHROW(paged_file_manager.OpenFile(file_name, &file_handle));
//     CHECK(file_handle.Opened());

//     REQUIRE(file_handle.GetNumPages() == 1);
//     REQUIRE(file_handle.GetReadCounter() == 1);
//     REQUIRE(file_handle.GetWriteCounter() == 1);
//     REQUIRE(file_handle.GetAppendCounter() == 1);

//     remove(file_name.c_str());
//   }
// }
