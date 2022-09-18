#pragma once

#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>

#include <renderer/Renderer.hpp>
#include <gameplay/World.hpp>

namespace lava
{
    class View final : public MTK::ViewDelegate
    {
    public:
        View( MTK::View*, MTL::Device*, const World* );
        ~View();
        
    public:
        auto drawInMTKView( MTK::View* ) -> void override;
        
    private:
        MTL::CommandQueue* commandQueue;
        Renderer* renderer;
        const World* world;
    };
}
