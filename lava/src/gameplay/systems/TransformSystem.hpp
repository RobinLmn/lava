#pragma once

#include <core/System.hpp>

namespace lava
{
    class TransformSystem final : public System
    {
    public:
        TransformSystem( entt::registry* );
        
    public:
        auto update( double ) -> void override;
    };
}
