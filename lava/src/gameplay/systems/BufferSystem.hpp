#pragma once
#include <core/System.hpp>

namespace lava
{
    class BufferSystem final : public System
    {
    public:
        BufferSystem ( entt::registry* );
        
    public:
        auto begin() -> void override;
        auto update( double ) -> void override;
    };
}
