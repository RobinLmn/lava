#include "RigidBodySystem.hpp"

#include <gameplay/components/RigidBody.hpp>
#include <gameplay/components/Transform.hpp>

namespace lava
{
    RigidBodySystem::RigidBodySystem( entt::registry* registry )
            : System(registry)
    {
    }

    auto RigidBodySystem::update( double dt ) -> void
    {
        const auto entities = registry->view<RigidBody, Transform>().each();
        for (auto [entity, rb, transform] : entities)
        {
        }
    }
}
