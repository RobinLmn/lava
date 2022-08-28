#pragma once

#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>

#include <renderer/Renderer.hpp>
#include <gameplay/World.hpp>

namespace lava
{
    class View final
    {
    private:
        class ViewDelegate final : public MTK::ViewDelegate
        {
        public:
            ViewDelegate( MTL::Device*, const World* );
            virtual ~ViewDelegate();
            
        public:
            auto drawInMTKView( MTK::View* ) -> void override;
            
        private:
            MTL::CommandQueue* commandQueue;
            Renderer* renderer;
            MTL::Device* device;
            const World* world;
        };
        
    public:
        View( const CGRect&, MTL::Device*, const World* );
        ~View();
        
    public:
        [[nodiscard]]
        auto getView() const -> MTK::View* { return view; };
        
    private:
        MTK::View* view;
        ViewDelegate* viewDelegate;
    };
}
