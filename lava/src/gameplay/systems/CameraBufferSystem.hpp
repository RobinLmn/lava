#pragma once
#include <core/System.hpp>

namespace lava
{
    class CameraBufferSystem final : public System
    {
    public:
        CameraBufferSystem ( entt::registry* );
        
    public:
        auto begin() -> void override;
        auto update( double ) -> void override;
    };
}
