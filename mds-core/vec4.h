//
// Created by oshikuru on 22. 10. 2020..
//

#ifndef MDS_VEC4_H
#define MDS_VEC4_H

#include "vec3.h"

namespace mds
{
    template<typename T, uint8_t A, uint8_t B, uint8_t C, uint8_t D>
    struct vec4_swizzle;

    template<typename T>
    struct vec4
    {
        vec4() = default;
        template<typename U>
        vec4(const vec4<U>& value);
        vec4(T value);
        template<typename U>
        vec4(const vec3<U>& rgb, T a = 0);
        vec4(T r, T g, T b, T a);

        union
        {
            T v[4];
            struct { T x, y, z, w; };
            struct { T r, g, b, a; };
            struct { T s, t, p, q; };
            vec2_swizzle<T, 0, 1> xy, rg, st;
            vec2_swizzle<T, 1, 2> yz, gb, tp;
            vec2_swizzle<T, 2, 3> zw, ba, pq;
            vec3_swizzle<T, 0, 1, 2> xyz, rgb, stp;
            vec3_swizzle<T, 1, 2, 3> yzw, gba, tpq;
            vec3_swizzle<T, 2, 3, 0> zwx, bar, pqs;
            vec3_swizzle<T, 3, 0, 1> wxy, arg, qst;
            vec4_swizzle<T, 0, 1, 3, 2> xywz, rgab, stqp;
            vec4_swizzle<T, 0, 2, 1, 3> xzyw, rbga, sptq;
            vec4_swizzle<T, 0, 2, 3, 1> xzwy, rbag, spqt;
            vec4_swizzle<T, 0, 3, 1, 2> xwyz, ragb, sqtp;
            vec4_swizzle<T, 0, 3, 2, 1> xwzy, rabg, sqpt;
            vec4_swizzle<T, 1, 0, 2, 3> yxzw, grba, tspq;
            vec4_swizzle<T, 1, 0, 3, 2> yxwz, grab, tsqp;
            vec4_swizzle<T, 1, 2, 0, 3> yzxw, gbra, tpsq;
            vec4_swizzle<T, 1, 2, 3, 0> yzwx, gbar, tpqs;
            vec4_swizzle<T, 1, 3, 0, 2> ywxz, garb, tqsp;
            vec4_swizzle<T, 1, 3, 2, 0> ywzx, gabr, tqps;
            vec4_swizzle<T, 2, 0, 1, 3> zxyw, brga, pstq;
            vec4_swizzle<T, 2, 0, 3, 1> zxwy, brag, psqt;
            vec4_swizzle<T, 2, 1, 0, 3> zyxw, bgra, ptsq;
            vec4_swizzle<T, 2, 1, 3, 0> zywx, bgar, ptqs;
            vec4_swizzle<T, 2, 3, 0, 1> zwxy, barg, pqst;
            vec4_swizzle<T, 2, 3, 1, 0> zwyx, bagr, pqts;
            vec4_swizzle<T, 3, 0, 1, 2> wxyz, argb, qstp;
            vec4_swizzle<T, 3, 0, 2, 1> wxzy, arbg, qspt;
            vec4_swizzle<T, 3, 1, 0, 2> wyxz, agrb, qtsp;
            vec4_swizzle<T, 3, 1, 2, 0> wyzx, agbr, qtps;
            vec4_swizzle<T, 3, 2, 0, 1> wzxy, abrg, qpst;
            vec4_swizzle<T, 3, 2, 1, 0> wzyx, abgr, qpts;
        };

        template<typename U>
        vec4& operator+=(const vec4<U>& other);
        template<typename U>
        vec4& operator-=(const vec4<U>& other);
        template<typename U>
        vec4& operator*=(const vec4<U>& other);
        template<typename U>
        vec4& operator/=(const vec4<U>& other);
    };

    template<typename T>
    auto to_vec4(T *data);

    template<typename T>
    vec4<T> abs(vec4<T> vec);

    using vec4c = vec4<int8_t>;
    using vec4uc = vec4<uint8_t>;
    using vec4s = vec4<int16_t>;
    using vec4us = vec4<uint16_t>;
    using vec4i = vec4<int32_t>;
    using vec4ui = vec4<uint32_t>;
    using vec4l = vec4<int64_t>;
    using vec4ul = vec4<uint64_t>;
    using vec4f = vec4<float>;
    using vec4d = vec4<double>;

