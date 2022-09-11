#pragma once

#include <simd/simd.h>
#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>

namespace lava
{
    struct TransformComponent
    {
        simd::float3 position;
        simd::float3 scale;
        simd::float3 rotation;
        
        simd::float4x4 model;
        MTL::Buffer* modelBuffer;
    };

    struct TransformBufferComponent
    {
        MTL::Buffer* modelBuffer;
    };
}
