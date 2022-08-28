#pragma once

#include <simd/simd.h>


namespace lava
{
    struct RigidBody
    {
        float mass;
        simd::float3 velocity;
        simd::float3 force;
    };
}
