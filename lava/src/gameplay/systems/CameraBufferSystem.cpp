#include "CameraBufferSystem.hpp"

#include <core/Engine.hpp>
#include <util/Math.hpp>

#include <gameplay/components/TransformComponent.hpp>
#include <gameplay/components/CameraComponent.hpp>

namespace lava
{
    CameraBufferSystem::CameraBufferSystem( entt::registry* registry )
        : System( registry )
    {
    }

    auto CameraBufferSystem::begin() -> void
    {
        auto entities = registry->view<const CameraComponent>().each();
        for (auto [entity, camera] : entities)
        {
            auto& buffer = registry->emplace<CameraBufferComponent>( entity );
            buffer.cameraBuffer = Engine::getDevice()->newBuffer( sizeof( simd::float4x4 ), MTL::ResourceStorageModeManaged );
        }
    }

    auto CameraBufferSystem::update( double dt ) -> void
    {
        auto entities = registry->view<CameraComponent, CameraBufferComponent, const TransformComponent>().each();
        for (auto [entity, camera, buffer, transform] : entities)
        {
            const auto projection = math::perspective( math::degreesToRadian( camera.fov ), camera.aspect, camera.near, camera.far);
            const auto view = transform.model;
            camera.viewProjection = projection * view;
            
            auto viewProjectionBufferData = reinterpret_cast<simd::float4x4*>( buffer.cameraBuffer->contents() );
            *viewProjectionBufferData = camera.viewProjection;
            
            buffer.cameraBuffer->didModifyRange( NS::Range::Make( 0, sizeof( simd::float4x4 ) ) );
        }
    }
}
