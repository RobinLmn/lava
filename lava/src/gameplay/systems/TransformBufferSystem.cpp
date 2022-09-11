#include "TransformBufferSystem.hpp"

#include <core/Engine.hpp>
#include <util/Math.hpp>

#include <gameplay/components/TransformComponent.hpp>

namespace lava
{
    TransformBufferSystem::TransformBufferSystem( entt::registry* registry )
        : System( registry )
    {
    }
    
    auto TransformBufferSystem::begin() -> void
    {
        auto entities = registry->view<TransformComponent>().each();
        for (auto [entity, transform] : entities)
        {
            registry->emplace<TransformBufferComponent>( entity );
        }
    }

    auto TransformBufferSystem::update( double ) -> void
    {
        auto entities = registry->view<TransformComponent, TransformBufferComponent>().each();
        for (auto [entity, transform, buffer] : entities)
        {
            transform.model = math::translate( transform.position );
            math::scale( transform.model, transform.scale );
            math::rotate( transform.model, math::degreesToRadian( transform.rotation ) );
            
            const auto transformDataSize = sizeof( simd::float4x4 );
            
            buffer.modelBuffer = Engine::get().getDevice()->newBuffer( transformDataSize, MTL::ResourceStorageModeManaged );
            auto* modelBufferData = reinterpret_cast<simd::float4x4*>( buffer.modelBuffer->contents() );
            *modelBufferData = transform.model;
            
            buffer.modelBuffer->didModifyRange( NS::Range::Make( 0, transformDataSize ) );
        }
    }
}
