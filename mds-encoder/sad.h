//
// Created by oshikuru on 20. 10. 2020..
//

#ifndef MDS_ENCODER_SAD_H
#define MDS_ENCODER_SAD_H

#include <cstdint>
#include <mds-core/block.h>
#include <mds-core/blockiterator.h>

namespace mds::encoder
{
    template<uint8_t BlockWidth = 8, uint8_t BlockHeight = 8>
    uint16_t sad(const blocks3 <BlockWidth, BlockHeight> &lhs, const blocks3 <BlockWidth, BlockHeight> &rhs)
    {
        vec256<uint16_t> sum[3];
        constexpr int size = (BlockWidth * BlockHeight) / NumOfElements<int16_t>;
        for (int i = 0; i < size; ++i)
        {
            sum[0] += mds::abs(lhs.r[i] - rhs.r[i]);
            sum[1] += mds::abs(lhs.g[i] - rhs.g[i]);
            sum[2] += mds::abs(lhs.b[i] - rhs.b[i]);
        }
        return mds::sum(sum[0]) + mds::sum(sum[1]) + mds::sum(sum[2]);
    }

    template<uint8_t BlockWidth = 8, uint8_t BlockHeight = 8>
    void
    sad(const block_iterator <BlockWidth, BlockHeight> &ref, const block_iterator <BlockWidth, BlockHeight> *blocks,
        uint16_t *results, uint8_t count)
    {
        vec256<uint16_t> sum[count * 3];
        constexpr int size = (BlockWidth * BlockHeight) / NumOfElements<int16_t>;
        for (int i = 0; i < size; ++i)
        {
            for (uint8_t j = 0; j < count; ++j)
            {
                sum[j * 3] += mds::abs(ref->r[i] - blocks[j]->r[i]);
                sum[j * 3 + 1] += mds::abs(ref->g[i] - blocks[j]->g[i]);
                sum[j * 3 + 2] += mds::abs(ref->b[i] - blocks[j]->b[i]);
            }
        }

        for (uint8_t j = 0; j < count; ++j)
        {
            results[j] = mds::sum(sum[j * 3]) +
                         mds::sum(sum[j * 3 + 1]) +
                         mds::sum(sum[j * 3 + 2]);
        }
    }
}

#endif //MDS_ENCODER_SAD_H
