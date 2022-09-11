#pragma once

#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>

#include <simd/simd.h>

namespace lava
{
    struct CameraComponent
    {
        bool isMainCamera;
        
        float far;
        float near;
        float fov;
        float aspect;
        
        float speed;
        float sensitivity;
        
        simd::float4x4 viewProjection;
    };

    struct CameraBufferComponent
    {
        MTL::Buffer* cameraBuffer;
    };
}