    template<typename T, uint8_t A, uint8_t B, uint8_t C, uint8_t D>
    struct vec4_swizzle
    {
        T v[4];
        vec4<T> operator=(const vec4<T>& vec) { return vec4<T>(v[A] = vec.x, v[B] = vec.y, v[C] = vec.z, v[D] = vec.w); }
        operator vec4<T>() const { return vec4<T>(v[A], v[B], v[C], v[D]); }
        vec4<T> operator+=(const vec4<T>& vec) { return vec4<T>(v[A] += vec.x, v[B] += vec.y, v[C] += vec.z, v[D] += vec.w); };
        vec4<T> operator-=(const vec4<T>& vec) { return vec4<T>(v[A] -= vec.x, v[B] -= vec.y, v[C] -= vec.z, v[D] -= vec.w); };
        vec4<T> operator*=(const vec4<T>& vec) { return vec4<T>(v[A] *= vec.x, v[B] *= vec.y, v[C] *= vec.z, v[D] *= vec.w); };
        vec4<T> operator/=(const vec4<T>& vec) { return vec4<T>(v[A] /= vec.x, v[B] /= vec.y, v[C] /= vec.z, v[D] /= vec.w); };
    };
}

template<typename T>
template<typename U>
mds::vec4<T>::vec4(const mds::vec4<U> &value) : vec4(value.r, value.g, value.b, value.a)
{
}

template<typename T>
mds::vec4<T>::vec4(T value) : v{value, value, value, value}
{
}

template<typename T>
mds::vec4<T>::vec4(T r, T g, T b, T a) : v{r, g, b, a}
{
}

template<typename T>
template<typename U>
mds::vec4<T>::vec4(const mds::vec3<U> &rgb, T a) : vec4(rgb.r, rgb.g, rgb.b, a)
{
}

template<typename T>
auto mds::to_vec4(T *data)
{
    struct result
    {
        operator vec4<T>*()
        {
            return reinterpret_cast<vec4<T>*>(data);
        }

        operator vec4<T>&()
        {
            return *reinterpret_cast<vec4<T>*>(data);
        }

        T *data;
    };
    return result{ data };
}

template<typename T>
template<typename U>
mds::vec4<T> &mds::vec4<T>::operator+=(const mds::vec4<U> &other)
{
    this->r += other.r;
    this->g += other.g;
    this->b += other.b;
    this->a += other.a;
    return *this;
}

template<typename T>
template<typename U>
mds::vec4<T> &mds::vec4<T>::operator-=(const mds::vec4<U> &other)
{
    this->r -= other.r;
    this->g -= other.g;
    this->b -= other.b;
    this->a -= other.a;
    return *this;
}

template<typename T>
template<typename U>
mds::vec4<T> &mds::vec4<T>::operator*=(const mds::vec4<U> &other)
{
    this->r *= other.r;
    this->g *= other.g;
    this->b *= other.b;
    this->a *= other.a;
    return *this;
}

template<typename T>
template<typename U>
mds::vec4<T> &mds::vec4<T>::operator/=(const mds::vec4<U> &other)
{
    this->r /= other.r;
    this->g /= other.g;
    this->b /= other.b;
    this->a /= other.a;
    return *this;
}

template<typename T, typename U>
mds::vec4<decltype(T{} + U{})> operator+(const mds::vec4<T>& lhs, const mds::vec4<U>& rhs)
{
    return mds::vec4<decltype(T{} + U{})>{lhs} += rhs;
}

template<typename T, typename U>
mds::vec4<decltype(T{} - U{})> operator-(const mds::vec4<T>& lhs, const mds::vec4<U>& rhs)
{
    return mds::vec4<decltype(T{} - U{})>{lhs} -= rhs;
}

template<typename T, typename U>
mds::vec4<decltype(T{} * U{})> operator*(const mds::vec4<T>& lhs, const mds::vec4<U>& rhs)
{
    return mds::vec4<decltype(T{} * U{})>{lhs} *= rhs;
}

template<typename T, typename U>
mds::vec4<decltype(T{} / U{})> operator/(const mds::vec4<T>& lhs, const mds::vec4<U>& rhs)
{
    return mds::vec4<decltype(T{} / U{})>{lhs} /= rhs;
}

template<typename T, typename U>
bool operator==(const mds::vec4<T>& lhs, const mds::vec4<U>& rhs)
{
    return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a;
}

template<typename T, typename U>
bool operator!=(const mds::vec4<T>& lhs, const mds::vec4<U>& rhs)
{
    return !(lhs == rhs);
}

template<typename T>
mds::vec4<T> mds::abs(mds::vec4<T> vec)
{
    vec.r = std::abs(vec.r);
    vec.g = std::abs(vec.g);
    vec.b = std::abs(vec.b);
    vec.a = std::abs(vec.a);
    return vec;
}

#endif //MDS_VEC4_H
