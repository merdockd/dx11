#include "Lights.hlsli"

cbuffer cbPerObject : register(b0)
{
	float4x4 gWorld;
	float4x4 gWorldInverseTranspose;
	float4x4 gWorldViewProjection;
    float4x4 gTexTransform;
    float4x4 gShadowTransform;
};

struct VertexShaderInput
{
	float3 mPositionL : POSITION;
	float3 mNormalL : NORMAL;
    float3 mTangentL : TANGENT;
    float2 mTexCoord : TEXCOORD;
};

struct VertexShaderOutput
{
    float4 mShadowPositionH : TEXCOORD1;
	float4 mPositionH : SV_POSITION;
    float3 mPositionW : POSITION;
    float3 mNormalW : NORMAL;
    float3 mTangentW : TANGENT;
    float2 mTexCoord : TEXCOORD0;
};

VertexShaderOutput main(VertexShaderInput input)
{
	VertexShaderOutput output;
	
	// Transform to world space space.
	output.mPositionW = mul(float4(input.mPositionL, 1.0f), gWorld).xyz;
	output.mNormalW = mul(input.mNormalL, (float3x3)gWorldInverseTranspose);
    output.mTangentW = mul(input.mTangentL, (float3x3)gWorld);
		
	// Transform to homogeneous clip space.
	output.mPositionH = mul(float4(input.mPositionL, 1.0f), gWorldViewProjection);

    // Output vertex attributes for interpolation across triangle.
	output.mTexCoord = mul(float4(input.mTexCoord, 0.0f, 1.0f), gTexTransform).xy;

    // Generate projective tex-coords to project shadow map onto scene.
    output.mShadowPositionH = mul(float4(input.mPositionL, 1.0f), gShadowTransform);
	
	return output;
}