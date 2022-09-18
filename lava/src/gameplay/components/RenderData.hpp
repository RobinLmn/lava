#pragma once

#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>

#include <simd/simd.h>

namespace lava
{
    struct ObjectData
    {
        simd::float4x4 modelMatrix;
        simd::float4x4 normalMatrix;
    };

    struct UniformData
    {
        float ambientStrength;
        float diffuseStrength;
        simd::float3 lightColor;
        simd::float3 lightPosition;
        simd::float4x4 viewProjection;
    };

    struct ObjectBuffer
    {
        MTL::Buffer* buffer;
    };

    struct UniformBuffer
    {
        MTL::Buffer* buffer;
    };

    struct MeshBuffer
    {
        MTL::Buffer* vertices;
        MTL::Buffer* indices;
    };
}
