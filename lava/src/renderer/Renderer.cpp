#include "Renderer.hpp"

#include <util/Util.hpp>

#include <gameplay/components/Transform.hpp>
#include <gameplay/components/Mesh.hpp>
#include <gameplay/components/Camera.hpp>
#include <gameplay/components/RenderData.hpp>

namespace
{
    using namespace lava;

    auto getUniformBuffer( const lava::World* world ) -> MTL::Buffer*
    {
        const auto entities = world->getRegistry()->view<const lava::UniformBuffer>().each();
        for ( auto [entity, uniformBuffer] : entities )
        {
            return uniformBuffer.buffer;
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
        descriptor->setDepthAttachmentPixelFormat( MTL::PixelFormat::PixelFormatDepth32Float );
        
        NS::Error* error = nullptr;
        pipelineState = device->newRenderPipelineState( descriptor, &error );
        
        vertexFunction->release();
        fragmentFunction->release();
        descriptor->release();
    }

    auto Renderer::buildDepthStencilStates() -> void
    {
        auto* descriptor = MTL::DepthStencilDescriptor::alloc()->init();
        descriptor->setDepthCompareFunction( MTL::CompareFunction::CompareFunctionLessEqual );
        descriptor->setDepthWriteEnabled( true );
        
        depthStencilState = device->newDepthStencilState( descriptor );

        descriptor->release();
    }
    
    auto Renderer::draw( MTL::RenderCommandEncoder* encoder, const World* world ) -> void
    {
        encoder->setRenderPipelineState( pipelineState );
        encoder->setDepthStencilState( depthStencilState );
        
        encoder->setCullMode( MTL::CullMode::CullModeBack );
        encoder->setTriangleFillMode( MTL::TriangleFillMode::TriangleFillModeFill );
        encoder->setFrontFacingWinding( MTL::WindingCounterClockwise );
        
        const auto& uniformBuffer = getUniformBuffer( world );
        
        const auto entities = world->getRegistry()->view<const StaticMesh, const MeshBuffer, const ObjectBuffer>().each();
        for ( auto [entity, mesh, meshBuffer, objectBuffer] : entities )
        {
            encoder->setVertexBuffer( meshBuffer.vertices, 0, 0 );
            encoder->setVertexBuffer( objectBuffer.buffer, 0, 1 );
            encoder->setVertexBuffer( uniformBuffer, 0, 2 );
            
            encoder->drawPrimitives(  MTL::PrimitiveType::PrimitiveTypeTriangle, 0, mesh.vertices.size(), 1 );
        }
    }
}
