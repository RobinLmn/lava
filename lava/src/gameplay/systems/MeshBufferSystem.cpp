#include "MeshBufferSystem.hpp"

#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>
#include <tinyobjloader/tiny_obj_loader.h>
#include <core/Engine.hpp>
#include <iostream>

#include <gameplay/components/MeshComponent.hpp>

namespace lava
{
    MeshBufferSystem::MeshBufferSystem( entt::registry* registry )
            : System(registry)
    {
    }

    auto MeshBufferSystem::begin() -> void
    {
        const auto entitiesToGenerate = registry->view<MeshFromPathComponent>().each();
        for (auto [entity, pathComponent] : entitiesToGenerate)
        {
            auto& mesh = registry->emplace<StaticMeshComponent>(entity);
            loadMesh( &mesh, pathComponent.path.c_str() );
        }
        
        const auto entities = registry->view<StaticMeshComponent>().each();
        for (auto [entity, mesh] : entities)
        {
            auto& buffer = registry->emplace<MeshBufferComponent>( entity );
            
            const auto vertexDataSize = mesh.vertices.size() * sizeof( Vertex );
            const auto indexDataSize = mesh.indices.size() * sizeof( uint16_t );
            
            buffer.vertexBuffer = Engine::getDevice()->newBuffer( vertexDataSize, MTL::ResourceStorageModeManaged );
            buffer.indexBuffer = Engine::getDevice()->newBuffer( indexDataSize, MTL::ResourceStorageModeManaged );
            
            memcpy( buffer.vertexBuffer->contents(), mesh.vertices.data(), vertexDataSize );
            memcpy( buffer.indexBuffer->contents(), mesh.indices.data(), indexDataSize );

            buffer.vertexBuffer->didModifyRange( NS::Range::Make( 0, buffer.vertexBuffer->length() ) );
            buffer.indexBuffer->didModifyRange( NS::Range::Make( 0, buffer.indexBuffer->length() ) );
        }
    }

    auto MeshBufferSystem::loadMesh( StaticMeshComponent* mesh, const char * path) -> void
    {
        tinyobj::ObjReaderConfig readerConfig;
        readerConfig.mtl_search_path = "/Users/robinleman/GitHub/lava/lava/content/models";
        tinyobj::ObjReader reader;

        if (!reader.ParseFromFile( path, readerConfig ))
        {
            if (!reader.Error().empty())
            {
                std::cerr << "TinyObjReader: " << reader.Error();
            }
            exit(1);
        }

        if (!reader.Warning().empty())
        {
            std::cout << "TinyObjReader: " << reader.Warning();
        }

        auto& attrib = reader.GetAttrib();
        auto& shapes = reader.GetShapes();
        auto& materials = reader.GetMaterials();

        size_t i = 0;
        for (size_t s = 0; s < shapes.size(); s++)
        {
            size_t index_offset = 0;
            for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
            {
                size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);
                size_t materialID = shapes[s].mesh.material_ids[f];

                // Loop over vertices in the face.
                for (size_t v = 0; v < fv; v++)
                {
                    tinyobj::index_t idx = shapes[s].mesh.indices[index_offset];
                    
                    // position
                    tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
                    tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
                    tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];

                    tinyobj::real_t nx = 0;
                    tinyobj::real_t ny = 0;
                    tinyobj::real_t nz = 0;

                    if (idx.normal_index >= 0)
                    {
                        nx = attrib.normals[3 * idx.normal_index +0];
                        ny = attrib.normals[3 * idx.normal_index +1];
                        nz = attrib.normals[3 * idx.normal_index +2];
                    }

                    Vertex vertex;
                    vertex.position = {vx, vy, vz};
                    vertex.normal = {nx, ny, nz};
                    
                    auto color = materials[materialID].diffuse;
                    vertex.color = { 0.9f, 0.9f, 0.9f } ;

                    mesh->vertices.emplace_back(vertex);
                    mesh->indices.emplace_back(i);

                    index_offset++;
                    i++;
                }
            }
        }
    }
}
