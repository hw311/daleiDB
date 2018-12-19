#ifndef DALEIDB_FILE_MANAGER_EXCEPTION_HPP_
#define DALEIDB_FILE_MANAGER_EXCEPTION_HPP_

#include <stdexcept>
#include <ios>
#include <string>

namespace daleiDB::file_manager::exception {

class FileNotFound : public std::runtime_error {
 public:
  FileNotFound() : runtime_error("File not found") {}
  explicit FileNotFound(const std::string& message) : runtime_error(message) {}
};

class FileAlreadyExists : public std::runtime_error {
 public:
  FileAlreadyExists() : runtime_error("File already exists") {}
  explicit FileAlreadyExists(const std::string& message)
      : runtime_error(message) {}
};

class FileHandleInUse : public std::runtime_error {
 public:
  FileHandleInUse() : runtime_error("FileHandle already in use") {}
};

class PageNumOutOfRange : public std::runtime_error {
 public:
  PageNumOutOfRange() : runtime_error("Page number out of range") {}
  explicit PageNumOutOfRange(const std::string& message)
      : runtime_error(message) {}
  explicit PageNumOutOfRange(const uint32_t& page_num, const uint32_t& max)
      : runtime_error("Page number "
                      + std::to_string(page_num)
                      + " is out of range. Maximum is "
                      + std::to_string(max)) {}
};

class IOFailure : public std::runtime_error {
 public:
  IOFailure() : runtime_error("I/O failure") {}
  explicit IOFailure(const std::string& message) : runtime_error(message) {}
  explicit IOFailure(const std::ios_base::failure& ios_failure)
      : runtime_error(ios_failure.what()) {}
};

}  // namespace daleiDB::file_manager::exception

#endif  // DALEIDB_FILE_MANAGER_EXCEPTION_HPP_
