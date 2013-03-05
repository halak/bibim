uniform mat4 MVP;

#if defined(FX_COLORMATRIX)
uniform vec4 CMRed;
uniform vec4 CMGreen;
uniform vec4 CMBlue;
#endif

#if defined(FX_OPACITYMAPFAN) || defined(FX_OPACITYMAPBAR)
uniform vec4 OMValues;
#endif

attribute vec4 Position;
attribute vec4 Color;
varying   vec4 fColor;
#if defined(INPUT_COLORTEXTURE) || defined(INPUT_ALPHATEXTURE)
attribute vec2 TexCoord1;
varying   vec2 fTexCoord1;
#endif
#if defined(MASKTEXTURE)
attribute vec2 TexCoord2;
varying   vec2 fTexCoord2;
#endif

void main()
{
    gl_Position = MVP * Position;
    fColor = Color;
    
#if defined(INPUT_COLORTEXTURE) || defined(INPUT_ALPHATEXTURE)
    fTexCoord1 = TexCoord1;
#endif
#if defined(MASKTEXTURE)
    fTexCoord2 = TexCoord2;
#endif
}

////////////////////////////////////////////////////////////////////////////////

varying vec4 fColor;

uniform sampler2D MainSampler;
varying vec2 fTexCoord1;

#if defined(MASKTEXTURE)
uniform sampler2D MaskSampler;
varying vec2 fTexCoord2;
#endif

void main()
{
#if defined(INPUT_COLOR)
    vec4 result = fColor;
#elif defined(INPUT_COLORTEXTURE)
    vec4 result = texture(MainSampler, fTexCoord1);// * fColor;
#elif defined(INPUT_ALPHATEXTURE)
    vec4 result = vec4(fColor.rgb, 0.5);//texture(MainSampler, fTexCoord1).a);// * fColor.a);
#endif

#if defined(MASKTEXTURE)
    vec4 mask = texture(MaskSampler, fTexCoord2).a;
#endif

#if defined(FX_COLORMATRIX)
    result = float4
    (
        dot(result.rgb, CMRed.rgb) + CMRed.a,
        dot(result.rgb, CMGreen.rgb) + CMGreen.a,
        dot(result.rgb, CMBlue.rgb) + CMBlue.a,
        result.a
    );
#endif

#if defined(FX_OPACITYMAP)
    result.a *= mask;
#elif defined(FX_OPACITYMAPFAN)
    result.a *= (mask - OMValues.x) * OMValues.y;
#elif defined(FX_OPACITYMAPBAR)
    result.a *= (OMValues.x <= mask && mask <= OMValues.y) ? 1.0f - abs((mask - OMValues.z) * OMValues.w) : 0.0f;
#endif

    gl_FragColor = result;
}