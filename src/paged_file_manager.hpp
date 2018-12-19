#ifndef DALEIDB_PAGED_FILE_MANAGER_HPP_
#define DALEIDB_PAGED_FILE_MANAGER_HPP_

#include <cstdint>
#include <fstream>
#include <string>
#include <memory>
#include <mutex>

#include "common.hpp"

namespace daleiDB::file_manager {

typedef uint32_t PageNum;

constexpr uint32_t kPageSize = 4096;
constexpr uint32_t kNumHiddenPages = 1;

class FileHandle {
 public:
  FileHandle();
  ~FileHandle();

  bool Opened() const;
  void OpenFile(const std::string& file_name);
  void CloseFile();

  void ReadPage(const PageNum& page_num, Byte* buffer);
  void WritePage(const PageNum& page_num, const Byte* buffer);
  void AppendPage(const Byte* buffer);

  uint32_t GetNumPages() const;
  uint32_t GetReadCounter() const;
  uint32_t GetWriteCounter() const;
  uint32_t GetAppendCounter() const;

 private:
  std::fstream file_;
  uint32_t num_pages_;
  uint32_t read_counter_;
  uint32_t write_counter_;
  uint32_t append_counter_;
};

class PagedFileManager {
 public:
  static PagedFileManager& Instance();

  void CreateFile(const std::string& file_name);
  void DestroyFile(const std::string& file_name);
  void OpenFile(const std::string& file_name, FileHandle* file_handle);
  void CloseFile(FileHandle* file_handle);

  ~PagedFileManager() = default;
  PagedFileManager(const PagedFileManager&) = delete;
  PagedFileManager& operator=(const PagedFileManager&) = delete;

 protected:
  PagedFileManager() = default;

 private:
  static std::unique_ptr<PagedFileManager> instance_;
  static std::once_flag once_flag_;
};

}  // namespace daleiDB::file_manager

#endif  // DALEIDB_PAGED_FILE_MANAGER_HPP_
