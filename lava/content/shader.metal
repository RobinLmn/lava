#include <metal_stdlib>
using namespace metal;

struct v2f
{
    float4 position [[position]];
    float3 normal;
    half3 color;
};

struct VertexData
{
    float3 position;
    float3 normal;
    float3 color;
};

v2f vertex vertexMain( device const VertexData* vertexData [[buffer(0)]],
                       constant float4x4& model [[buffer(1)]],
                       constant float4x4& viewProjection [[buffer(2)]],
                       uint vertexId [[vertex_id]] )
{
    const device VertexData& v = vertexData[ vertexId ];
    float4 position = float4( v.position, 1.0 );
    
    v2f o;
    o.position = viewProjection * model * position;
    o.color = half3( v.color.rgb );
    o.normal = v.normal;
    
    return o;
}

half4 fragment fragmentMain( v2f in [[stage_in]] )
{
   return half4( in.color, 1.0 );
}
