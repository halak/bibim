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
            const int width = GetImage()->GetWidth();
            const int height = GetImage()->GetHeight();
            if (width != 0 && height != 0)
                return Vector2(width, height);
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

        if (GetImage() == nullptr || GetImage()->GetTexture() == nullptr)
            return;

        context.Draw(GetImage(), GetHorizontalFlip(), GetVerticalFlip());
    }

    void UISprite::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        image = static_cast<Image*>(reader.ReadAsset());
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