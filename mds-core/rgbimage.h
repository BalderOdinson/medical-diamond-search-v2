//
// Created by oshikuru on 21. 10. 2020..
//

#ifndef MDS_ENCODER_TESTS_RGBIMAGE_H
#define MDS_ENCODER_TESTS_RGBIMAGE_H

#include <vector>
#include <string_view>
#include "vec3.h"

namespace mds
{
    struct rgb_image
    {
        rgb_image() = default;
        rgb_image(size_t width, size_t height);
        rgb_image(const rgb_image& other) = default;
        rgb_image(rgb_image&& other) noexcept = default;

        rgb_image& operator=(const rgb_image& other) = default;
        rgb_image& operator=(rgb_image&& other) noexcept = default;

        vec3uc* data();
        [[nodiscard]] const vec3uc* data() const;

        vec3uc &operator[](size_t idx);
        const vec3uc &operator[](size_t idx) const;

        vec3uc &operator[](const std::pair<size_t, size_t> &idx);
        const vec3uc &operator[](const std::pair<size_t, size_t> &idx) const;

        [[nodiscard]] size_t width() const;
        [[nodiscard]] size_t height() const;

    private:
        size_t width_{};
        size_t height_{};
        std::vector<vec3uc> data_;
    };

    std::pair<std::vector<uint8_t>, rgb_image> load_bitmap_image(std::string_view src_path);
    void write_to_bitmap_image(const rgb_image& img, const uint8_t* header, std::string_view src_path);
}


#endif //MDS_ENCODER_TESTS_RGBIMAGE_H
