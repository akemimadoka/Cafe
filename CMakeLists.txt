cmake_minimum_required(VERSION 3.12)

project(Cafe CXX)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.13/conan.cmake"
                  "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(CONANFILE conanfile.txt
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing)

add_compile_definitions(CAFE_BUILDING)
if(BUILD_SHARED_LIBS)
    add_compile_definitions(CAFE_BUILDING_DLL)
endif()

add_subdirectory(Cafe.Core)

set(CAFE_INCLUDE_ENCODING OFF CACHE BOOL "Build encoding library")

if(CAFE_INCLUDE_ENCODING)
    add_subdirectory(Cafe.Encoding)
endif(CAFE_INCLUDE_ENCODING)
