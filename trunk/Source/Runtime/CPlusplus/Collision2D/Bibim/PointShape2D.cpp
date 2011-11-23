#include <Bibim/PCH.h>
#include <Bibim/PointShape2D.h>

namespace Bibim
{
    BBImplementsComponent(PointShape2D);

    PointShape2D::PointShape2D()
        : Shape2D(Shape2D::PointType)
    {
    }

    PointShape2D::~PointShape2D()
    {
    }

    bool PointShape2D::Raycast(Vector2 /*origin*/, Vector2 /*direction*/, float /*length*/, RaycastReport2D& /*outReport*/, IRaycastCallback2D* /*callback*/)
    {
        return false;
    }

    void PointShape2D::AppendTo(std::list<Vector2>& vertices)
    {
        vertices.push_back(GetPosition());
    }

    void PointShape2D::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }

    void PointShape2D::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
    }
}