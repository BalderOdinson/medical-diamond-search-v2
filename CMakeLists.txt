cmake_minimum_required(VERSION 3.17)
project(mds)

option(USE_OPENMP "Use OpenMP to parallelize execution" OFF)

add_subdirectory(mds-core)
add_subdirectory(mds-encoder)
add_subdirectory(mds-decoder)