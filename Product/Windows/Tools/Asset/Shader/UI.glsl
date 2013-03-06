uniform mat4 MVP;

attribute mediump vec3 Position;
attribute lowp vec4 Color;
varying   lowp vec4 fColor;
#if defined(INPUT_COLORTEXTURE) || defined(INPUT_ALPHATEXTURE)
attribute mediump vec2 TexCoord1;
varying   mediump vec2 fTexCoord1;
#endif
#if defined(MASKTEXTURE)
attribute mediump vec2 TexCoord2;
varying   mediump vec2 fTexCoord2;
#endif

void main()
{
    gl_Position = MVP * vec4(Position.xyz, 1);
    fColor = Color.bgra * 0.0039215686274509803921568627451;
    
#if defined(INPUT_COLORTEXTURE) || defined(INPUT_ALPHATEXTURE)
    fTexCoord1 = TexCoord1;
#endif
#if defined(MASKTEXTURE)
    fTexCoord2 = TexCoord2;
#endif
}

////////////////////////////////////////////////////////////////////////////////

varying vec4 fColor;

#if defined(FX_COLORMATRIX)
uniform vec4 CMRed;
uniform vec4 CMGreen;
uniform vec4 CMBlue;
#endif

#if defined(FX_OPACITYMAPFAN) || defined(FX_OPACITYMAPBAR)
uniform vec4 OMValues;
#endif

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
    vec4 result = texture(MainSampler, fTexCoord1) * fColor;
#elif defined(INPUT_ALPHATEXTURE)
    vec4 result = vec4(fColor.rgb, texture(MainSampler, fTexCoord1).a * fColor.a);
#endif

#if defined(FX_COLORMATRIX)
    result = vec4
    (
        dot(result.rgb, CMRed.rgb) + CMRed.a,
        dot(result.rgb, CMGreen.rgb) + CMGreen.a,
        dot(result.rgb, CMBlue.rgb) + CMBlue.a,
        result.a
    );
#endif

#if defined(MASKTEXTURE)
    lowp float mask = texture(MaskSampler, fTexCoord2).a;
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