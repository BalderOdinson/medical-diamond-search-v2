cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-mavx2)
if(USE_OPENMP)
    find_package(OpenMP REQUIRED)
    add_compile_options(-fopenmp)
endif()

project(mds-encoder)
include_directories(../)
add_library(mds-encoder STATIC sad.cpp sad.h mds.cpp mds.h)

if(USE_OPENMP)
    target_link_libraries(mds-encoder PUBLIC mds-core OpenMP::OpenMP_CXX)
else()
    target_link_libraries(mds-encoder PUBLIC mds-core)
endif()

project(mds-encoder-tests)
include_directories(./)
add_executable(mds-encoder-tests tests/catch.cpp tests/sad.cpp tests/mds.cpp)
target_link_libraries(mds-encoder-tests mds-encoder)

project(mds-encoder-cli)
include_directories(./)
add_executable(mds-encoder-cli main.cpp)
target_link_libraries(mds-encoder-cli mds-encoder)

# Generate assembly
# set_target_properties(mds-encoder-tests PROPERTIES COMPILE_FLAGS "-save-temps")