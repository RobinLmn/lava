#pragma once
#include <core/System.hpp>
#include <gameplay/components/MeshComponent.hpp>

namespace lava
{
    class MeshBufferSystem final : public System
    {
    public:
        MeshBufferSystem( entt::registry* );
    
    public:
        auto begin() -> void override;
        
    private:
        auto loadMesh( StaticMeshComponent*, const char* ) -> void;
    };
}
