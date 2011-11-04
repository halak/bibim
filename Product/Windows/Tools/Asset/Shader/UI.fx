float4x4 WTM;
float4x4 VPTM;

#if defined(COLORMATRIX)
float4 Red;
float4 Green;
float4 Blue;
#endif

texture DefaultTexture;

#if defined(COLORANDALPHATEXTURE)
texture MaskTexture;
#endif

#if defined(OPACITYMAP)
float OMStart;
float OMInvLength;
#endif

struct VSInput
{
    float4 Position : POSITION0;
    float4  Color : COLOR0;
    float2 TexCoord1 : TEXCOORD0;
#if defined(COLORANDALPHATEXTURE)
    float2 TexCoord2 : TEXCOORD1;
#endif
};

sampler DefaultSampler = 
sampler_state
{
    Texture = <DefaultTexture>;
};

#if defined(COLORANDALPHATEXTURE)
sampler MaskSampler = 
sampler_state
{
    Texture = <MaskTexture>;
};
#endif

VSInput VSMain(VSInput input)
{
    VSInput output;
    output.Position = mul(mul(input.Position, WTM), VPTM);
    output.Color = input.Color;
    output.TexCoord1 = input.TexCoord1;
#if defined(COLORANDALPHATEXTURE)
    output.TexCoord2 = input.TexCoord2;
#endif
    return output;
}

float4 PSMain(VSInput input) : COLOR0
{
    float4 output;
#if defined(NOTEXTURE) || defined(COLORONLY)
    output = input.Color;
#elif defined(COLORTEXTURE)
    output = tex2D(DefaultSampler, input.TexCoord1) * input.Color;
#elif defined(ALPHATEXTURE)
    output = float4(input.Color.rgb, tex2D(DefaultSampler, input.TexCoord1).a * input.Color.a);
#elif defined(COLORANDALPHATEXTURE)
    float maskAlpha = tex2D(MaskSampler, input.TexCoord2).a;
    output = tex2D(DefaultSampler, input.TexCoord1) * input.Color;
#endif

#if defined(COLORMATRIX)
    output = float4
    (
        dot(output.rgb, Red.rgb) + Red.a,
        dot(output.rgb, Green.rgb) + Green.a,
        dot(output.rgb, Blue.rgb) + Blue.a,
        output.a
    );
#endif

#if defined(OPACITYMAP)
    float OM = (maskAlpha - OMStart) * OMInvLength;
    output.a *= OM;
#endif

    return output;
}

technique Grayscale
{
    pass
    {
        VertexShader = compile vs_2_0 VSMain();
        PixelShader = compile ps_2_0 PSMain();
    }
}