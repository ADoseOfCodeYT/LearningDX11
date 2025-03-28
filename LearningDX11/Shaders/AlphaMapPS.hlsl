Texture2D shaderTexture1 : register(t0);
Texture2D shaderTexture2 : register(t1);
Texture2D shaderTexture3 : register(t2);
SamplerState SampleType : register(s0);

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
};

float4 AlphaMapPixelShader(PixelInputType input) : SV_TARGET
{
    float4 color1;
    float4 color2;
    float4 alphaValue;
    float4 blendColor;
	 
	
    // Get the pixel color from the first texture.
    color1 = shaderTexture1.Sample(SampleType, input.tex);

    // Get the pixel color from the second texture.
    color2 = shaderTexture2.Sample(SampleType, input.tex);

    // Get the pixel color from the alpha texture.
    alphaValue  = shaderTexture3.Sample(SampleType, input.tex);

    // Combine the two textures based on the alpha value.
    blendColor = (alphaValue * color1) + ((1.0 - alphaValue) * color2);

    // Saturate the final color value.
    blendColor = saturate(blendColor);

    return blendColor;
}