#include <Bibim/PCH.h>
#include <Bibim/UISprite.h>
#include <Bibim/Assert.h>
#include <Bibim/BitMask.h>
#include <Bibim/Colors.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Image.h>
#include <Bibim/UIDrawingContext.h>
#include <Bibim/UIPickingContext.h>

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

    void UISprite::OnPick(UIPickingContext& context)
    {
        if (GetPickable() && context.Contains(context.GetCurrentClippedBounds()))
        {
            if (mask == nullptr || image == nullptr)
                context.SetResult(this);
            else
            {
                const RectF unclippedBounds = context.GetCurrentBounds();
                const Rect clippingRect = image->GetClippingRect();

                Vector2 p = context.GetCurrentPoint();
                p.X -= unclippedBounds.X;
                p.Y -= unclippedBounds.Y;
                p.X *= static_cast<float>(clippingRect.Width) / unclippedBounds.Width;
                p.Y *= static_cast<float>(clippingRect.Height) / unclippedBounds.Height;
                p.X += 0.5f;
                p.Y += 0.5f;

                if (mask->GetPixel(static_cast<int>(p.X), static_cast<int>(p.Y)))
                    context.SetResult(this);
            }
        }
    }

    void UISprite::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        image = static_cast<Image*>(reader.ReadAsset());
        autoResize = reader.ReadBool();
        horizontalFlip = reader.ReadBool();
        verticalFlip = reader.ReadBool();
        mask = static_cast<BitMask*>(reader.ReadAsset());
    }

    void UISprite::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        image = o->image;
        autoResize = o->autoResize;
        horizontalFlip = o->horizontalFlip;
        verticalFlip = o->verticalFlip;
        mask = o->mask;
    }
}