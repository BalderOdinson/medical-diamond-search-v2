//
// Created by oshikuru on 24. 10. 2020..
//

#ifndef MDS_MOTIONVECTOR_H
#define MDS_MOTIONVECTOR_H

#include <string_view>
#include <vector>
#include "vec2.h"

namespace mds
{
    struct motion_vector
    {
        vec2uc block;
        vec2c direction;
    };

    void save(std::string_view filename, const std::vector<motion_vector> &motions);
    std::vector<motion_vector> load(std::string_view filename);
}


#endif //MDS_MOTIONVECTOR_H
