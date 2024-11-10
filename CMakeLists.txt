cmake_minimum_required(VERSION 3.14)
project(computer_algebra)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Werror)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(computer_algebra_lib
        src/model/natural_number.cpp
        src/model/integer_numbers.cpp
        src/model/rational_numbers.cpp
        src/model/polynomial.cpp
        src/core/processing_input.h
        src/core/processing_input.cpp

)

target_include_directories(computer_algebra_lib PUBLIC
        src
)

add_executable(computer-algebra
        src/main.cpp
)

target_link_libraries(computer-algebra PRIVATE computer_algebra_lib)

add_executable(computer-algebra-test
        tests/natural_number_test.cpp
        tests/integer_number_test.cpp
        tests/rational_numbers_test.cpp
        tests/polynomial_test.cpp
        tests/core_test.cpp
)

target_link_libraries(computer-algebra-test PRIVATE computer_algebra_lib gtest_main)

include(GoogleTest)
gtest_discover_tests(computer-algebra-test)
