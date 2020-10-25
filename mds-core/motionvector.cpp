//
// Created by oshikuru on 24. 10. 2020..
//

#include <cstdio>
#include "motionvector.h"

void mds::save(std::string_view filename, const std::vector<motion_vector> &motions)
{
    FILE* f = fopen(filename.data(), "wb");
    fwrite(motions.data(), sizeof(mds::motion_vector), motions.size(), f);
    fclose(f);
}

std::vector<mds::motion_vector> mds::load(std::string_view filename)
{
    FILE* f = fopen(filename.data(), "rb");

    fseek(f, 0L, SEEK_END);
    size_t size = ftell(f);
    rewind(f);

    std::vector<mds::motion_vector> data(size / sizeof(mds::motion_vector));

    fread(data.data(), sizeof(mds::motion_vector), data.size(), f);
    fclose(f);

    return data;
}