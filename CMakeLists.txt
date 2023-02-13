cmake_minimum_required(VERSION 3.13)
project(war)              
set(CMAKE_CXX_STANDARD 20)


Include(FetchContent)


# Import Catch2, a header-only testing framework for C++
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

# main_test.cpp is our main test suite, running all sub tests.
add_executable(tests test/main_test.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_include_directories(tests PRIVATE include test)

add_executable(war src/main.cpp)
target_include_directories(war PRIVATE include)