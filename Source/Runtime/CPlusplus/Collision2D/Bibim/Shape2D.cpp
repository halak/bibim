#include <Bibim/Config.h>
#include <Bibim/Shape2D.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/IntersectShapes2D.h>

namespace Bibim
{
    Shape2D::Shape2D(Type type)
        : type(type),
          position(Vector2::Zero),
          rotation(0.0f),
          scale(1.0f),
          revision(0)
    {
    }

    Shape2D::~Shape2D()
    {
    }

    void Shape2D::SetPosition(Vector2 value)
    {
        if (GetPosition() != value)
        {
            position = value;
            revision++;
        }
    }

    void Shape2D::SetRotation(float value)
    {
        if (GetRotation() != value)
        {
            rotation = value;
            revision++;
        }
    }

    void Shape2D::SetScale(float value)
    {
        if (GetScale() != value)
        {
            scale = value;
            revision++;
        }
    }

    bool Shape2D::Intersect(Shape2D* left, Shape2D* right)
    {
        return IntersectShapes2D::Test(left, right);
    }

    void Shape2D::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        position = reader.ReadVector2();
        rotation = reader.ReadFloat();
        scale = reader.ReadFloat();
        revision = 0;
    }

    void Shape2D::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        position = o->position;
        rotation = o->rotation;
        scale = o->scale;
        revision = o->revision;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    Shape2D::SimpleVertices::SimpleVertices()
    {
    }

    Shape2D::SimpleVertices::~SimpleVertices()
    {
    }

    void Shape2D::SimpleVertices::Clear()
    {
        v.clear();
    }

    void Shape2D::SimpleVertices::Append(Vector2 p0)
    {
        v.push_back(p0);
    }

    void Shape2D::SimpleVertices::Append(Vector2 p0, Vector2 p1)
    {
        v.push_back(p0);
        v.push_back(p1);
    }

    void Shape2D::SimpleVertices::Append(Vector2 p0, Vector2 p1, Vector2 p2)
    {
        v.push_back(p0);
        v.push_back(p1);
        v.push_back(p2);
    }

    void Shape2D::SimpleVertices::Append(Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3)
    {
        v.push_back(p0);
        v.push_back(p1);
        v.push_back(p2);
        v.push_back(p3);
    }

    void Shape2D::SimpleVertices::Append(const std::vector<Vector2>& p)
    {
        v.insert(v.end(), p.begin(), p.end());
    }
}