#include <Bibim/PCH.h>
#include <Bibim/UITransform2D.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Matrix4.h>

namespace Bibim
{
    BBImplementsComponent(UITransform2D);

    UITransform2D::UITransform2D()
    {
    }

    UITransform2D::~UITransform2D()
    {
    }

    const Matrix4& UITransform2D::ComputeMatrix(UIVisualVisitor& /*context*/)
    {
        return Matrix4::Identity;
    }

    void UITransform2D::Reset()
    {
    }

    void UITransform2D::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }

    void UITransform2D::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        // const This* o = static_cast<const This*>(original);
    }
}