//
// Created by oshikuru on 23. 10. 2020..
//

#ifndef MDS_BLOCKITERATOR_H
#define MDS_BLOCKITERATOR_H

#include "block.h"
#include "rgbimage.h"
#include <limits>
#include <memory>
#include <optional>

namespace mds
{
    template<uint8_t Width, uint8_t Height>
    union blocks3
    {
        blocks3() : v{{},{},{}}
        {}

        block<int16_t, Width, Height> v[3];
        struct
        {
            block<int16_t, Width, Height> r, g, b;
        };
        struct
        {
            block<int16_t, Width, Height> x, y, z;
        };
        struct
        {
            block<int16_t, Width, Height> s, t, p;
        };
    };

    using blocks3x8x8 = blocks3<8, 8>;
    using blocks3x16x16 = blocks3<16, 16>;

    template<uint8_t Width, uint8_t Height>
    struct block_iterator
    {
        static constexpr size_t invalid_pos = std::numeric_limits<size_t>::max();

        block_iterator();
        explicit block_iterator(const rgb_image &img);
        block_iterator(const rgb_image &img, size_t block_idx);
        block_iterator(const rgb_image &img, const vec2<size_t> &pixel);
        block_iterator(const block_iterator<Width, Height> &other, const rgb_image &img);
        block_iterator(const block_iterator<Width, Height> &other);
        block_iterator(block_iterator<Width, Height> &&other) noexcept;

        block_iterator<Width, Height> &operator=(const block_iterator<Width, Height> &other);
        block_iterator<Width, Height> &operator=(block_iterator<Width, Height> &&other) noexcept;

        explicit operator bool() const;

        block_iterator<Width, Height> operator++(int)
        {
            auto old_pos = pos_;
            *this += 1;
            return {img_, old_pos};
        }

        block_iterator<Width, Height> &operator++()
        {
            *this += 1;
            return *this;
        }

        block_iterator<Width, Height> operator--(int)
        {
            auto old_pos = pos_;
            *this -= 1;
            return {img_, old_pos};
        }

        block_iterator<Width, Height> &operator--()
        {
            *this -= 1;
            return *this;
        }

        block_iterator<Width, Height> &operator+=(size_t count);
        block_iterator<Width, Height> &operator-=(size_t count);

        block_iterator<Width, Height> &operator+=(const vec2<size_t> &direction)
        {
            cache_.reset();
            pos_ += direction.y * img_->width() + direction.x;
            return *this;
        }

        block_iterator<Width, Height> &operator-=(const vec2<size_t> &direction)
        {
            cache_.reset();
            pos_ -= direction.y * img_->width() + direction.x;
            return *this;
        }

        blocks3<Width, Height> &operator*();
        const blocks3<Width, Height> &operator*() const;

        blocks3<Width, Height> *operator->();
        const blocks3<Width, Height> *operator->() const;

        friend bool
        operator==(const mds::block_iterator<Width, Height> &lhs, const mds::block_iterator<Width, Height> &rhs)
        { return lhs.img_ == rhs.img_ && lhs.pos_ == rhs.pos_; }

        friend bool
        operator!=(const mds::block_iterator<Width, Height> &lhs, const mds::block_iterator<Width, Height> &rhs)
        { return !(lhs == rhs); }

        friend bool
        operator<(const mds::block_iterator<Width, Height> &lhs, const mds::block_iterator<Width, Height> &rhs)
        { return lhs.img_ == rhs.img_ && lhs.pos_ < rhs.pos_; }

        friend bool
        operator>(const mds::block_iterator<Width, Height> &lhs, const mds::block_iterator<Width, Height> &rhs)
        { return lhs.img_ == rhs.img_ && lhs.pos_ > rhs.pos_; }

        friend bool
        operator<=(const mds::block_iterator<Width, Height> &lhs, const mds::block_iterator<Width, Height> &rhs)
        { return lhs.img_ == rhs.img_ && lhs.pos_ <= rhs.pos_; }

        friend bool
        operator>=(const mds::block_iterator<Width, Height> &lhs, const mds::block_iterator<Width, Height> &rhs)
        { return lhs.img_ == rhs.img_ && lhs.pos_ >= rhs.pos_; }

        friend vec2<std::make_signed<size_t>::type>
        operator-(const mds::block_iterator<Width, Height> &lhs, const mds::block_iterator<Width, Height> &rhs)
        {
            vec2<std::make_signed<size_t>::type> p1 = {
                    std::make_signed<size_t>::type(lhs.pos_ % lhs.img_->width()),
                    std::make_signed<size_t>::type(lhs.pos_ / lhs.img_->width())
            };
            vec2<std::make_signed<size_t>::type> p2 = {
                    std::make_signed<size_t>::type(rhs.pos_ % rhs.img_->width()),
                    std::make_signed<size_t>::type(rhs.pos_ / rhs.img_->width())
            };
            return p1 - p2;
        }

    private:
        const rgb_image *img_;
        size_t pos_{};
        std::optional<blocks3<Width, Height>> cache_;
    };

    template<uint8_t Width, uint8_t Height>
    block_iterator<Width, Height>::block_iterator() : img_(nullptr), pos_(invalid_pos)
    {

    }

    template<uint8_t Width, uint8_t Height>
    block_iterator<Width, Height>::block_iterator(const rgb_image &img) : img_(&img)
    {
    }

