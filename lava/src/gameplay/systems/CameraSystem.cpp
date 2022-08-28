#include "CameraSystem.hpp"

#include <core/Engine.hpp>
#include <util/Math.hpp>

#include <gameplay/components/Camera.hpp>
#include <gameplay/components/Transform.hpp>

namespace lava
{
    CameraSystem::CameraSystem( entt::registry* registry )
        : System( registry )
    {
    }

    auto CameraSystem::update( double ) -> void
    {
        auto entities = registry->view<Camera, Transform>().each();
        for (auto [entity, camera, transform] : entities)
        {
            const auto projection = math::perspective( math::degreesToRadian( camera.fov ), camera.aspect, camera.near, camera.far);
            const auto view = transform.model;
            camera.viewProjection = projection * view;
            
            const auto cameraDataSize = sizeof( simd::float4x4 );
            
            camera.cameraBuffer = Engine::get().getDevice()->newBuffer( cameraDataSize, MTL::ResourceStorageModeManaged );
            
            auto viewProjectionBufferData = reinterpret_cast<simd::float4x4*>( camera.cameraBuffer->contents() );
            *viewProjectionBufferData = camera.viewProjection;
            camera.cameraBuffer->didModifyRange( NS::Range::Make( 0, cameraDataSize ) );
        }
    }
}
