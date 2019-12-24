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
