
#define NUM_LIGHTS 4

Texture2D shaderTexture1 : register(t0);
Texture2D shaderTexture2 : register(t1);
SamplerState SampleType : register(s0);

cbuffer LightColorBuffer
{
    float4 diffuseColor[NUM_LIGHTS];
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
     float3 lightPos[NUM_LIGHTS] : TEXCOORD1;
};

float4 LightPixelShader(PixelInputType input) : SV_TARGET
{
    float lightIntensity[NUM_LIGHTS];
    float4 colorArray[NUM_LIGHTS];
    float4 colorSum;
    float4 finalColor;
    int i;

    float4 color1;
    float4 color2;
    float4 blendColor;
    
     // Sample the pixel color from the textures using the sampler at this texture coordinate location.
    color1 = shaderTexture1.Sample(SampleType, input.tex);
    color2 = shaderTexture2.Sample(SampleType, input.tex);
    
    // Combine the two textures together.
    blendColor = color1 * color2 * 2.0;
    
    for(i=0; i<NUM_LIGHTS; i++)
    {
        // Calculate the different amounts of light on this pixel based on the positions of the lights.
        lightIntensity[i] = saturate(dot(input.normal, input.lightPos[i]));

        // Determine the diffuse color amount of each of the four lights.
        colorArray[i] = diffuseColor[i] * lightIntensity[i];
    }

    // Initialize the sum of colors.
    colorSum = float4(0.0f, 0.0f, 0.0f, 1.0f);

    // Add all of the light colors up.
    for(i=0; i<NUM_LIGHTS; i++)
    {
        colorSum.r += colorArray[i].r;
        colorSum.g += colorArray[i].g;
        colorSum.b += colorArray[i].b;
    }

    // Multiply the texture pixel by the combination of all four light colors to get the final result.
    finalColor = saturate(colorSum * blendColor);

    return finalColor;
}

