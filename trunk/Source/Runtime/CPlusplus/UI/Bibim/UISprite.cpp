#include <Bibim/PCH.h>
#include <Bibim/UISprite.h>
#include <Bibim/Assert.h>
#include <Bibim/Colors.h>
#include <Bibim/UIDrawingContext.h>
#include <Bibim/UIFrame.h>
#include <Bibim/UIImage.h>

namespace Bibim
{
    UISprite::UISprite()
        : image(nullptr),
          autoResize(true),
          horizontalFlip(false),
          verticalFlip(false)
    {
    }

    UISprite::~UISprite()
    {
    }

    Vector2 UISprite::GetDesiredSize()
    {
        if (GetAutoResize() && GetImage())
        {
            Rectangle clippingRectangle = GetImage()->GetClippingRectangle();
            if (clippingRectangle.IsEmpty())
                clippingRectangle = GetImage()->GetRealClippingRectangle();
            if (clippingRectangle.IsEmpty() == false)
                return Vector2(clippingRectangle.Width, clippingRectangle.Height);
        }

        return UIVisual::GetDesiredSize();
    }

    void UISprite::SetImage(UIImage* value)
    {
        image = value;
    }

    void UISprite::OnDraw(UIDrawingContext& context)
    {
        UIVisual::OnDraw(context);

        if (GetImage() == nullptr || GetImage()->GetRealTexture() == nullptr)
            return;

        context.Draw(GetImage(), GetHorizontalFlip(), GetVerticalFlip());
    }
}