cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-mavx2)

project(mds-decoder)
include_directories(../)
add_library(mds-decoder STATIC decoder.h decoder.cpp)
target_link_libraries(mds-decoder PUBLIC mds-core)

project(mds-decoder-tests)
include_directories(./)
add_executable(mds-decoder-tests tests/catch.hpp tests/catch.cpp tests/decoder.cpp)
target_link_libraries(mds-decoder-tests mds-decoder)

project(mds-decoder-cli)
include_directories(./)
add_executable(mds-decoder-cli main.cpp)
target_link_libraries(mds-decoder-cli mds-decoder)