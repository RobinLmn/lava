#pragma once

#include <simd/simd.h>

#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>

namespace lava
{
    struct Camera
    {
        float far;
        float near;
        float fov;
        float aspect;
        
        simd::float4x4 viewProjection;
        bool isMainCamera;
        
        MTL::Buffer* cameraBuffer;
    };
}
