#include <simd/simd.h>

namespace lava::constants
{
    const float pi = 3.1415f;
}

namespace lava::math
{
    extern auto perspective( float fovRadians, float aspect, float near, float far ) -> simd::float4x4;
    extern auto translate( const simd::float3& v ) -> simd::float4x4;

    extern auto scale( simd::float4x4& matrix, const simd::float3& scale ) -> void;
    extern auto rotateX( simd::float4x4& matrix, float angleRadians ) -> void;
    extern auto rotateY( simd::float4x4& matrix, float angleRadians ) -> void;
    extern auto rotateZ( simd::float4x4& matrix, float angleRadians ) -> void;
    extern auto rotate( simd::float4x4& matrix, const simd::float3& angleRadians ) -> void;

    extern auto degreesToRadian( const simd::float3& vectorRadians ) -> simd::float3;
    extern auto degreesToRadian( const float& angleRadians ) -> float;
}
