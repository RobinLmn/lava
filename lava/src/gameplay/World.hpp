#pragma once

#include <entt/entity/registry.hpp>

namespace lava
{
    class World
    {
    public:
        ~World();
        
    public:
        auto initialize() -> void;
        
        [[nodiscard]]
        auto getRegistry() const -> const entt::registry* { return registry; };
        
    private:
        entt::registry* registry;
    };
}
