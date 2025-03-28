Texture2D shaderTexture1 : register(t0);
Texture2D shaderTexture2 : register(t1);
SamplerState SampleType : register(s0);

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
};

float4 LightMapPixelShader(PixelInputType input) : SV_TARGET
{
    float4 color;
    float4 lightColor;
    float4 finalColor;
	 
	
    // Get the pixel color from the color texture.
    color = shaderTexture1.Sample(SampleType, input.tex);

    // Get the pixel color from the light map.
    lightColor = shaderTexture2.Sample(SampleType, input.tex);
	
    // Blend the two pixels together.
    finalColor = color * lightColor;

    return finalColor;
}