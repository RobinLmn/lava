#pragma once
#include <core/System.hpp>

namespace lava
{
    class RigidBodySystem : public System
    {
    public:
        RigidBodySystem( entt::registry* );
        
    public:
        auto update( double ) -> void override;
    };
}
