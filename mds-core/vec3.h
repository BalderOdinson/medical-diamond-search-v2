//
// Created by oshikuru on 22. 10. 2020..
//

#ifndef MDS_VEC3_H
#define MDS_VEC3_H

#include "vec2.h"

namespace mds
{
    template<typename T, uint8_t A, uint8_t B, uint8_t C>
    struct vec3_swizzle;

    template<typename T>
    struct vec3
    {
        vec3() = default;
        template<typename U>
        vec3(const vec3<U>& value);
        vec3(T value);
        template<typename U>
        vec3(const vec2<U>& rg, T b = 0);
        vec3(T r, T g, T b);

        union
        {
            T v[3];
            struct { T x, y, z; };
            struct { T r, g, b; };
            struct { T s, t, p; };
            vec2_swizzle<T, 0, 0> xx, rr, ss;
            vec2_swizzle<T, 0, 1> xy, rg, st;
            vec2_swizzle<T, 0, 2> xz, rb, sp;
            vec2_swizzle<T, 1, 0> yx, gr, ts;
            vec2_swizzle<T, 1, 1> yy, gg, tt;
            vec2_swizzle<T, 1, 2> yz, gb, tp;
            vec2_swizzle<T, 2, 0> zx, br, ps;
            vec2_swizzle<T, 2, 1> zy, bg, pt;
            vec2_swizzle<T, 2, 2> zz, bb, pp;
            vec3_swizzle<T, 0, 0, 0> xxx, rrr, sss;
            vec3_swizzle<T, 0, 0, 1> xxy, rrg, sst;
            vec3_swizzle<T, 0, 0, 2> xxz, rrb, ssp;
            vec3_swizzle<T, 0, 1, 0> xyx, rgr, sts;
            vec3_swizzle<T, 0, 1, 1> xyy, rgg, stt;
            vec3_swizzle<T, 0, 1, 2> xyz, rgb, stp;
            vec3_swizzle<T, 0, 2, 0> xzx, rbr, sps;
            vec3_swizzle<T, 0, 2, 1> xzy, rbg, spt;
            vec3_swizzle<T, 0, 2, 2> xzz, rbb, spp;
            vec3_swizzle<T, 1, 0, 0> yxx, grr, tss;
            vec3_swizzle<T, 1, 0, 1> yxy, grg, tst;
            vec3_swizzle<T, 1, 0, 2> yxz, grb, tsp;
            vec3_swizzle<T, 1, 1, 0> yyx, ggr, tts;
            vec3_swizzle<T, 1, 1, 1> yyy, ggg, ttt;
            vec3_swizzle<T, 1, 1, 2> yyz, ggb, ttp;
            vec3_swizzle<T, 1, 2, 0> yzx, gbr, tps;
            vec3_swizzle<T, 1, 2, 1> yzy, gbg, tpt;
            vec3_swizzle<T, 1, 2, 2> yzz, gbb, tpp;
            vec3_swizzle<T, 2, 0, 0> zxx, brr, pss;
            vec3_swizzle<T, 2, 0, 1> zxy, brg, pst;
            vec3_swizzle<T, 2, 0, 2> zxz, brb, psp;
            vec3_swizzle<T, 2, 1, 0> zyx, bgr, pts;
            vec3_swizzle<T, 2, 1, 1> zyy, bgg, ptt;
            vec3_swizzle<T, 2, 1, 2> zyz, bgb, ptp;
            vec3_swizzle<T, 2, 2, 0> zzx, bbr, ppt;
            vec3_swizzle<T, 2, 2, 1> zzy, bbg, pps;
            vec3_swizzle<T, 2, 2, 2> zzz, bbb, ppp;
        };

        template<typename U>
        vec3& operator+=(const vec3<U>& other);
        template<typename U>
        vec3& operator-=(const vec3<U>& other);
        template<typename U>
        vec3& operator*=(const vec3<U>& other);
        template<typename U>
        vec3& operator/=(const vec3<U>& other);
    };

    template<typename T>
    auto to_vec3(T *data);

    template<typename T>
    vec3<T> abs(vec3<T> vec);

    using vec3c = vec3<int8_t>;
    using vec3uc = vec3<uint8_t>;
    using vec3s = vec3<int16_t>;
    using vec3us = vec3<uint16_t>;
    using vec3i = vec3<int32_t>;
    using vec3ui = vec3<uint32_t>;
    using vec3l = vec3<int64_t>;
    using vec3ul = vec3<uint64_t>;
    using vec3f = vec3<float>;
    using vec3d = vec3<double>;

