#pragma once

#include <simd/simd.h>
#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>

namespace lava
{
    struct Transform
    {
        simd::float3 position;
        simd::float3 scale;
        simd::float3 rotation;
    };
}
