#include "View.hpp"
#include "Engine.hpp"

namespace lava
{
    View::View( MTK::View* view, MTL::Device* device, const World* world )
        : world( world )
        , commandQueue( device->newCommandQueue() )
        , renderer( new Renderer( device ) )
    {
        view->setColorPixelFormat( MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB );
        view->setClearColor( MTL::ClearColor::Make( 0.53, 0.81, 0.98, 1.0 ) );
        
        view->setDepthStencilPixelFormat( MTL::PixelFormat::PixelFormatDepth16Unorm );
        view->setClearDepth( 1.0f );
    }

    View::~View()
    {
        commandQueue->release();
        delete renderer;
    }

    auto View::drawInMTKView( MTK::View* view) -> void
    {
        auto releasePool = NS::AutoreleasePool::alloc()->init();
        auto commandBuffer = commandQueue->commandBuffer();
        auto encoder = commandBuffer->renderCommandEncoder( view->currentRenderPassDescriptor() );
        
        Engine::get().update();
        renderer->draw( encoder, world );

        encoder->endEncoding();
        
        commandBuffer->presentDrawable( view->currentDrawable() );
        commandBuffer->commit();
        
        releasePool->release();
    }
}
