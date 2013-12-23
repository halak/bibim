#include <Bibim/Config.h>
#include <Bibim/UIInverseTransform.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/UIVisualVisitor.h>

namespace Bibim
{
    BBImplementsComponent(UIInverseTransform);

    UIInverseTransform::UIInverseTransform()
    {
    }

    UIInverseTransform::~UIInverseTransform()
    {
    }

    const Matrix4& UIInverseTransform::ComputeMatrix(UIVisualVisitor& context)
    {
        return context.GetCurrentTransformInv();
    }

    void UIInverseTransform::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }

    void UIInverseTransform::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
    }
}