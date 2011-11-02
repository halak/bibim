#include <Bibim/PCH.h>
#include <Bibim/UIBlendingEffect.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/ShaderEffect.h>

namespace Bibim
{
    UIBlendingEffect::Effector::Effector(Effector* /*parent*/, UIBlendingEffect* effect)
        : UIRenderer::Effector(UIBlendingEffect::ClassID, false, true),
          mode(effect->mode)
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

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    BBImplementsComponent(UIBlendingEffect);

    UIBlendingEffect::UIBlendingEffect()
        : Base(ClassIndex, true, false),
          mode(NormalBlend)
    {
    }

    UIBlendingEffect::UIBlendingEffect(BlendMode mode)
        : Base(ClassIndex, true, false),
          mode(mode)
    {
    }

    UIBlendingEffect::~UIBlendingEffect()
    {
    }

    UIBlendingEffect::Effector* UIBlendingEffect::CreateEffector(UIRenderer::Effector* parent)
    {
        return new Effector(static_cast<Effector*>(parent), this);
    }

    void UIBlendingEffect::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        mode = static_cast<BlendMode>(reader.ReadInt8());
    }

    void UIBlendingEffect::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        mode = o->mode;
    }
}