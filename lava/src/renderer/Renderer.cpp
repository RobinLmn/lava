#include "Renderer.hpp"

#include <util/Util.hpp>

#include <gameplay/components/TransformComponent.hpp>
#include <gameplay/components/MeshComponent.hpp>
#include <gameplay/components/CameraComponent.hpp>

namespace
{
    auto getCameraBuffer( const lava::World* world ) -> MTL::Buffer*
    {
        const auto entities = world->getRegistry()->view<const lava::CameraComponent, const lava::CameraBufferComponent>().each();
        for ( auto [entity, camera, buffer] : entities )
        {
            if ( camera.isMainCamera )
            {
                return buffer.cameraBuffer;
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
        
        const auto entities = world->getRegistry()->view< const StaticMeshComponent,
                                                          const MeshBufferComponent,
                                                          const TransformBufferComponent >().each();
        
        for ( auto [entity, mesh, buffer, transform] : entities )
        {
            encoder->setVertexBuffer( buffer.vertexBuffer, 0, 0 );
            encoder->setVertexBuffer( transform.modelBuffer, 0, 1 );
            encoder->setVertexBuffer( cameraBuffer, 0, 2 );
            
            encoder->setCullMode( MTL::CullModeBack );
            encoder->setFrontFacingWinding( MTL::Winding::WindingCounterClockwise );

            encoder->drawIndexedPrimitives( MTL::PrimitiveType::PrimitiveTypeTriangle,
                                            mesh.indices.size(),
                                            MTL::IndexType::IndexTypeUInt16,
                                            buffer.indexBuffer,
                                            0,
                                            1 );
        }
    }
}
