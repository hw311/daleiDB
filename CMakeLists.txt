cmake_minimum_required(VERSION 3.9)

project(daleiDB LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ($ENV{TRAVIS})
  if ($ENV{TRAVIS} STREQUAL "true")
    message(STATUS "Building on Travis-CI.")
    set(IS_TRAVIS_BUILD TRUE)
  endif()
endif()

option(GENERATE_COVERAGE_INFO "Generate line coverage info." ON)
if (GENERATE_COVERAGE_INFO)
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
    set(GCOV_COMMAND gcov CACHE STRING "Command to invoke to run gcov.")
  endif()
endif()

set(DALEIDB_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(TESTS_DIR ${DALEIDB_DIR}/tests)
set(UTILS_DIR ${DALEIDB_DIR}/utils)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)

find_package(Threads REQUIRED)

set(TEST_SOURCES
    ${TESTS_DIR}/src/run_unit_tests.cpp
    ${TESTS_DIR}/src/paged_file_manager_tests.cpp
    ${TESTS_DIR}/src/file_handle_tests.cpp
    )

set(DALEIDB_SOURCES
    ${DALEIDB_DIR}/src/paged_file_manager.cpp
    )

set(HEADER_DIR
    ${UTILS_DIR}
    ${DALEIDB_DIR}/src
    )

set(UTILS_HEADERS
    ${UTILS_DIR}/catch.hpp
    )

set(DALEIDB_HEADERS
    ${DALEIDB_DIR}/src/file_manager_exception.hpp
    ${DALEIDB_DIR}/src/paged_file_manager.hpp
    )

set(HEADERS
    ${UTILS_HEADERS}
    ${DALEIDB_HEADERS}
    )


# Build daleiDB ## Not now

# Build unit tests

option(BUILD_TESTS "Build tests." ON)
if (BUILD_TESTS)
  enable_testing()

  add_library(Catch INTERFACE)
  target_include_directories(Catch INTERFACE ${UTILS_DIR})

  add_executable(run_unit_tests ${TEST_SOURCES} ${DALEIDB_SOURCES} ${HEADERS})
  target_include_directories(run_unit_tests PUBLIC ${HEADER_DIR})
  target_link_libraries(run_unit_tests PUBLIC Threads::Threads Catch)

  if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
    target_compile_options(
        run_unit_tests PRIVATE
        -Wall -Wextra -Wunreachable-code -Wpedantic -Wmissing-declarations
        )
  endif()

  if (GENERATE_COVERAGE_INFO AND (CMAKE_CXX_COMPILER_ID STREQUAL "GNU"))
    target_compile_options(
        run_unit_tests PRIVATE
        -g -O0 -fprofile-arcs -ftest-coverage
        )
    target_link_libraries(run_unit_tests PRIVATE --coverage)
    add_custom_target(
        collect_coverage
        COMMAND ${GCOV_COMMAND} -o
        CMakeFiles/run_unit_tests.dir/src ${DALEIDB_SOURCES}
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        COMMENT "Collecting gcov covreage information"
        )
  endif()

  if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
      target_compile_options(
          run_unit_tests PRIVATE
          -Wweak-vtables -Wexit-time-destructors
          -Wglobal-constructors -Wmissing-noreturn
          )
  endif()

  if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
      STRING(REGEX REPLACE "/W[0-9]" "/W4" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
      target_compile_options(
          run_unit_tests PRIVATE
          /w44265 /w44061 /w44062 /w45038
          )
      target_compile_options(run_unit_tests PRIVATE /utf-8)
  endif()

  add_test(NAME unit_tests COMMAND run_unit_tests)
endif()

# Build Doxygen docs

option(GENERATE_DOXYGEN_DOC "Generate Doxygen documentation." ON)
if (GENERATE_DOXYGEN_DOC)
  find_package(Doxygen)
  if (TARGET Doxygen::doxygen)
    get_property(
        DOXYGEN_EXECUTABLE
        TARGET Doxygen::doxygen
        PROPERTY IMPORTED_LOCATION
        )

    set(DOC_DIR ${PROJECT_BINARY_DIR}/doc)
    configure_file(${DALEIDB_DIR}/doc/Doxyfile.in ${DOC_DIR}/Doxyfile @ONLY)
    add_custom_target(
        doc
        COMMAND ${DOXYGEN_EXECUTABLE}
        WORKING_DIRECTORY ${DOC_DIR}
        COMMENT "Building doxygen documentation"
        SOURCES ${DALEIDB_DIR}/doc/Doxyfile.in
        )
  endif()
endif()
