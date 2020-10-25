cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-mavx2)

project(mds-core)
add_library(mds-core STATIC vec2.cpp vec2.h vector.cpp vector.h block.cpp block.h rgbimage.cpp rgbimage.h vec3.cpp vec3.h vec4.cpp vec4.h blockiterator.cpp blockiterator.h motionvector.cpp motionvector.h)

project(mds-core-tests)
include_directories(./)
add_executable(mds-core-tests tests/catch.cpp tests/vec.cpp tests/block.cpp tests/vector.cpp tests/image.cpp tests/blockiterator.cpp)
target_link_libraries(mds-core-tests mds-core)


# Generate assembly
# set_target_properties(mds-encoder-tests PROPERTIES COMPILE_FLAGS "-save-temps")