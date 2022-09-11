#pragma once

#include <core/System.hpp>

namespace lava
{
    class TransformBufferSystem final : public System
    {
    public:
        TransformBufferSystem( entt::registry* );
        
    public:
        auto begin() -> void override;
        auto update( double ) -> void override;
    };
}
