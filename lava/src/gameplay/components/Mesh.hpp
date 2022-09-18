#pragma once

#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>
#include <vector>
#include <simd/simd.h>
#include <string>

namespace lava
{
    struct Vertex
    {
        simd::float3 position;
        simd::float3 normal;
        simd::float3 color;
    };

    struct StaticMesh
    {
        std::vector<Vertex> vertices;
        std::vector<uint16_t> indices;
    };

    struct MeshPath
    {
        std::string path;
    };
}
