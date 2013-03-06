#include <Bibim/PCH.h>
#include <Bibim/UIBlendingEffect.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/ShaderEffect.h>

namespace Bibim
{
    BBImplementsComponent(UIBlendingEffect);

    UIBlendingEffect::UIBlendingEffect()
        : Base(ClassIndex, true, true),
          mode(NormalBlend)
    {
    }

    UIBlendingEffect::UIBlendingEffect(BlendMode mode)
        : Base(ClassIndex, true, true),
          mode(mode)
    {
    }

    UIBlendingEffect::UIBlendingEffect(const char* mode)
        : Base(ClassIndex, true, true),
          mode(ConvertFromStringToBlendMode(mode))
    {
    }

    UIBlendingEffect::~UIBlendingEffect()
    {
    }

    UIRenderer::Effector* UIBlendingEffect::CreateEffector(UIRenderer::Effector* parent, bool /*isShaderFunctionRendering*/)
    {
        return new Effector(static_cast<Effector*>(parent), this);
    }

    void UIBlendingEffect::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        mode = static_cast<BlendMode>(reader.ReadByte());
    }

    void UIBlendingEffect::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        mode = o->mode;
    }

    BlendMode UIBlendingEffect::ConvertFromStringToBlendMode(const char* value)
    {
             if (value == nullptr)                                      return NormalBlend;
        else if (String::EqualsCharsIgnoreCase(value, "Normal"))        return NormalBlend;
        else if (String::EqualsCharsIgnoreCase(value, "Add"))           return AdditiveBlend;
        else if (String::EqualsCharsIgnoreCase(value, "Lighten"))       return LightenBlend;
        else if (String::EqualsCharsIgnoreCase(value, "Darken"))        return DarkenBlend;
        else if (String::EqualsCharsIgnoreCase(value, "Mul"))           return MultiplyBlend;
        else if (String::EqualsCharsIgnoreCase(value, "Screen"))        return ScreenBlend;
        else if (String::EqualsCharsIgnoreCase(value, "Additive"))      return AdditiveBlend;
        else if (String::EqualsCharsIgnoreCase(value, "Muliply"))       return MultiplyBlend;
        else if (String::EqualsCharsIgnoreCase(value, "Dodge"))         return AdditiveBlend;
        else if (String::EqualsCharsIgnoreCase(value, "LinearDodge"))   return AdditiveBlend;
        else                                                            return NormalBlend;
    }
    
    const char* UIBlendingEffect::ConvertFromBlendModeToString(BlendMode value)
    {
        switch (value)
        {
            case NormalBlend:   return "Normal";
            case AdditiveBlend: return "Add";
            case LightenBlend:  return "Lighten";
            case DarkenBlend:   return "Darken";
            case MultiplyBlend: return "Mul";
            case ScreenBlend:   return "Screen";
            default:            return "Normal";
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIBlendingEffect::Effector::Effector(Effector* /*parent*/, UIBlendingEffect* effect)
        : mode(effect->mode)
    {
    }

    UIBlendingEffect::Effector::~Effector()
    {
    }

    void UIBlendingEffect::Effector::Begin(UIRendererBase* renderer)
    {
        oldMode = renderer->Setup(mode);
    }

    void UIBlendingEffect::Effector::End(UIRendererBase* renderer)
    {
        renderer->Setup(oldMode);
    }
}