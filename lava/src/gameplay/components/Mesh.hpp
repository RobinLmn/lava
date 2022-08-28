#pragma once

#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>
#include <vector>
#include <simd/simd.h>

namespace lava
{
    struct Vertex
    {
        simd::float3 position;
        simd::float3 normal;
        simd::float3 color;
    };

    struct Mesh
    {
        std::vector<Vertex> vertices;
        std::vector<uint16_t> indices;
        
        MTL::Buffer* vertexBuffer;
        MTL::Buffer* indexBuffer;
    };
}
