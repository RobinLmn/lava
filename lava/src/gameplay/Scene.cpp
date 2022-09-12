#include "Scene.hpp"

#include <gameplay/components/CameraComponent.hpp>
#include <gameplay/components/MeshComponent.hpp>
#include <gameplay/components/TransformComponent.hpp>

#include <util/Math.hpp>

namespace
{
    using namespace  lava;

    auto makeCube( entt::registry* registry, simd::float3 pos ) -> void
    {
        const auto entity = registry->create();
        
        auto& entityMesh = registry->emplace<MeshFromPathComponent>( entity );
        entityMesh.path = "/Users/robinleman/GitHub/lava/lava/content/models/cube.obj";
        
        auto& entityTransform = registry->emplace<TransformComponent>( entity );
        entityTransform.scale = {0.4f, 0.4f, 0.4f};
        entityTransform.position = pos - entityTransform.scale;
        entityTransform.rotation = {0.f, 0.f, 0.f};
    }

    auto makeCamera( entt::registry* registry )
    {
        const auto camera = registry->create();
        
        auto& cameraTransform = registry->emplace<TransformComponent>( camera );
        cameraTransform.position = {0.f, 0.f, -10.f};
        cameraTransform.scale = {1.f, 1.f, 1.f};
        cameraTransform.rotation = {0.f, 0.f, 0.f};
        
        auto& cameraComponent = registry->emplace<CameraComponent>( camera );
        cameraComponent.isMainCamera = true;
        cameraComponent.near = 0.03f;
        cameraComponent.far = 2000.f;
        cameraComponent.aspect = 1.f;
        cameraComponent.fov = math::degreesToRadian( 45.f );
        cameraComponent.speed = 10.f;
        cameraComponent.sensitivity = 1.f;
    }

    auto makeTurtle( entt::registry* registry )
    {
        const auto entity = registry->create();
        
        auto& entityMesh = registry->emplace<MeshFromPathComponent>( entity );
        entityMesh.path = "/Users/robinleman/GitHub/lava/lava/content/models/3DTurtle.obj";
        
        auto& entityTransform = registry->emplace<TransformComponent>( entity );
        entityTransform.position = {0.f, 0.f, 0.f};
        entityTransform.scale = {0.1f, 0.1f, 0.1f};
        entityTransform.rotation = {0.f, 180.f, 0.f};
    }

    auto makeChessKing( entt::registry* registry )
    {
        const auto entity = registry->create();
        
        auto& entityMesh = registry->emplace<MeshFromPathComponent>( entity );
        entityMesh.path = "/Users/robinleman/GitHub/lava/lava/content/models/ChessKing.obj";
        
        auto& entityTransform = registry->emplace<TransformComponent>( entity );
        entityTransform.position = {0.f, 0.f, 0.f};
        entityTransform.scale = {1.f, 1.f, 1.f};
        entityTransform.rotation = {0.f, 0.f, 0.f};
    }
}

namespace lava
{
    auto Scene::instantiate( entt::registry* registry ) -> void
    {
        makeCamera( registry );
        makeChessKing( registry );
    }
}
