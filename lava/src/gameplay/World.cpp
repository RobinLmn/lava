#include "World.hpp"
#include <gameplay/Scene.hpp>

#include <gameplay/systems/MeshLoadingSystem.hpp>
#include <gameplay/systems/CameraControlSystem.hpp>
#include <gameplay/systems/BufferSystem.hpp>

namespace lava
{
    World::World()
    {
        registry = new entt::registry();
        scene = new Scene();
        
        systems =
        {
            new CameraControlSystem( registry ),
            new MeshLoadingSystem( registry ),
            new BufferSystem( registry ),
        };
    }

    auto World::begin() -> void
    {
        scene->instantiate( registry );
        for (auto system: systems)
        {
            system->begin();
        }
    }

    auto World::update( double deltaTime ) -> void
    {
        for (auto system: systems)
        {
            system->update( deltaTime );
        }
    }

    auto World::end() -> void
    {
        for (auto system: systems)
        {
            system->end();
        }
    }

    World::~World()
    {
        delete registry;
    }
}
