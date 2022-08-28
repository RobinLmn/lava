#include "Math.hpp"

namespace lava::math
{
    auto perspective( float fovRadians, float aspect, float near, float far ) -> simd::float4x4
    {
        using simd::float4;
        float ys = 1.f / tanf( fovRadians * 0.5f );
        float xs = ys / aspect;
        float zs = far / ( near - far );
        return simd_matrix_from_rows((float4){ xs, 0.0f, 0.0f, 0.0f },
                                     (float4){ 0.0f, ys, 0.0f, 0.0f },
                                     (float4){ 0.0f, 0.0f, zs, near * zs },
                                     (float4){ 0, 0, -1, 0 });
    }

    auto translate( const simd::float3& v ) -> simd::float4x4
    {
        using simd::float4;
        
        const float4 col0 = { 1.0f, 0.0f, 0.0f, 0.0f };
        const float4 col1 = { 0.0f, 1.0f, 0.0f, 0.0f };
        const float4 col2 = { 0.0f, 0.0f, 1.0f, 0.0f };
        const float4 col3 = { v.x, v.y, v.z, 1.0f };
        
        return simd_matrix( col0, col1, col2, col3 );
    }

    auto scale( simd::float4x4& matrix, const simd::float3& scale ) -> void
    {
        using simd::float4;
        
        auto scaleMatrix = simd_matrix(  (float4){ scale.x, 0, 0, 0 },
                                         (float4){ 0, scale.y, 0, 0 },
                                         (float4){ 0, 0, scale.z, 0 },
                                         (float4){ 0, 0, 0, 1.0 });
        
        matrix = matrix * scaleMatrix;
    }

    auto rotateX ( simd::float4x4& matrix, float angleRadians ) -> void
    {
        using simd::float4;
        matrix = matrix * simd_matrix_from_rows( (float4){ 1.0f, 0.0f, 0.0f, 0.0f },
                                                 (float4){ 0.0f, cosf( angleRadians ), sinf( angleRadians ), 0.0f },
                                                 (float4){ 0.0f, -sinf( angleRadians ), cosf( angleRadians ), 0.0f },
                                                 (float4){ 0.0f, 0.0f, 0.0f, 1.0f });
    }

    auto rotateY( simd::float4x4& matrix, float angleRadians ) -> void
    {
        using simd::float4;
        matrix = matrix * simd_matrix_from_rows( (float4){ cosf( angleRadians ), 0.0f, sinf( angleRadians ), 0.0f },
                                                 (float4){ 0.0f, 1.0f, 0.0f, 0.0f },
                                                 (float4){ -sinf( angleRadians ), 0.0f, cosf( angleRadians ), 0.0f },
                                                 (float4){ 0.0f, 0.0f, 0.0f, 1.0f });
    }

    auto rotateZ( simd::float4x4& matrix, float angleRadians ) -> void
    {
        using simd::float4;
        matrix = matrix * simd_matrix_from_rows( (float4){ cosf( angleRadians ), sinf( angleRadians ), 0.0f, 0.0f },
                                                 (float4){ -sinf( angleRadians ), cosf( angleRadians ), 0.0f, 0.0f },
                                                 (float4){ 0.0f, 0.0f, 1.0f, 0.0f },
                                                 (float4){ 0.0f, 0.0f, 0.0f, 1.0f });
    }

    auto rotate( simd::float4x4& matrix, const simd::float3& rotation ) -> void
    {
        rotateX( matrix, rotation.x );
        rotateY( matrix, rotation.y );
        rotateZ( matrix, rotation.z );
    }

    auto degreesToRadian( const float& angleRadians ) -> float
    {
        return angleRadians * constants::pi / 180.f;
    }

    auto degreesToRadian( const simd::float3& v ) -> simd::float3
    {
        return simd::float3{ degreesToRadian( v.x ), degreesToRadian( v.y ), degreesToRadian( v.z ) };
    }

    
}
