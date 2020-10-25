//
// Created by oshikuru on 21. 10. 2020..
//

#include <cstdio>
#include "rgbimage.h"

mds::rgb_image::rgb_image(size_t width, size_t height) : width_(width), height_(height)
{
    data_.resize(width_ * height_);
}

mds::vec3uc *mds::rgb_image::data()
{
    return data_.data();
}

const mds::vec3uc *mds::rgb_image::data() const
{
    return data_.data();
}

mds::vec3uc &mds::rgb_image::operator[](size_t idx)
{
    return data_[idx];
}

const mds::vec3uc &mds::rgb_image::operator[](size_t idx) const
{
    return data_[idx];
}

mds::vec3uc &mds::rgb_image::operator[](const std::pair<size_t, size_t> &idx)
{
    return data_[idx.first * width_ + idx.second];
}

const mds::vec3uc &mds::rgb_image::operator[](const std::pair<size_t, size_t> &idx) const
{
    return data_[idx.first * width_ + idx.second];
}

size_t mds::rgb_image::width() const
{
    return width_;
}

size_t mds::rgb_image::height() const
{
    return height_;
}

std::pair<std::vector<uint8_t>, mds::rgb_image> mds::load_bitmap_image(std::string_view src_path)
{
    FILE* f = fopen(src_path.data(), "rb");
    std::vector<uint8_t> info(54);

    // read the 54-byte header
    fread(info.data(), sizeof(unsigned char), 54, f);

    // extract image height and width from header
    size_t width = *(int*)&info[18];
    size_t height = *(int*)&info[22];

    mds::rgb_image image(width, height);
    fread(image.data(), sizeof(vec3uc), width * height, f);
    fclose(f);

    return {std::move(info), image};
}

void mds::write_to_bitmap_image(const mds::rgb_image &img, const uint8_t *header, std::string_view src_path)
{
    FILE* f = fopen(src_path.data(), "wb");
    fwrite(header, 1, 54, f);
    fwrite(img.data(), sizeof(mds::vec3uc), img.width() * img.height(), f);
    fclose(f);
}
