//
// Created by oshikuru on 21. 10. 2020..
//

#ifndef MDS_ENCODER_TESTS_BLOCK_H
#define MDS_ENCODER_TESTS_BLOCK_H

#include <cstdint>
#include <array>
#include <cmath>
#include "vector.h"

namespace mds
{
    template<typename Type, uint8_t Width, uint8_t Height>
    struct block
    {
        block();

        vec256<Type> &operator[](size_t idx);
        const vec256<Type> &operator[](size_t idx) const;

        Type &operator[](const std::pair<size_t, size_t> &idx);
        const Type &operator[](const std::pair<size_t, size_t> &idx) const;

        Type *data();
        const Type *data() const;

    private:
        std::array<vec256<Type>, Width * Height / mds::NumOfElements<Type>> data_;
    };

    using block8x8 = block<int16_t, 8, 8>;
    using block16x16 = block<int16_t, 16, 16>;

    template<typename Type, uint8_t Width, uint8_t Height>
    block<Type, Width, Height>::block()
    {
        static_assert((Width * Height) % mds::NumOfElements<Type> == 0, "Block width * height must be divisible with number of elements in vector");
    }

    template<typename Type, uint8_t Width, uint8_t Height>
    vec256<Type> &block<Type, Width, Height>::operator[](size_t idx)
    {
        return data_[idx];
    }

    template<typename Type, uint8_t Width, uint8_t Height>
    const vec256<Type> &block<Type, Width, Height>::operator[](size_t idx) const
    {
        return data_[idx];
    }

    template<typename Type, uint8_t Width, uint8_t Height>
    Type &block<Type, Width, Height>::operator[](const std::pair<size_t, size_t> &idx)
    {
        size_t i = idx.first * Width + idx.second;
        return data_[i / mds::NumOfElements<Type>][i % mds::NumOfElements<Type>];
    }

    template<typename Type, uint8_t Width, uint8_t Height>
    const Type &block<Type, Width, Height>::operator[](const std::pair<size_t, size_t> &idx) const
    {
        size_t i = idx.second * Width + idx.first;
        return data_[i / mds::NumOfElements<Type>][i % mds::NumOfElements<Type>];
    }

    template<typename Type, uint8_t Width, uint8_t Height>
    Type *block<Type, Width, Height>::data()
    {
        return data_[0];
    }

    template<typename Type, uint8_t Width, uint8_t Height>
    const Type *block<Type, Width, Height>::data() const
    {
        return data_[0];
    }
}


#endif //MDS_ENCODER_TESTS_BLOCK_H
