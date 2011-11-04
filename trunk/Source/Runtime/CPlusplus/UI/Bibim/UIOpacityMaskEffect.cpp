#include <Bibim/PCH.h>
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
        switch (fill)
        {
            case FanStyle:
                if (isShaderFunctionRendering)
                    return new FanEffectorForShaderFunction(this);
                else
                    return new EffectorForFixedFunction(this);
            case BarStyle:
                if (isShaderFunctionRendering)
                    return new BarEffectorForShaderFunction(this);
                else
                    return nullptr;
            default:
                BBBreak();
        }
    }

    void UIOpacityMaskEffect::SetStartPoint(float value)
    {
        startPoint = Math::Clamp(value, 0.0f, 1.0f);
    }

    void UIOpacityMaskEffect::SetLength(float value)
    {
        length = Math::Clamp(value, -1.0f, +1.0f);
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
        fill = static_cast<FillStyle>(reader.ReadInt8());
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

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIOpacityMaskEffect::FanEffectorForShaderFunction::FanEffectorForShaderFunction(UIOpacityMaskEffect* effect)
        : MaskEffector(BBMakeFOURCC('U', 'O', 'M', 'F'), effect)
    {
        startPoint = effect->startPoint;
        invLength = effect->invLength;
    }

    UIOpacityMaskEffect::FanEffectorForShaderFunction::~FanEffectorForShaderFunction()
    {
    }

    void UIOpacityMaskEffect::FanEffectorForShaderFunction::Setup(ShaderEffect* effect)
    {
        if (ShaderEffect::ParameterPtr param = effect->FindParameter("MaskTexture"))
            param->SetValue(GetMask()->GetTexture());
        if (ShaderEffect::ParameterPtr param = effect->FindParameter("OMStart"))
            param->SetValue(startPoint);
        if (ShaderEffect::ParameterPtr param = effect->FindParameter("OMInvLength"))
            param->SetValue(invLength);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIOpacityMaskEffect::BarEffectorForShaderFunction::BarEffectorForShaderFunction(UIOpacityMaskEffect* effect)
        : MaskEffector(BBMakeFOURCC('U', 'O', 'M', 'B'), effect)
    {
        startPoint = effect->startPoint;
        invLength = effect->invLength;
    }

    UIOpacityMaskEffect::BarEffectorForShaderFunction::~BarEffectorForShaderFunction()
    {
    }

    void UIOpacityMaskEffect::BarEffectorForShaderFunction::Setup(ShaderEffect* effect)
    {
        if (ShaderEffect::ParameterPtr param = effect->FindParameter("MaskTexture"))
            param->SetValue(GetMask()->GetTexture());
        if (ShaderEffect::ParameterPtr param = effect->FindParameter("OMStart"))
            param->SetValue(startPoint);
        if (ShaderEffect::ParameterPtr param = effect->FindParameter("OMInvLength"))
            param->SetValue(invLength);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIOpacityMaskEffect::EffectorForFixedFunction::EffectorForFixedFunction(UIOpacityMaskEffect* effect)
        : MaskEffector(effect)
    {
    }

    UIOpacityMaskEffect::EffectorForFixedFunction::~EffectorForFixedFunction()
    {
    }

    void UIOpacityMaskEffect::EffectorForFixedFunction::Begin(UIRenderer* renderer)
    {
    }
    
    void UIOpacityMaskEffect::EffectorForFixedFunction::End(UIRenderer* renderer)
    {
    }
}