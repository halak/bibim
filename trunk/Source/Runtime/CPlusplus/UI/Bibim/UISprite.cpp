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
            Rect clippingRect = GetImage()->GetClippingRect();
            if (clippingRect.IsEmpty())
                clippingRect = GetImage()->GetRealClippingRect();
            if (clippingRect.IsEmpty() == false)
                return Vector2(clippingRect.Width, clippingRect.Height);
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

    UIElement* UISprite::Read(AssetStreamReader& /*reader*/, UIElement* /*existingInstance*/)
    {
        return nullptr;
    }
}