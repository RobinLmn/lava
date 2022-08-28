#pragma once
#include <entt/entity/registry.hpp>

namespace lava
{
    class System
    {
    public:
        System( entt::registry* );
        virtual ~System();
        
    public:
        virtual auto begin() -> void;
        virtual auto update( double ) -> void;
        virtual auto end() -> void;
        
    protected:
        entt::registry* registry;
    };
}
