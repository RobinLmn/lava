#pragma once

#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>

#include <gameplay/World.hpp>

namespace lava
{
    class Renderer final
    {
    public:
        Renderer( MTL::Device* );
        ~Renderer();
        
    public:
        auto draw( MTL::RenderCommandEncoder*, const World* ) -> void;
        
    private:
        auto buildShaders() -> void;
        auto buildDepthStencilStates() -> void;
        
    private:
        MTL::Library* library;
        MTL::RenderPipelineState* pipelineState;
        MTL::Device* device;
        MTL::DepthStencilState* depthStencilState;
    };
}
