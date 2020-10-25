//
// Created by oshikuru on 24. 10. 2020..
//

#ifndef MDS_DECODER_H
#define MDS_DECODER_H

#include <vector>
#include <mds-core/rgbimage.h>
#include <mds-core/motionvector.h>

namespace mds::decoder
{
    rgb_image decode_motion_vector8x8(const rgb_image& referent_frame, const std::vector<motion_vector>& motions);
}


#endif //MDS_DECODER_H
