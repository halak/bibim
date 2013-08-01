#include <Bibim/Config.h>
#include <Bibim/UserShape2D.h>

namespace Bibim
{
    UserShape2D::UserShape2D()
        : Shape2D(Shape2D::UserType)
    {
    }

    UserShape2D::~UserShape2D()
    {
    }

    void UserShape2D::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }

    void UserShape2D::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
    }
}