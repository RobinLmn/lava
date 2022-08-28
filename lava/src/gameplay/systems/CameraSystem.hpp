#pragma once

#include <core/System.hpp>

namespace lava
{
    class CameraSystem final : public System
    {
    public:
        CameraSystem( entt::registry* );
        
    public:
        auto begin() -> void override;
    };
}
