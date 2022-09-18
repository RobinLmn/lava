#pragma once
#include <core/System.hpp>
#include <gameplay/components/Mesh.hpp>

namespace lava
{
    class MeshLoadingSystem final : public System
    {
    public:
        MeshLoadingSystem( entt::registry* );
    
    public:
        auto begin() -> void override;
        
    private:
        auto loadMesh( StaticMesh*, const char* ) -> void;
    };
}