    template<typename T, uint8_t A, uint8_t B, uint8_t C>
    struct vec3_swizzle
    {
        T v[3];
        vec3<T> operator=(const vec3<T>& vec) { return vec3<T>(v[A] = vec.x, v[B] = vec.y, v[C] = vec.z); }
        operator vec3<T>() const { return vec3<T>(v[A], v[B], v[C]); }
        vec3<T> operator+=(const vec3<T>& vec) { return vec3<T>(v[A] += vec.x, v[B] += vec.y, v[C] += vec.z); };
        vec3<T> operator-=(const vec3<T>& vec) { return vec3<T>(v[A] -= vec.x, v[B] -= vec.y, v[C] -= vec.z); };
        vec3<T> operator*=(const vec3<T>& vec) { return vec3<T>(v[A] *= vec.x, v[B] *= vec.y, v[C] *= vec.z); };
        vec3<T> operator/=(const vec3<T>& vec) { return vec3<T>(v[A] /= vec.x, v[B] /= vec.y, v[C] /= vec.z); };
    };
}

template<typename T>
template<typename U>
mds::vec3<T>::vec3(const mds::vec3<U> &value) : vec3(value.r, value.g, value.b)
{
}

template<typename T>
mds::vec3<T>::vec3(T value) : v{value, value, value}
{
}

template<typename T>
template<typename U>
mds::vec3<T>::vec3(const mds::vec2<U> &rg, T b) : vec3(rg.r, rg.g, b)
{
}

template<typename T>
mds::vec3<T>::vec3(T r, T g, T b) : v{r, g, b}
{
}

template<typename T>
auto mds::to_vec3(T *data)
{
    struct result
    {
        operator vec3<T>*()
        {
            return reinterpret_cast<vec3<T>*>(data);
        }

        operator vec3<T>&()
        {
            return *reinterpret_cast<vec3<T>*>(data);
        }

        T *data;
    };
    return result{ data };
}

template<typename T>
template<typename U>
mds::vec3<T> &mds::vec3<T>::operator+=(const mds::vec3<U> &other)
{
    this->r += other.r;
    this->g += other.g;
    this->b += other.b;
    return *this;
}

template<typename T>
template<typename U>
mds::vec3<T> &mds::vec3<T>::operator-=(const mds::vec3<U> &other)
{
    this->r -= other.r;
    this->g -= other.g;
    this->b -= other.b;
    return *this;
}

template<typename T>
template<typename U>
mds::vec3<T> &mds::vec3<T>::operator*=(const mds::vec3<U> &other)
{
    this->r *= other.r;
    this->g *= other.g;
    this->b *= other.b;
    return *this;
}

template<typename T>
template<typename U>
mds::vec3<T> &mds::vec3<T>::operator/=(const mds::vec3<U> &other)
{
    this->r /= other.r;
    this->g /= other.g;
    this->b /= other.b;
    return *this;
}

template<typename T, typename U>
mds::vec3<decltype(T{} + U{})> operator+(const mds::vec3<T>& lhs, const mds::vec3<U>& rhs)
{
    return mds::vec3<decltype(T{} + U{})>{lhs} += rhs;
}

template<typename T, typename U>
mds::vec3<decltype(T{} - U{})> operator-(const mds::vec3<T>& lhs, const mds::vec3<U>& rhs)
{
    return mds::vec3<decltype(T{} - U{})>{lhs} -= rhs;
}

template<typename T, typename U>
mds::vec3<decltype(T{} * U{})> operator*(const mds::vec3<T>& lhs, const mds::vec3<U>& rhs)
{
    return mds::vec3<decltype(T{} * U{})>{lhs} *= rhs;
}

template<typename T, typename U>
mds::vec3<decltype(T{} / U{})> operator/(const mds::vec3<T>& lhs, const mds::vec3<U>& rhs)
{
    return mds::vec3<decltype(T{} / U{})>{lhs} /= rhs;
}

template<typename T, typename U>
bool operator==(const mds::vec3<T>& lhs, const mds::vec3<U>& rhs)
{
    return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b;
}

template<typename T, typename U>
bool operator!=(const mds::vec3<T>& lhs, const mds::vec3<U>& rhs)
{
    return !(lhs == rhs);
}

template<typename T>
mds::vec3<T> mds::abs(mds::vec3<T> vec)
{
    vec.r = std::abs(vec.r);
    vec.g = std::abs(vec.g);
    vec.b = std::abs(vec.b);
    return vec;
}


#endif //MDS_VEC3_H