    template<uint8_t Width, uint8_t Height>
    block_iterator<Width, Height>::block_iterator(const rgb_image &img, size_t block_idx)  : img_(&img)
    {
        *this += block_idx;
    }

    template<uint8_t Width, uint8_t Height>
    block_iterator<Width, Height>::block_iterator(const rgb_image &img, const vec2<size_t> &pixel) : img_(&img)
    {
        *this += pixel;
    }

    template<uint8_t Width, uint8_t Height>
    block_iterator<Width, Height>::block_iterator(const block_iterator<Width, Height> &other, const rgb_image &img) :
            pos_(other.pos_), img_(&img)
    {

    }

    template<uint8_t Width, uint8_t Height>
    block_iterator<Width, Height>::block_iterator(const block_iterator<Width, Height> &other) :
            img_(other.img_), pos_(other.pos_)
    {
    }

    template<uint8_t Width, uint8_t Height>
    block_iterator<Width, Height>::block_iterator(block_iterator<Width, Height> &&other) noexcept :
            img_(other.img_), pos_(other.pos_), cache_(std::move(other.cache_))
    {
    }

    template<uint8_t Width, uint8_t Height>
    block_iterator<Width, Height> &block_iterator<Width, Height>::operator=(const block_iterator<Width, Height> &other)
    {
        img_ = other.img_;
        pos_ = other.pos_;
        return *this;
    }

    template<uint8_t Width, uint8_t Height>
    block_iterator<Width, Height> &
    block_iterator<Width, Height>::operator=(block_iterator<Width, Height> &&other) noexcept
    {
        img_ = other.img_;
        pos_ = other.pos_;
        cache_ = std::move(other.cache_);
        return *this;
    }

    template<uint8_t Width, uint8_t Height>
    block_iterator<Width, Height>::operator bool() const
    {
        size_t x = pos_ % img_->width();
        size_t y = pos_ / img_->width();
        return img_->width() - Width >= x &&
               img_->height() - Height >= y &&
               pos_ != invalid_pos;
    }

    template<uint8_t Width, uint8_t Height>
    blocks3<Width, Height> &block_iterator<Width, Height>::operator*()
    {
        if (cache_)
            return *cache_;

        cache_ = blocks3<Width, Height>();
        for (uint8_t i = 0; i < Height; ++i)
        {
            for (uint8_t j = 0; j < Width; ++j)
            {
                cache_->r[{i, j}] = (*img_)[pos_ + i * img_->width() + j].r;
                cache_->g[{i, j}] = (*img_)[pos_ + i * img_->width() + j].g;
                cache_->b[{i, j}] = (*img_)[pos_ + i * img_->width() + j].b;
            }
        }
        return *cache_;
    }

    template<uint8_t Width, uint8_t Height>
    const blocks3<Width, Height> &block_iterator<Width, Height>::operator*() const
    {
        return const_cast<block_iterator<Width, Height> *>(this)->operator*();
    }

    template<uint8_t Width, uint8_t Height>
    blocks3<Width, Height> *block_iterator<Width, Height>::operator->()
    {
        return &this->operator*();
    }

    template<uint8_t Width, uint8_t Height>
    const mds::blocks3<Width, Height> *mds::block_iterator<Width, Height>::operator->() const
    {
        return &this->operator*();
    }

    template<uint8_t Width, uint8_t Height>
    block_iterator<Width, Height> &block_iterator<Width, Height>::operator+=(size_t count)
    {
        cache_.reset();
        size_t new_pos =
                (pos_ / img_->width() + ((pos_ + Width * count) / img_->width() - pos_ / img_->width()) * Height) // y
                * img_->width() +
                (pos_ + Width * count) % img_->width(); // x
        pos_ = new_pos < pos_ ? invalid_pos : new_pos;
        return *this;
    }

    template<uint8_t Width, uint8_t Height>
    block_iterator<Width, Height> &block_iterator<Width, Height>::operator-=(size_t count)
    {
        cache_.reset();
        size_t new_pos =
                (pos_ / img_->width() - (pos_ / img_->width() - (pos_ - Width * count) / img_->width()) * Height) // y
                * img_->width() +
                (pos_ - Width * count) % img_->width(); // x
        pos_ = new_pos > pos_ ? invalid_pos : new_pos;
        return *this;
    }

    using block_iterator8x8 = block_iterator<8, 8>;
    using block_iterator16x16 = block_iterator<16, 16>;
}

template<uint8_t Width, uint8_t Height>
mds::block_iterator<Width, Height> operator+(mds::block_iterator<Width, Height> lhs, size_t count)
{
    return lhs += count;
}

template<uint8_t Width, uint8_t Height>
mds::block_iterator<Width, Height> operator-(mds::block_iterator<Width, Height> lhs, size_t count)
{
    return lhs -= count;
}

template<uint8_t Width, uint8_t Height>
mds::block_iterator<Width, Height> operator+(mds::block_iterator<Width, Height> lhs, const mds::vec2<size_t> &direction)
{
    return lhs += direction;
}

template<uint8_t Width, uint8_t Height>
mds::block_iterator<Width, Height> operator-(mds::block_iterator<Width, Height> lhs, const mds::vec2<size_t> &direction)
{
    return lhs -= direction;
}

#endif //MDS_BLOCKITERATOR_H
