#include <Bibim/PCH.h>
#include <Bibim/UITransform.h>
#include <Bibim/ComponentStreamReader.h>

namespace Bibim
{
    UITransform::UITransform()
    {
    }

    UITransform::~UITransform()
    {
    }

    void UITransform::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }

    void UITransform::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
    }
}