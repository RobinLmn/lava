#pragma once

#include <simd/simd.h>

namespace lava
{
    struct Light
    {
        float ambientStrength;
        float diffuseStrength;
        simd::float3 color;
    };
}
