#pragma once
#include <core/System.hpp>

namespace lava
{
    class CameraControlSystem final : public System
    {
    public:
        CameraControlSystem( entt::registry* );
        
    public:
        auto update( double ) -> void override;
    };
}
