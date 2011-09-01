#include <Bibim/PCH.h>
#include <Bibim/UserShape2D.h>

namespace Bibim
{
    UserShape2D::UserShape2D()
        : Shape2D(Shape2D::UserType)
    {
    }

    UserShape2D::UserShape2D(IUserShape2DPtr UserShape2D)
        : Shape2D(Shape2D::UserType),
          userShape(UserShape2D)
    {
    }

    UserShape2D::~UserShape2D()
    {
    }

    IUserShape2DPtr UserShape2D::GetUserShape()
    {
        return userShape;
    }

    void UserShape2D::SerUserShape(IUserShape2DPtr value)
    {
        userShape = value;
    }

    bool UserShape2D::Raycast(const Ray2D& ray, RaycastReport2D& outReport, IRaycastCallback2D* callback)
    {
        if (userShape)
            return userShape->Raycast(this, ray, outReport, callback);
        else
            return false;
    }

    void UserShape2D::AppendTo(std::list<Vector2>& vertices)
    {
        if (userShape)
            userShape->AppendTo(this, vertices);
    }
}