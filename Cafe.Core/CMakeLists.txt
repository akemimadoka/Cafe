add_library(Cafe.Core INTERFACE)

target_include_directories(Cafe.Core INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

target_compile_features(Cafe.Core INTERFACE cxx_std_20)

install(TARGETS Cafe.Core
    EXPORT Core)

install(DIRECTORY include/
    TYPE INCLUDE
    FILES_MATCHING PATTERN "*.h")

install(EXPORT Core
    DESTINATION cmake/Core)
