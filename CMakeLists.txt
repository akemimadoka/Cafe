cmake_minimum_required(VERSION 3.12)

project(Cafe
    VERSION 0.1
    DESCRIPTION "A general purpose C++ library"
    HOMEPAGE_URL "https://github.com/akemimadoka/Cafe"
    LANGUAGES "CXX")

set(CAFE_INCLUDE_TESTS OFF CACHE BOOL
    "Include tests, if this option is not enabled, all tests will be excluded even explicit enabled")

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.14/conan.cmake"
                  "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

if(CAFE_INCLUDE_TESTS)
    set(INCLUDE_TESTS True)
else()
    set(INCLUDE_TESTS False)
endif()

conan_cmake_run(CONANFILE conanfile.py
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing
                OPTIONS "CAFE_INCLUDE_TESTS=${INCLUDE_TESTS}")

add_compile_definitions(CAFE_BUILDING)
if(BUILD_SHARED_LIBS)
    add_compile_definitions(CAFE_BUILDING_DLL)
    if(CMAKE_SYSTEM_NAME MATCHES "Windows")
        set(CMAKE_SHARED_LIBRARY_PREFIX "")
    endif()
endif()

add_subdirectory(Cafe.Core)

set(CAFE_INCLUDE_ENCODING ON CACHE BOOL "Include encoding library")

if(CAFE_INCLUDE_ENCODING)
    add_subdirectory(Cafe.Encoding)
endif()

set(CAFE_INCLUDE_ERROR_HANDLING ON CACHE BOOL "Include error handling library")

if(CAFE_INCLUDE_ERROR_HANDLING)
    add_subdirectory(Cafe.ErrorHandling)
endif()

set(CAFE_INCLUDE_ENVIRONMENT ON CACHE BOOL "Include environment library")

if(CAFE_INCLUDE_ENVIRONMENT)
    add_subdirectory(Cafe.Environment)
endif()

set(CAFE_INCLUDE_TEXT_UTILS ON CACHE BOOL "Include text utilities library")

if(CAFE_INCLUDE_TEXT_UTILS)
    add_subdirectory(Cafe.TextUtils)
endif()

set(CAFE_INCLUDE_IO ON CACHE BOOL "Include io library")

if(CAFE_INCLUDE_IO)
    add_subdirectory(Cafe.Io)
endif()
