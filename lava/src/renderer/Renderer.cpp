#include "Renderer.hpp"

#include <core/Util.hpp>

#include <gameplay/components/Transform.hpp>
#include <gameplay/components/Mesh.hpp>
#include <gameplay/components/Camera.hpp>

namespace
{
    auto getCameraBuffer( const lava::World* world ) -> MTL::Buffer*
    {
        const auto entities = world->getRegistry()->view<const lava::Camera>().each();
        for ( auto [entity, camera] : entities )
        {
            if ( camera.isMainCamera )
            {
                return camera.cameraBuffer;
            }
        }
        return nullptr;
    }
}

namespace lava
{
    Renderer::Renderer( MTL::Device* device )
        : device( device )
    {
        buildShaders();
        buildDepthStencilStates();
    }

    Renderer::~Renderer()
    {
        pipelineState->release();
        library->release();
        depthStencilState->release();
    }

    auto Renderer::buildShaders() -> void
    {
        library = device->newDefaultLibrary();
        auto vertexFunction = library->newFunction( TO_NS_STRING( "vertexMain" ) );
        auto fragmentFunction = library->newFunction( TO_NS_STRING( "fragmentMain" ) );
        
        auto descriptor = MTL::RenderPipelineDescriptor::alloc()->init();
        descriptor->setVertexFunction( vertexFunction );
        descriptor->setFragmentFunction( fragmentFunction );
        
        descriptor->colorAttachments()->object( 0 )->setPixelFormat( MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB );
        descriptor->setDepthAttachmentPixelFormat( MTL::PixelFormat::PixelFormatDepth16Unorm );
        
        NS::Error* error = nullptr;
        pipelineState = device->newRenderPipelineState( descriptor, &error );
        
        vertexFunction->release();
        fragmentFunction->release();
        descriptor->release();
    }

    auto Renderer::buildDepthStencilStates() -> void
    {
        auto* descriptor = MTL::DepthStencilDescriptor::alloc()->init();
        descriptor->setDepthCompareFunction( MTL::CompareFunction::CompareFunctionLess );
        descriptor->setDepthWriteEnabled( true );

        depthStencilState = device->newDepthStencilState( descriptor );

        descriptor->release();
    }
    
    auto Renderer::draw( MTL::RenderCommandEncoder* encoder, const World* world ) -> void
    {
        encoder->setRenderPipelineState( pipelineState );
        encoder->setDepthStencilState( depthStencilState );
        
        const auto cameraBuffer = getCameraBuffer( world );
        
        const auto entities = world->getRegistry()->view<const Mesh, const Transform>().each();
        for ( auto [entity, mesh, transform] : entities )
        {
            encoder->setVertexBuffer( mesh.vertexBuffer, 0, 0 );
            encoder->setVertexBuffer( transform.modelBuffer, 0, 1 );
            encoder->setVertexBuffer( cameraBuffer, 0, 2 );
            
            encoder->setCullMode( MTL::CullModeBack );
            encoder->setFrontFacingWinding( MTL::Winding::WindingCounterClockwise );

            encoder->drawIndexedPrimitives( MTL::PrimitiveType::PrimitiveTypeTriangle,
                                            mesh.indices.size(),
                                            MTL::IndexType::IndexTypeUInt16,
                                            mesh.indexBuffer,
                                            0,
                                            1 );
        }
    }
}
