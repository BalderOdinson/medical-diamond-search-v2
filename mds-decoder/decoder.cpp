//
// Created by oshikuru on 24. 10. 2020..
//

#include "decoder.h"
#include <cstring>

constexpr size_t BlockHeight8x8 = 8;
constexpr size_t BlockWidth8x8 = 8;
constexpr size_t BlockHeight16x16 = 16;
constexpr size_t BlockWidth16x16 = 16;
constexpr size_t NumOfPixels8x8 = 64;
constexpr size_t NumOfPixels16x16 = 256;

mds::rgb_image
mds::decoder::decode_motion_vector8x8(const mds::rgb_image &referent_frame, const std::vector<motion_vector> &motions)
{
    rgb_image frame = referent_frame;
    for (const auto &motion : motions)
    {
        vec2<size_t> pixel = motion.block * vec2<size_t>{BlockWidth8x8};
        vec2<size_t> new_pixel = pixel + motion.direction;

        for (uint8_t i = 0; i < BlockHeight8x8; ++i)
        {
            memcpy(&frame[{new_pixel.y + i, new_pixel.x}],
                   &referent_frame[{pixel.y + i, pixel.x}],
                   sizeof(vec3uc) * BlockWidth8x8);
        }
    }
    return frame;
}
