set(SOURCE_FILES
    Functions.Test.cpp
    Main.cpp)

add_executable(Cafe.Core.Test ${SOURCE_FILES})

target_link_libraries(Cafe.Core.Test PRIVATE
    CONAN_PKG::Catch2 Cafe.Core)

ParseAndAddCatchTests(Cafe.Core.Test)
