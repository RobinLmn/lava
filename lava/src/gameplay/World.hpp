#pragma once

#include <entt/entity/registry.hpp>
#include <core/System.hpp>

namespace lava
{
    class World
    {
    public:
        World();
        ~World();
        
    public:
        [[nodiscard]]
        auto getRegistry() const -> const entt::registry* { return registry; };
        
        auto begin() -> void;
        auto update( double ) -> void;
        auto end() -> void;
        
    private:
        entt::registry* registry;
        std::array<System*, 3> systems;
    };
}
