#include "Scene.hpp"

#include <gameplay/components/Camera.hpp>
#include <gameplay/components/Mesh.hpp>
#include <gameplay/components/Transform.hpp>
#include <gameplay/components/Light.hpp>

#include <util/Math.hpp>

namespace
{
    using namespace  lava;

    auto makeCamera( entt::registry* registry )
    {
        const auto cameraEntity = registry->create();
        
        auto& cameraTransform = registry->emplace<Transform>( cameraEntity );
        cameraTransform.position = {0.f, -0.06f, -12.f};
        cameraTransform.scale = {1.f, 1.f, 1.f};
        cameraTransform.rotation = {0.f, 0.f, 0.f};
        
        auto& cameraComponent = registry->emplace<Camera>( cameraEntity );
        cameraComponent.isMainCamera = true;
        cameraComponent.near = 0.03f;
        cameraComponent.far = 100.f;
        cameraComponent.aspect = 1.f;
        cameraComponent.fov = math::degreesToRadian( 45.f );
        cameraComponent.speed = 0.1f;
        cameraComponent.sensitivity = 1.f;
    }

    auto makeChessKing( entt::registry* registry )
    {
        const auto entity = registry->create();
        
        auto& entityMesh = registry->emplace<MeshPath>( entity );
        entityMesh.path = "/Users/robinleman/GitHub/lava/lava/content/models/ChessKing.obj";
        
        auto& entityTransform = registry->emplace<Transform>( entity );
        entityTransform.position = {0.f, 0.f, 0.f};
        entityTransform.scale = {1.f, 1.f, 1.f};
        entityTransform.rotation = {0.f, 0.f, 0.f};
    }

    auto makeLight( entt::registry* registry )
    {
        const auto lightEntity = registry->create();
        
        auto& lightComponent = registry->emplace<Light>( lightEntity );
        lightComponent.color = {1.f, 1.f, 1.f};
        lightComponent.ambientStrength = 0.1f;
        lightComponent.diffuseStrength = 2.f;
        
        auto& lightTransform = registry->emplace<Transform>( lightEntity );
        lightTransform.position = {10.f, 10.f, 0.f};
    }
}

namespace lava
{
    auto Scene::instantiate( entt::registry* registry ) -> void
    {
        makeLight( registry );
        makeCamera( registry );
        makeChessKing( registry );
    }
}
