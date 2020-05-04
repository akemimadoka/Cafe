set(CAFE_CORE_INCLUDE_TEST ON CACHE BOOL "Include core test")

add_library(Cafe.Core INTERFACE)

target_include_directories(Cafe.Core INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>)

target_compile_features(Cafe.Core INTERFACE cxx_std_20)

install(TARGETS Cafe.Core
    EXPORT Core)

install(DIRECTORY src/
    TYPE INCLUDE
    FILES_MATCHING PATTERN "*.h")

install(EXPORT Core
    DESTINATION cmake/Core)

if(CAFE_INCLUDE_TESTS AND CAFE_CORE_INCLUDE_TEST)
    add_subdirectory(Test)
endif()
