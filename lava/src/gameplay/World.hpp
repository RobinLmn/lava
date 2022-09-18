#pragma once
#include <core/System.hpp>
#include <gameplay/Scene.hpp>
#include <entt/entity/registry.hpp>

namespace lava
{
    class World final
    {
    public:
        World();
        ~World();
        
    public:
        auto begin() -> void;
        auto update( double ) -> void;
        auto end() -> void;
        
        [[nodiscard]]
        auto getRegistry() const -> const entt::registry* { return registry; };
        
    private:
        entt::registry* registry;
        Scene* scene;
        std::array<System*, 3> systems;
    };
}
