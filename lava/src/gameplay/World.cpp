#include "World.hpp"

#include <util/Math.hpp>

#include <gameplay/components/Mesh.hpp>
#include <gameplay/components/Camera.hpp>
#include <gameplay/components/Transform.hpp>

#include <gameplay/systems/CameraSystem.hpp>
#include <gameplay/systems/MeshSystem.hpp>
#include <gameplay/systems/TransformSystem.hpp>

namespace lava
{
    auto World::initialize() -> void
    {
        registry = new entt::registry();
        
        const auto entity = registry->create();
        
        auto& mesh = registry->emplace<Mesh>( entity );
        MeshSystem::loadMesh( &mesh, "/Users/robinleman/GitHub/lava/lava/content/models/cube.obj" );
        
        auto& transform = registry->emplace<Transform>( entity );
        transform.position = {0.f, 0.f, -5.f};
        transform.scale = {0.01f, 0.01f, 0.01f};
        transform.rotation = {10.f, 10.f, 10.f};
        
        const auto camera = registry->create();
        
        auto& cameraTransform = registry->emplace<Transform>( camera );
        cameraTransform.position = {0.f, 0.f, 0.f};
        cameraTransform.scale = {1.f, 1.f, 1.f};
        cameraTransform.rotation = {0.f, 0.f, 0.f};
        
        auto& cameraComponent = registry->emplace<Camera>( camera );
        cameraComponent.isMainCamera = true;
        cameraComponent.near = 0.03f;
        cameraComponent.far = 500.f;
        cameraComponent.aspect = 1.f;
        cameraComponent.fov = math::degreesToRadian( 45.f );
        
        TransformSystem transformSys{ registry };
        transformSys.begin();
        
        MeshSystem meshSys{ registry };
        meshSys.begin();
        
        CameraSystem camSys{ registry };
        camSys.begin();
    }

    World::~World()
    {
        delete registry;
    }
}
