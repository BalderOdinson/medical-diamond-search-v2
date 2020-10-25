//
// Created by oshikuru on 20. 10. 2020..
//

#ifndef MDS_ENCODER_VEC_H
#define MDS_ENCODER_VEC_H

#include <cstdint>
#include <cstddef>
#include <cmath>

namespace mds
{
    template<typename T, uint8_t A, uint8_t B>
    struct vec2_swizzle;

    template<typename T>
    struct vec2
    {
        vec2() = default;
        template<typename U>
        vec2(const vec2<U>& value);
        vec2(T value);
        vec2(T r, T g);

        union
        {
            T v[2];
            struct { T x, y; };
            struct { T r, g; };
            struct { T s, t; };
            vec2_swizzle<T, 0, 0> xx;
            vec2_swizzle<T, 1, 1> yy;
            vec2_swizzle<T, 1, 0> yx;
        };

        template<typename U>
        vec2& operator+=(const vec2<U>& other);
        template<typename U>
        vec2& operator-=(const vec2<U>& other);
        template<typename U>
        vec2& operator*=(const vec2<U>& other);
        template<typename U>
        vec2& operator/=(const vec2<U>& other);
    };

    template<typename T>
    auto to_vec2(T *data);

    template<typename T>
    vec2<T> abs(vec2<T> vec);

    template<typename T, typename U>
    bool operator==(const mds::vec2<T>& lhs, const mds::vec2<U>& rhs);

    template<typename T, typename U>
    bool operator!=(const mds::vec2<T>& lhs, const mds::vec2<U>& rhs);

    using vec2c = vec2<int8_t>;
    using vec2uc = vec2<uint8_t>;
    using vec2s = vec2<int16_t>;
    using vec2us = vec2<uint16_t>;
    using vec2i = vec2<int32_t>;
    using vec2ui = vec2<uint32_t>;
    using vec2l = vec2<int64_t>;
    using vec2ul = vec2<uint64_t>;
    using vec2f = vec2<float>;
    using vec2d = vec2<double>;

    template<typename T, uint8_t A, uint8_t B>
    struct vec2_swizzle
    {
        T v[2];
        vec2<T> operator=(const vec2<T>& vec) { return vec2<T>(v[A] = vec.x, v[B] = vec.y); }
        operator vec2<T>() const { return vec2<T>(v[A], v[B]); }
        vec2<T> operator+=(const vec2<T>& vec) { return vec2<T>(v[A] += vec.x, v[B] += vec.y); };
        vec2<T> operator-=(const vec2<T>& vec) { return vec2<T>(v[A] -= vec.x, v[B] -= vec.y); };
        vec2<T> operator*=(const vec2<T>& vec) { return vec2<T>(v[A] *= vec.x, v[B] *= vec.y); };
        vec2<T> operator/=(const vec2<T>& vec) { return vec2<T>(v[A] /= vec.x, v[B] /= vec.y); };
    };
}

template<typename T>
template<typename U>
mds::vec2<T>::vec2(const mds::vec2<U> &value) : vec2(value.r, value.g)
{
}

template<typename T>
mds::vec2<T>::vec2(T value) : v{value, value}
{
}

template<typename T>
mds::vec2<T>::vec2(T r, T g) : v{r, g}
{
}

template<typename T>
auto mds::to_vec2(T *data)
{
    struct result
    {
        operator vec2<T>*()
        {
            return reinterpret_cast<vec2<T>*>(data);
        }

        operator vec2<T>&()
        {
            return *reinterpret_cast<vec2<T>*>(data);
        }

        T *data;
    };
    return result{ data };
}

template<typename T>
template<typename U>
mds::vec2<T> &mds::vec2<T>::operator+=(const mds::vec2<U> &other)
{
    this->r += other.r;
    this->g += other.g;
    return *this;
}

template<typename T>
template<typename U>
mds::vec2<T> &mds::vec2<T>::operator-=(const mds::vec2<U> &other)
{
    this->r -= other.r;
    this->g -= other.g;
    return *this;
}

template<typename T>
template<typename U>
mds::vec2<T> &mds::vec2<T>::operator*=(const mds::vec2<U> &other)
{
    this->r *= other.r;
    this->g *= other.g;
    return *this;
}

template<typename T>
template<typename U>
mds::vec2<T> &mds::vec2<T>::operator/=(const mds::vec2<U> &other)
{
    this->r /= other.r;
    this->g /= other.g;
    return *this;
}

template<typename T, typename U>
mds::vec2<decltype(T{} + U{})> operator+(const mds::vec2<T>& lhs, const mds::vec2<U>& rhs)
{
    return mds::vec2<decltype(T{} + U{})>{lhs} += rhs;
}

template<typename T, typename U>
mds::vec2<decltype(T{} - U{})> operator-(const mds::vec2<T>& lhs, const mds::vec2<U>& rhs)
{
    return mds::vec2<decltype(T{} - U{})>{lhs} -= rhs;
}

template<typename T, typename U>
mds::vec2<decltype(T{} * U{})> operator*(const mds::vec2<T>& lhs, const mds::vec2<U>& rhs)
{
    return mds::vec2<decltype(T{} * U{})>{lhs} *= rhs;
}

template<typename T, typename U>
mds::vec2<decltype(T{} / U{})> operator/(const mds::vec2<T>& lhs, const mds::vec2<U>& rhs)
{
    return mds::vec2<decltype(T{} / U{})>{lhs} /= rhs;
}

template<typename T, typename U>
bool mds::operator==(const mds::vec2<T>& lhs, const mds::vec2<U>& rhs)
{
    return lhs.r == rhs.r && lhs.g == rhs.g;
}

template<typename T, typename U>
bool mds::operator!=(const mds::vec2<T>& lhs, const mds::vec2<U>& rhs)
{
    return !(lhs == rhs);
}

template<typename T>
mds::vec2<T> mds::abs(mds::vec2<T> vec)
{
    vec.r = std::abs(vec.r);
    vec.g = std::abs(vec.g);
    return vec;
}

#endif //MDS_ENCODER_VEC_H
