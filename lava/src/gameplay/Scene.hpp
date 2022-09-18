#pragma once
#include <entt/entity/registry.hpp>

namespace lava
{
    class Scene final
    {
    public:
        auto instantiate( entt::registry* ) -> void;
    };
}
