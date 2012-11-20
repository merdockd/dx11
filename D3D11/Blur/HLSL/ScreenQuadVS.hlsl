cbuffer cbPerFrame : register(b0)
{
	float4x4 gWorldInverseTranspose;
	float4x4 gWorldViewProjection;
    float4x4 gTexTransform;
};

struct VertexShaderInput
{
	float3 mPositionL : POSITION;
	float3 mNormalL : NORMAL;
    float2 mTexCoord : TEXCOORD;
};

struct VertexShaderOutput
{
	float4 mPositionH : SV_POSITION;
    float3 mNormalW : NORMAL;
    float2 mTexCoord : TEXCOORD;
};

VertexShaderOutput main(VertexShaderInput input)
{
	VertexShaderOutput output;
	
	// Transform to world space space.
	output.mNormalW = mul(input.mNormalL, (float3x3)gWorldInverseTranspose);
		
	// Transform to homogeneous clip space.
	output.mPositionH = mul(float4(input.mPositionL, 1.0f), gWorldViewProjection);

    // Output vertex attributes for interpolation across triangle.
	output.mTexCoord = mul(float4(input.mTexCoord, 0.0f, 1.0f), gTexTransform).xy;
	
	return output;
}