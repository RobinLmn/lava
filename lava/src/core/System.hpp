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
        virtual auto update() -> void;
        virtual auto shutdown() -> void;
        
    protected:
        entt::registry* registry;
    };
}
