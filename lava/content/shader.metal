#include <metal_stdlib>
using namespace metal;

struct v2f
{
    half3 color;
    float4 position [[position]];
    float3 normal;
    float3 lightPosition;
    float3 lightColor;
    float3 ambientStrength;
    float3 diffuseStrength;
};

struct VertexData
{
    float3 position;
    float3 normal;
    float3 color;
};

struct ObjectData
{
    float4x4 modelMatrix;
    float4x4 normalMatrix;
};

struct RenderData
{
    float ambientStrength;
    float diffuseStrength;
    float3 lightColor;
    float3 lightPosition;
    float4x4 viewProjection;
};

v2f vertex vertexMain( device const VertexData* vertexData [[buffer(0)]],
                       constant ObjectData* objectData [[buffer(1)]],
                       constant RenderData* renderData [[buffer(2)]],
                       uint vertexId [[vertex_id]] )
{
    const device VertexData& v = vertexData[ vertexId ];
    float4 position = float4( v.position, 1.0 );
    
    v2f o;
    
    o.position = renderData->viewProjection * objectData->modelMatrix * position;
    o.normal = (objectData->normalMatrix * float4(v.normal, 1.0)).xyz;
    
    o.color = half3( v.color.rgb );
    o.lightPosition = renderData->lightPosition;
    o.lightColor = renderData->lightColor;
    o.ambientStrength = renderData->ambientStrength;
    o.diffuseStrength = renderData->diffuseStrength;
    
    return o;
}

half4 fragment fragmentMain( v2f in [[stage_in]] )
{
    float3 lightDirection = normalize(in.position.xyz - in.lightPosition);
    
    half3 ambient = (half3)(in.ambientStrength * in.lightColor);
    half3 diffuse = (half3)(max(dot(in.normal, lightDirection), 0.0) * in.diffuseStrength * in.lightColor);
    
    half3 color = (ambient + diffuse) * in.color;
    
    return half4( color, 1.0 );
}
