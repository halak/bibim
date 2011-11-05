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

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIBlendingEffect::Effector::Effector(Effector* /*parent*/, UIBlendingEffect* effect)
        : mode(effect->mode)
    {
    }

    UIBlendingEffect::Effector::~Effector()
    {
    }

    void UIBlendingEffect::Effector::Begin(UIRenderer* renderer)
    {
        oldMode = renderer->Setup(mode);
    }

    void UIBlendingEffect::Effector::End(UIRenderer* renderer)
    {
        renderer->Setup(oldMode);
    }
}