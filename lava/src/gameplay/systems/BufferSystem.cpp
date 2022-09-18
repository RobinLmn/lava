#include "BufferSystem.hpp"

#include <core/Engine.hpp>
#include <util/Math.hpp>

#include <gameplay/components/Transform.hpp>
#include <gameplay/components/Mesh.hpp>
#include <gameplay/components/Camera.hpp>
#include <gameplay/components/Light.hpp>
#include <gameplay/components/RenderData.hpp>

namespace
{
    template <class T>
    auto UpdateBuffer(MTL::Buffer* buffer, T data)
    {
        auto bufferData = reinterpret_cast<T*>( buffer->contents() );
        *bufferData = data;
        buffer->didModifyRange( NS::Range::Make( 0, sizeof( T ) ) );
    }
}

namespace lava
{
    BufferSystem::BufferSystem( entt::registry* registry )
        : System( registry )
    {
    }

    auto BufferSystem::begin() -> void
    {
        auto cameras = registry->view<const Camera>().each();
        for (auto [entity, camera] : cameras)
        {
            if ( !camera.isMainCamera ) continue;
            
            registry->emplace<UniformData>( entity );
            auto& uniformBuffer = registry->emplace<UniformBuffer>( entity );
            uniformBuffer.buffer = Engine::getDevice()->newBuffer( sizeof( UniformData ), MTL::ResourceStorageModeManaged );
            break;
        }
        
        auto meshes = registry->view<const StaticMesh>().each();
        for (auto [entity, mesh] : meshes)
        {
            auto& meshBuffer = registry->emplace<MeshBuffer>( entity );
            
            const auto vertexDataSize = mesh.vertices.size() * sizeof( Vertex );
            const auto indexDataSize = mesh.indices.size() * sizeof( uint16_t );
            
            meshBuffer.vertices = Engine::getDevice()->newBuffer( vertexDataSize, MTL::ResourceStorageModeManaged );
            meshBuffer.indices = Engine::getDevice()->newBuffer( indexDataSize, MTL::ResourceStorageModeManaged );
            
            memcpy( meshBuffer.vertices->contents(), mesh.vertices.data(), vertexDataSize );
            memcpy( meshBuffer.indices->contents(), mesh.indices.data(), indexDataSize );

            meshBuffer.vertices->didModifyRange( NS::Range::Make( 0, meshBuffer.vertices->length() ) );
            meshBuffer.indices->didModifyRange( NS::Range::Make( 0, meshBuffer.indices->length() ) );
        }
        
        auto transforms = registry->view<const Transform>().each();
        for (auto [entity, transform] : transforms)
        {
            registry->emplace<ObjectData>( entity );
            auto& objectBuffer = registry->emplace<ObjectBuffer>( entity );
            objectBuffer.buffer = Engine::get().getDevice()->newBuffer( sizeof( ObjectData ), MTL::ResourceStorageModeManaged );
        }
    }

    auto BufferSystem::update( double ) -> void
    {
        auto transforms = registry->view<const Transform, ObjectBuffer, ObjectData>().each();
        for (auto [entity, transform, buffer, data] : transforms)
        {
            data.modelMatrix = math::translate( transform.position );
            math::scale( data.modelMatrix, transform.scale );
            math::rotate( data.modelMatrix, math::degreesToRadian( transform.rotation ) );
            data.normalMatrix = simd::transpose( simd::inverse( data.modelMatrix ) );
            
            UpdateBuffer<ObjectData>(buffer.buffer, data);
        }
        
        auto cameras = registry->view<const Camera, const Transform, const ObjectData, UniformBuffer, UniformData>().each();
        for (auto [entity, camera, transform, objectData, buffer, uniformData] : cameras)
        {
            if (!camera.isMainCamera) continue;
            
            const auto projection = math::perspective( math::degreesToRadian( camera.fov ), camera.aspect, camera.near, camera.far);
            const auto view = objectData.modelMatrix;
            uniformData.viewProjection = projection * view;
            
            auto lights = registry->view<const Light, const Transform>().each();
            for (auto [entity, light, transform] : lights)
            {
                uniformData.lightColor = light.color;
                uniformData.lightPosition = transform.position;
                uniformData.ambientStrength = light.ambientStrength;
                uniformData.diffuseStrength = light.diffuseStrength;
            }
             
            UpdateBuffer<UniformData>(buffer.buffer, uniformData);
            
            break;
        }
    }
}
