add_library(Cafe.Core INTERFACE)

target_include_directories(Cafe.Core INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(Cafe.Core INTERFACE cxx_std_17)
