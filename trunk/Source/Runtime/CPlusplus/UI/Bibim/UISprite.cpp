#include <Bibim/PCH.h>
#include <Bibim/UISprite.h>
#include <Bibim/Assert.h>
#include <Bibim/Colors.h>
#include <Bibim/UIDrawingContext.h>
#include <Bibim/UIFrame.h>
#include <Bibim/UIImage.h>
#include <Bibim/UIStreamReader.h>

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

    UIElement* UISprite::Create(StreamReader& reader, UIElement* /*existingInstance*/)
    {
        UISprite* o = new UISprite();
        UIVisual::Read(reader, o);

        const String textureURI = reader.ReadString();
        const Rect clippingRect = reader.ReadRect();
        o->image = new UIImage(textureURI, clippingRect);
        o->autoResize = reader.ReadBool();
        o->horizontalFlip = reader.ReadBool();
        o->verticalFlip = reader.ReadBool();

        return o;
    }
}