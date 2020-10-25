//
// Created by oshikuru on 21. 10. 2020..
//

#ifndef MDS_ENCODER_TESTS_VEC_H
#define MDS_ENCODER_TESTS_VEC_H

#include <cstdint>
#include <array>
#include <cstddef>
#include <numeric>
#include <cmath>

namespace mds
{
    template<typename Type>
    constexpr int NumOfElements = 32 / sizeof(Type);

    template<typename Type>
    struct alignas(32) vec256
    {
        vec256();
        vec256(Type value);
        vec256(const std::array<Type, NumOfElements<Type>>& values);
        template<typename OtherType>
        vec256(const vec256<OtherType>& other);

        Type& operator[](size_t index);
        const Type& operator[](size_t index) const;

        operator Type*();
        operator const Type*() const;

        template<typename OtherType>
        vec256& operator+=(const vec256<OtherType>& other);
        template<typename OtherType>
        vec256& operator-=(const vec256<OtherType>& other);
        template<typename OtherType>
        vec256& operator*=(const vec256<OtherType>& other);
        template<typename OtherType>
        vec256& operator/=(const vec256<OtherType>& other);


    private:
        Type data_[NumOfElements<Type>];
    };

    template<typename Type>
    vec256<Type>::vec256() : vec256(0)
    {
    }

    template<typename Type>
    vec256<Type>::vec256(Type value)
    {
        for (uint8_t i = 0; i < NumOfElements<Type>; ++i)
            data_[i] = value;
    }

    template<typename Type>
    template<typename OtherType>
    vec256<Type>::vec256(const vec256<OtherType> &other)
    {
        static_assert(NumOfElements<Type> == NumOfElements<OtherType>, "Cannot construct vec256 with types of different sizes");
        for (uint8_t i = 0; i < NumOfElements<Type>; ++i)
            data_[i] = other[i];
    }

    template<typename Type>
    vec256<Type>::vec256(const std::array<Type, NumOfElements<Type>> &values)
    {
        for (uint8_t i = 0; i < NumOfElements<Type>; ++i)
            data_[i] = values[i];
    }

    template<typename Type>
    vec256<Type>::operator Type *()
    {
        return data_;
    }

    template<typename Type>
    vec256<Type>::operator const Type *() const
    {
        return data_;
    }

    template<typename Type>
    Type &vec256<Type>::operator[](size_t index)
    {
        return data_[index];
    }

    template<typename Type>
    const Type &vec256<Type>::operator[](size_t index) const
    {
        return data_[index];
    }

    template<typename Type>
    template<typename OtherType>
    vec256<Type> &vec256<Type>::operator+=(const vec256<OtherType> &other)
    {
        static_assert(NumOfElements<Type> == NumOfElements<OtherType>, "Cannot construct vec256 with types of different sizes");
        for (uint8_t i = 0; i < NumOfElements<Type>; ++i)
            data_[i] += other[i];
        return *this;
    }

    template<typename Type>
    template<typename OtherType>
    vec256<Type> &vec256<Type>::operator-=(const vec256<OtherType> &other)
    {
        static_assert(NumOfElements<Type> == NumOfElements<OtherType>, "Cannot construct vec256 with types of different sizes");
        for (uint8_t i = 0; i < NumOfElements<Type>; ++i)
            data_[i] -= other[i];
        return *this;
    }

    template<typename Type>
    template<typename OtherType>
    vec256<Type> &vec256<Type>::operator*=(const vec256<OtherType> &other)
    {
        static_assert(NumOfElements<Type> == NumOfElements<OtherType>, "Cannot construct vec256 with types of different sizes");
        for (uint8_t i = 0; i < NumOfElements<Type>; ++i)
            data_[i] *= other[i];
        return *this;
    }

    template<typename Type>
    template<typename OtherType>
    vec256<Type> &vec256<Type>::operator/=(const vec256<OtherType> &other)
    {
        static_assert(NumOfElements<Type> == NumOfElements<OtherType>, "Cannot construct vec256 with types of different sizes");
        for (uint8_t i = 0; i < NumOfElements<Type>; ++i)
            data_[i] /= other[i];
        return *this;
    }

    template<typename Type>
    vec256<Type> abs(mds::vec256<Type> vec)
    {
        for (uint8_t i = 0; i < NumOfElements<Type>; ++i)
            vec[i] = std::abs(vec[i]);
        return vec;
    }

    template<typename Type>
    Type sum(const vec256<Type> &other)
    {
        return std::accumulate(&other[0], &other[NumOfElements<Type> - 1] + 1, Type(0));
    }

    template<class T, class U>
    struct unsigned_result_type {
        using type = typename std::conditional<(std::is_unsigned<T>::value), T, U>::type;
    };

    template<class T, class U>
    struct result_type {
        using r_type = decltype(T{} + U{});
        using type = typename std::conditional<(sizeof(r_type) > sizeof(T)), typename unsigned_result_type<T, U>::type, r_type>::type;
    };
}


template<typename Type1, typename Type2>
mds::vec256<typename mds::result_type<Type1, Type2>::type> operator+(const mds::vec256<Type1>& lhs, const mds::vec256<Type2>& rhs)
{
    return mds::vec256<typename mds::result_type<Type1, Type2>::type>{lhs} += rhs;
}

template<typename Type1, typename Type2>
mds::vec256<typename mds::result_type<Type1, Type2>::type> operator-(const mds::vec256<Type1>& lhs, const mds::vec256<Type2>& rhs)
{
    return mds::vec256<typename mds::result_type<Type1, Type2>::type>{lhs} -= rhs;
}

template<typename Type1, typename Type2>
mds::vec256<typename mds::result_type<Type1, Type2>::type> operator*(const mds::vec256<Type1>& lhs, const mds::vec256<Type2>& rhs)
{
    return mds::vec256<typename mds::result_type<Type1, Type2>::type>{lhs} *= rhs;
}

template<typename Type1, typename Type2>
mds::vec256<typename mds::result_type<Type1, Type2>::type> operator/(const mds::vec256<Type1>& lhs, const mds::vec256<Type2>& rhs)
{
    return mds::vec256<typename mds::result_type<Type1, Type2>::type>{lhs} /= rhs;
}

template<typename Type1, typename Type2>
bool operator==(const mds::vec256<Type1>& lhs, const mds::vec256<Type2>& rhs)
{
    static_assert(mds::NumOfElements<Type1> == mds::NumOfElements<Type2>, "Cannot construct vec256 with types of different sizes");
    bool r = true;
    for (uint8_t i = 0; i < mds::NumOfElements<Type1>; ++i)
        r &= lhs[i] == rhs[i];
    return r;
}

template<typename Type1, typename Type2>
bool operator!=(const mds::vec256<Type1>& lhs, const mds::vec256<Type2>& rhs)
{
    return !(lhs == rhs);
}


#endif //MDS_ENCODER_TESTS_VEC_H
