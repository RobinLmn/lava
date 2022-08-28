#include <metal_stdlib>
using namespace metal;

struct v2f
{
    float4 position [[position]];
    half3 color;
};

struct VertexData
{
    float3 position;
};

v2f vertex vertexMain( device const VertexData* vertexData [[buffer(0)]],
                       constant float4x4& model [[buffer(1)]],
                       constant float4x4& viewProjection [[buffer(2)]],
                       uint vertexId [[vertex_id]] )
{
    float4 position = float4( vertexData[ vertexId ].position, 1.0 );
    position = model * position;
    position = viewProjection * position;
    
    v2f o;
    o.position = position;
    o.color = half3( 1.0 );
    return o;
}

half4 fragment fragmentMain( v2f in [[stage_in]] )
{
    return half4( in.color, 1.0 );
}
