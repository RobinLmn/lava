#include "View.hpp"

namespace lava
{
    View::View( const CGRect& frame, MTL::Device* device, const World* world )
    {
        view = MTK::View::alloc()->init( frame, device );

        view->setColorPixelFormat( MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB );
        view->setClearColor( MTL::ClearColor::Make( 0.1, 0.1, 0.1, 1.0 ) );
        
        view->setDepthStencilPixelFormat( MTL::PixelFormat::PixelFormatDepth16Unorm );
        view->setClearDepth( 1.0f );

        viewDelegate = new ViewDelegate( device, world );
        view->setDelegate( viewDelegate );
    }

    View::~View()
    {
        view->release();
        delete viewDelegate;
    }

    View::ViewDelegate::ViewDelegate( MTL::Device* device, const World* world )
        : device( device->retain() ),
          world( world )
    {
        commandQueue = device->newCommandQueue();
        renderer = new Renderer( device );
    }

    View::ViewDelegate::~ViewDelegate()
    {
        commandQueue->release();
        delete renderer;
    }

    auto View::ViewDelegate::drawInMTKView( MTK::View* view ) -> void
    {
        auto releasePool = NS::AutoreleasePool::alloc()->init();
        auto commandBuffer = commandQueue->commandBuffer();
        auto encoder = commandBuffer->renderCommandEncoder( view->currentRenderPassDescriptor() );
        
        renderer->draw( encoder, world );

        encoder->endEncoding();
        
        commandBuffer->presentDrawable( view->currentDrawable() );
        commandBuffer->commit();
        
        releasePool->release();
    }
}
