#include "TransformSystem.hpp"

#include <core/Engine.hpp>
#include <util/Math.hpp>
#include <gameplay/components/Transform.hpp>

namespace lava
{
    TransformSystem::TransformSystem( entt::registry* registry )
        : System( registry )
    {
    }

    auto TransformSystem::begin() -> void
    {
        auto entities = registry->view<Transform>().each();
        for (auto [entity, transform] : entities)
        {
            transform.model = math::translate( transform.position );
            math::scale( transform.model, transform.scale );
            math::rotate( transform.model, math::degreesToRadian( transform.rotation ) );
            
            const auto transformDataSize = sizeof( simd::float4x4 );
            
            transform.modelBuffer = Engine::get().getDevice()->newBuffer( transformDataSize, MTL::ResourceStorageModeManaged );
            auto* modelBufferData = reinterpret_cast<simd::float4x4*>( transform.modelBuffer->contents() );
            *modelBufferData = transform.model;
            
            transform.modelBuffer->didModifyRange( NS::Range::Make( 0, transformDataSize ) );
            
            

        }
    }
}
