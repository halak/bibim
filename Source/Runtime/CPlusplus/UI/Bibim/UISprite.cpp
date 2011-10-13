#include <Bibim/PCH.h>
#include <Bibim/UISprite.h>
#include <Bibim/Assert.h>
#include <Bibim/Colors.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Image.h>
#include <Bibim/UIDrawingContext.h>
#include <Bibim/UIFrame.h>

namespace Bibim
{
    BBImplementsComponent(UISprite);

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

    void UISprite::SetImage(Image* value)
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

    void UISprite::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        const String textureURI = reader.ReadString();
        const Rect clippingRect = reader.ReadRect();
        image = new Image(textureURI, clippingRect);
        autoResize = reader.ReadBool();
        horizontalFlip = reader.ReadBool();
        verticalFlip = reader.ReadBool();
    }

    void UISprite::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        image = o->image;
        autoResize = o->autoResize;
        horizontalFlip = o->horizontalFlip;
        verticalFlip = o->verticalFlip;
    }
}