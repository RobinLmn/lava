#include "MeshSystem.hpp"

#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>
#include <tinyobjloader/tiny_obj_loader.h>
#include <core/Engine.hpp>

namespace lava
{
    MeshSystem::MeshSystem( entt::registry* registry )
            : System(registry)
    {
    }

    auto MeshSystem::begin() -> void
    {
        const auto entities = registry->view<Mesh>().each();
        for (auto [entity, mesh] : entities)
        {
            const auto vertexDataSize = mesh.vertices.size() * sizeof( simd::float3 );
            const auto indexDataSize = mesh.indices.size() * sizeof( uint16_t );
            
            mesh.vertexBuffer = Engine::get().getDevice()->newBuffer( vertexDataSize, MTL::ResourceStorageModeManaged );
            mesh.indexBuffer = Engine::get().getDevice()->newBuffer( indexDataSize, MTL::ResourceStorageModeManaged );
            
            memcpy( mesh.vertexBuffer->contents(), mesh.vertices.data(), vertexDataSize );
            memcpy( mesh.indexBuffer->contents(), mesh.indices.data(), indexDataSize );

            mesh.vertexBuffer->didModifyRange( NS::Range::Make( 0, mesh.vertexBuffer->length() ) );
            mesh.indexBuffer->didModifyRange( NS::Range::Make( 0, mesh.indexBuffer->length() ) );
        }
    }

    auto MeshSystem::loadMesh( Mesh* mesh, const char * path) -> void
    {
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        
        tinyobj::LoadObj( &attrib, &shapes, &materials, nullptr, nullptr, path );
        
        size_t i = 0;
        for (size_t s = 0; s < shapes.size(); s++)
        {
          size_t index_offset = 0;
          for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
          {
            size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);
            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++)
            {
                // position
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                tinyobj::real_t vx = attrib.vertices[3*size_t(idx.vertex_index)+0];
                tinyobj::real_t vy = attrib.vertices[3*size_t(idx.vertex_index)+1];
                tinyobj::real_t vz = attrib.vertices[3*size_t(idx.vertex_index)+2];
                
                simd::float3 pos{vx, vy, vz};
                mesh->vertices.emplace_back(pos);
                mesh->indices.emplace_back(i);
                i++;
            }
            index_offset += fv;
          }
        }
    }
}
