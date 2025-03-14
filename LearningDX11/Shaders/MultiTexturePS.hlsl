Texture2D shaderTexture1 : register(t0);
Texture2D shaderTexture2 : register(t1);
SamplerState SampleType : register(s0);

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
};

float4 MultiTexturePixelShader(PixelInputType input) : SV_TARGET
{
    float4 color1;
    float4 color2;
    float4 blendColor;
    
    // Sample the pixel color from the textures using the sampler at this texture coordinate location.
    color1 = shaderTexture1.Sample(SampleType, input.tex);
    color2 = shaderTexture2.Sample(SampleType, input.tex);
	
    // Combine the two textures together.
    blendColor = color1 * color2 * 2.0;

    // Saturate the final color.
    blendColor = saturate(blendColor);

    return blendColor;
}