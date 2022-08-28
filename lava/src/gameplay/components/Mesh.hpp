#pragma once

#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>
#include <vector>
#include <simd/simd.h>

namespace lava
{
    struct Mesh
    {
        std::vector<simd::float3> vertices;
        std::vector<uint16_t> indices;
        
        MTL::Buffer* vertexBuffer;
        MTL::Buffer* indexBuffer;
    };
}
