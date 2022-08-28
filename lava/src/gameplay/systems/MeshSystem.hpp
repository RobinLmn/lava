#pragma once

#include <gameplay/components/Mesh.hpp>
#include <core/System.hpp>

namespace lava
{
    class MeshSystem final : public System
    {
    public:
        MeshSystem( entt::registry* );
    
    public:
        static auto loadMesh( Mesh*, const char* ) -> void;
        auto begin() -> void override;
    };
}
