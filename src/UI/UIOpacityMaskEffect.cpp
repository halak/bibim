#include <Bibim/Config.h>
#include <Bibim/UIOpacityMaskEffect.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Image.h>
#include <Bibim/Math.h>
#include <Bibim/ShaderEffect.h>

namespace Bibim
{
    BBImplementsComponent(UIOpacityMaskEffect);

    UIOpacityMaskEffect::UIOpacityMaskEffect()
        : Base(true, true, nullptr),
          startPoint(0.0f),
          length(1.0f),
          fill(FanStyle),
          invLength(1.0f)
    {
    }

    UIOpacityMaskEffect::UIOpacityMaskEffect(Image* mask)
        : Base(true, true, mask),
          startPoint(0.0f),
          length(1.0f),
          fill(FanStyle),
          invLength(1.0f)
    {
    }

    UIOpacityMaskEffect::UIOpacityMaskEffect(Image* mask, float startPoint, float length, FillStyle fill)
        : Base(true, true, mask),
          startPoint(Math::Clamp(startPoint, 0.0f, 1.0f)),
          length(Math::Clamp(length, -1.0f, +1.0f)),
          fill(fill),
          invLength(1.0)
    {
    }

    UIOpacityMaskEffect::~UIOpacityMaskEffect()
    {
    }

    UIRenderer::Effector* UIOpacityMaskEffect::CreateEffector(UIRenderer::Effector* /*parent*/, bool isShaderFunctionRendering)
    {
        if ((startPoint == 0.0f && length == +1.0f) ||
            (startPoint == 1.0f && length == -1.0f))
        {
            if (isShaderFunctionRendering)
                return new EffectorForShaderFunction(this);
            else
                return new EffectorForFixedFunction(this);
        }

        switch (fill)
        {
            case FanStyle:
                if (isShaderFunctionRendering)
                    return new FanEffectorForShaderFunction(this);
                else
                    return nullptr;
            case BarStyle:
                if (length == 0.0f)
                    return nullptr;

                if (isShaderFunctionRendering)
                    return new BarEffectorForShaderFunction(this);
                else
                    return nullptr;
            default:
                BBBreak();
                return nullptr;
        }
    }

    void UIOpacityMaskEffect::SetStartPoint(float value)
    {
        startPoint = value;
    }

    void UIOpacityMaskEffect::SetLength(float value)
    {
        value = value;
        if (length != value)
        {
            length = value;
            if (value != 0.0f)
                invLength = 1.0f / value;
        }
    }

    void UIOpacityMaskEffect::SetFill(FillStyle value)
    {
        fill = value;
    }

    void UIOpacityMaskEffect::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        startPoint = reader.ReadFloat();
        length = reader.ReadFloat();
        fill = static_cast<FillStyle>(reader.ReadByte());
        if (length != 0.0f)
            invLength = 1.0f / length;
    }

    void UIOpacityMaskEffect::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        startPoint = o->startPoint;
        length = o->length;
        fill = o->fill;
        invLength = o->invLength;
    }

    UIOpacityMaskEffect::FillStyle UIOpacityMaskEffect::ConvertFromStringToFillStyle(const char* value)
    {
             if (value == nullptr)                            return FanStyle;
        else if (String::EqualsCharsIgnoreCase(value, "Fan")) return FanStyle;
        else if (String::EqualsCharsIgnoreCase(value, "Bar")) return BarStyle;
        else                                                  return FanStyle;
    }

    const char* UIOpacityMaskEffect::ConvertFromFillStyleToString(FillStyle value)
    {
        switch (value)
        {
            case FanStyle: return "Fan";
            case BarStyle: return "Bar";
            default:       return "Fan";
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIOpacityMaskEffect::EffectorForShaderFunction::EffectorForShaderFunction(UIOpacityMaskEffect* effect)
        : MaskEffector(BBMakeFOURCC('U', 'O', 'M', '_'), effect)
    {
    }

    UIOpacityMaskEffect::EffectorForShaderFunction::~EffectorForShaderFunction()
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIOpacityMaskEffect::FanEffectorForShaderFunction::FanEffectorForShaderFunction(UIOpacityMaskEffect* effect)
        : MaskEffector(BBMakeFOURCC('U', 'O', 'M', 'F'), effect)
    {
        unifiedValue.X = effect->startPoint;
        unifiedValue.Y = effect->invLength;
        unifiedValue.Z = 0.0f;
        unifiedValue.W = 0.0f;
    }

    UIOpacityMaskEffect::FanEffectorForShaderFunction::~FanEffectorForShaderFunction()
    {
    }

    void UIOpacityMaskEffect::FanEffectorForShaderFunction::Setup(ShaderEffect* effect)
    {
        if (ShaderEffect::ParameterPtr param = effect->FindParameter("OMValues"))
            param->SetValue(unifiedValue);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIOpacityMaskEffect::BarEffectorForShaderFunction::BarEffectorForShaderFunction(UIOpacityMaskEffect* effect)
        : MaskEffector(BBMakeFOURCC('U', 'O', 'M', 'B'), effect)
    {
        const float s = effect->startPoint;
        const float e = effect->startPoint + effect->length;

        unifiedValue.X = Math::Min(s, e);
        unifiedValue.Y = Math::Max(s, e);
        unifiedValue.Z = s + (e - s) * 0.5f;
        unifiedValue.W = effect->invLength * 2.0f;
    }

    UIOpacityMaskEffect::BarEffectorForShaderFunction::~BarEffectorForShaderFunction()
    {
    }

    void UIOpacityMaskEffect::BarEffectorForShaderFunction::Setup(ShaderEffect* effect)
    {
        if (ShaderEffect::ParameterPtr param = effect->FindParameter("OMValues"))
            param->SetValue(unifiedValue);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIOpacityMaskEffect::EffectorForFixedFunction::EffectorForFixedFunction(UIOpacityMaskEffect* effect)
        : MaskEffector(effect)
    {
    }

    UIOpacityMaskEffect::EffectorForFixedFunction::~EffectorForFixedFunction()
    {
    }

    void UIOpacityMaskEffect::EffectorForFixedFunction::Begin(UIRendererBase* renderer)
    {
        renderer->BeginOpacityMaskMode();
    }
    
    void UIOpacityMaskEffect::EffectorForFixedFunction::End(UIRendererBase* renderer)
    {
        renderer->EndOpacityMaskMode();
    }
}