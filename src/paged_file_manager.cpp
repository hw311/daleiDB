#include <cstdint>
#include <fstream>
#include <string>
#include <memory>
#include <mutex>

#include "paged_file_manager.hpp"
#include "file_manager_exception.hpp"

namespace daleiDB::file_manager {

FileHandle::FileHandle()
    : file_(), num_pages_(0), read_counter_(0), write_counter_(0),
      append_counter_(0) {
  file_.exceptions(std::fstream::badbit);
  file_.rdbuf()->pubsetbuf(nullptr, 0);
}

FileHandle::~FileHandle() {
  if (file_.is_open())
    CloseFile();
}

bool FileHandle::Opened() const {
  return file_.is_open();
}

void FileHandle::OpenFile(const std::string& file_name) {
  file_.clear();

  try {
    file_.open(file_name,
               std::fstream::in | std::fstream::out | std::fstream::binary);
    file_.seekg(0, file_.end);

    std::streamoff file_begin = 0;
    std::streamoff end_pos = file_.tellg();

    if (end_pos != file_begin) {  // Previous file
      file_.seekg(0, file_.beg);
      file_.read(reinterpret_cast<char*>(&num_pages_), sizeof(num_pages_));
      file_.read(reinterpret_cast<char*>(&read_counter_),
                 sizeof(read_counter_));
      file_.read(reinterpret_cast<char*>(&write_counter_),
                 sizeof(write_counter_));
      file_.read(reinterpret_cast<char*>(&append_counter_),
                 sizeof(append_counter_));
    } else {  // New file
      file_.seekp(kNumHiddenPages * kPageSize - 1);
      file_ << '$';
    }
  } catch (const std::fstream::failure& fstream_fail) {
    throw exception::IOFailure(fstream_fail);
  }
}

void FileHandle::CloseFile() {
  file_.clear();

  try {
    file_.seekp(0, file_.beg);
    file_.write(reinterpret_cast<const char*>(&num_pages_), sizeof(num_pages_));
    file_.write(reinterpret_cast<const char*>(&read_counter_),
                sizeof(read_counter_));
    file_.write(reinterpret_cast<const char*>(&write_counter_),
                sizeof(write_counter_));
    file_.write(reinterpret_cast<const char*>(&append_counter_),
                sizeof(append_counter_));
    file_.close();
  } catch (const std::fstream::failure& fstream_fail) {
    throw exception::IOFailure(fstream_fail);
  }

  num_pages_ = 0;
  read_counter_ = 0;
  write_counter_ = 0;
  append_counter_ = 0;
}

void FileHandle::ReadPage(const PageNum& page_num, Byte* buffer) {
  file_.clear();

  if (page_num >= num_pages_)
    throw exception::PageNumOutOfRange(page_num, num_pages_ - 1);

  try {
    file_.seekg((page_num + kNumHiddenPages) * kPageSize, file_.beg);
    file_.read(reinterpret_cast<char*>(buffer), kPageSize);
  } catch (const std::fstream::failure& fstream_fail) {
    throw exception::IOFailure(fstream_fail);
  }

  ++read_counter_;
}

void FileHandle::WritePage(const PageNum& page_num, const Byte* buffer) {
  file_.clear();

  if (page_num >= num_pages_)
    throw exception::PageNumOutOfRange(page_num, num_pages_ - 1);

  try {
    file_.seekp((page_num + kNumHiddenPages) * kPageSize, file_.beg);
    file_.write(reinterpret_cast<const char*>(buffer), kPageSize);
    file_.flush();
  } catch (const std::fstream::failure& fstream_fail) {
    throw exception::IOFailure(fstream_fail);
  }

  ++write_counter_;
}

void FileHandle::AppendPage(const Byte* buffer) {
  file_.clear();

  try {
    file_.seekp(0, file_.end);
    file_.write(reinterpret_cast<const char*>(buffer), kPageSize);
    file_.flush();
  } catch (const std::fstream::failure& fstream_fail) {
    throw exception::IOFailure(fstream_fail);
  }

  ++num_pages_;
  ++append_counter_;
}

uint32_t FileHandle::GetNumPages() const {
  return num_pages_;
}

uint32_t FileHandle::GetReadCounter() const {
  return read_counter_;
}

uint32_t FileHandle::GetWriteCounter() const {
  return write_counter_;
}

uint32_t FileHandle::GetAppendCounter() const {
  return append_counter_;
}

std::unique_ptr<PagedFileManager> PagedFileManager::instance_ = nullptr;
std::once_flag PagedFileManager::once_flag_;

PagedFileManager& PagedFileManager::Instance() {
  std::call_once(once_flag_, [] { instance_.reset(new PagedFileManager()); });
  return *(instance_.get());
}

void PagedFileManager::CreateFile(const std::string& file_name) {
  if (std::ifstream(file_name))
    throw exception::FileAlreadyExists("File " + file_name + " already exists");

  try {
    std::fstream(file_name, std::fstream::out);
  } catch (const std::fstream::failure& fstream_fail) {
    throw exception::IOFailure(fstream_fail);
  }
}

void PagedFileManager::DestroyFile(const std::string& file_name) {
  if (!std::ifstream(file_name))
    throw exception::FileNotFound("File " + file_name + " not found");

  if (remove(file_name.c_str()) != 0)
    throw exception::IOFailure("Deletion failure");
}

void PagedFileManager::OpenFile(const std::string& file_name,
                                FileHandle* file_handle) {
  if (file_handle->Opened())
    throw exception::FileHandleInUse();

  if (!std::ifstream(file_name))
    throw exception::FileNotFound("File " + file_name + " not found");

  file_handle->OpenFile(file_name);
}

void PagedFileManager::CloseFile(FileHandle* file_handle) {
  file_handle->CloseFile();
}

}  // namespace daleiDB::file_manager
