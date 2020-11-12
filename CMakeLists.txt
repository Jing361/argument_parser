CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(ArgumentParser LANGUAGES CXX)

ADD_LIBRARY(arg_parse source/argparse.cc)
TARGET_INCLUDE_DIRECTORIES(arg_parse PUBLIC header)
SET_TARGET_PROPERTIES(arg_parse PROPERTIES
                      CXX_STANDARD 20
                      CXX_STANDARD_REQUIRED YES)
target_compile_options(arg_parse PRIVATE
                       $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
                       -Wall -Wextra -pedantic>
                       $<$<CXX_COMPILER_ID:MSVC>:
                       /W4>)

ADD_SUBDIRECTORY(vendor/Catch2)
ADD_SUBDIRECTORY(test)

