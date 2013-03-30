float4x4 MVP;
texture MainTexture;

#if defined(MASKTEXTURE)
texture MaskTexture;
#endif

sampler MainSampler = sampler_state
{
    Texture = <MainTexture>;
};

#if defined(MASKTEXTURE)
sampler MaskSampler = sampler_state
{
    Texture = <MaskTexture>;
};
#endif

#if defined(FX_COLORMATRIX)
float4 CMRed;
float4 CMGreen;
float4 CMBlue;
#endif

#if defined(FX_OPACITYMAPFAN) || defined(FX_OPACITYMAPBAR)
float4 OMValues;
#endif

texture DefaultTexture;
struct VSInput
{
    float4 Position : POSITION0;
    float4 Color : COLOR0;
#if defined(INPUT_COLORTEXTURE) || defined(INPUT_ALPHATEXTURE)
    float2 TexCoord1 : TEXCOORD0;
#endif
#if defined(MASKTEXTURE)
    float2 TexCoord2 : TEXCOORD1;
#endif
};

VSInput VSMain(VSInput input)
{
    VSInput output;
    output.Position = mul(input.Position, MVP);
    output.Color = input.Color;
#if defined(INPUT_COLORTEXTURE) || defined(INPUT_ALPHATEXTURE)
    output.TexCoord1 = input.TexCoord1;
#endif
#if defined(MASKTEXTURE)
    output.TexCoord2 = input.TexCoord2;
#endif
    return output;
}

float4 PSMain(VSInput input) : COLOR0
{
#if defined(INPUT_COLOR)
    float4 output = input.Color;
#elif defined(INPUT_COLORTEXTURE)
    float4 output = tex2D(MainSampler, input.TexCoord1) * input.Color;
#elif defined(INPUT_ALPHATEXTURE)
    float4 output = float4(input.Color.rgb, tex2D(MainSampler, input.TexCoord1).a * input.Color.a);
#endif

#if defined(MASKTEXTURE)
    float mask = tex2D(MaskSampler, input.TexCoord2).a;
#endif

#if defined(FX_COLORMATRIX)
    output = float4
    (
        dot(output.rgb, CMRed.rgb) + CMRed.a,
        dot(output.rgb, CMGreen.rgb) + CMGreen.a,
        dot(output.rgb, CMBlue.rgb) + CMBlue.a,
        output.a
    );
#endif

#if defined(FX_OPACITYMAP)
    output.a *= mask;
#elif defined(FX_OPACITYMAPFAN)
    output.a *= (mask - OMValues.x) * OMValues.y;
#elif defined(FX_OPACITYMAPBAR)
    output.a *= (OMValues.x <= mask && mask <= OMValues.y) ? 1.0f - abs((mask - OMValues.z) * OMValues.w) : 0.0f;
#endif

    return output;
}

technique
{
    pass
    {
        VertexShader = compile vs_2_0 VSMain();
        PixelShader  = compile ps_2_0 PSMain();
    }
}