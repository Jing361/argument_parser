CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(ArgumentParser_test LANGUAGES CXX)

ADD_EXECUTABLE(arg_parse_test test.cc)
TARGET_INCLUDE_DIRECTORIES(arg_parse_test PUBLIC header)
TARGET_LINK_LIBRARIES(arg_parse_test
                      PUBLIC arg_parse
                      PUBLIC Catch2::Catch2WithMain)
SET_TARGET_PROPERTIES(arg_parse_test PROPERTIES
                      CXX_STANDARD 20
                      CXX_STANDARD_REQUIRED YES)
target_compile_options(arg_parse_test PRIVATE
                       $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
                       -Wall -Wextra -pedantic>
                       $<$<CXX_COMPILER_ID:MSVC>:
                       /W4>)
