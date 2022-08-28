#include "World.hpp"

#include <util/Math.hpp>

#include <gameplay/components/Mesh.hpp>
#include <gameplay/components/Camera.hpp>
#include <gameplay/components/Transform.hpp>
#include <gameplay/components/RigidBody.hpp>

#include <gameplay/systems/CameraSystem.hpp>
#include <gameplay/systems/MeshSystem.hpp>
#include <gameplay/systems/TransformSystem.hpp>
#include <gameplay/systems/RigidBodySystem.hpp>

namespace
{
    using namespace lava;

    auto makeScene( entt::registry* registry )
    {
        const auto entity = registry->create();
        
        auto& mesh = registry->emplace<Mesh>( entity );
        MeshSystem::loadMesh( &mesh, "/Users/robinleman/GitHub/lava/lava/content/models/cube.obj" );
        
        auto& transform = registry->emplace<Transform>( entity );
        transform.position = {0.f, 0.f, 0.f};
        transform.scale = {0.01f, 0.01f, 0.01f};
        transform.rotation = {-10.f, -10.f, -10.f};
        
        auto& rb = registry->emplace<RigidBody>( entity );
        rb.mass = 1.0f;
        rb.force = {0.f, -0.001f, 0.f};
        
        const auto camera = registry->create();
        
        auto& cameraTransform = registry->emplace<Transform>( camera );
        cameraTransform.position = {0.f, 0.f, -10.f};
        cameraTransform.scale = {1.f, 1.f, 1.f};
        cameraTransform.rotation = {0.f, 0.f, 0.f};
        
        auto& cameraComponent = registry->emplace<Camera>( camera );
        cameraComponent.isMainCamera = true;
        cameraComponent.near = 0.03f;
        cameraComponent.far = 500.f;
        cameraComponent.aspect = 1.f;
        cameraComponent.fov = math::degreesToRadian( 45.f );
    }
}
namespace lava
{
    World::World()
    {
        registry = new entt::registry();
        
        systems =
        {
            new MeshSystem( registry ),
            new TransformSystem( registry ),
            new CameraSystem( registry ),
            new RigidBodySystem( registry )
        };
        
        makeScene( registry );
    }

    auto World::begin() -> void
    {
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
