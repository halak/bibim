#include <Bibim/PCH.h>
#include <Bibim/UIImage.h>
#include <Bibim/Assert.h>
#include <Bibim/BitMask.h>
#include <Bibim/Colors.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Image.h>
#include <Bibim/UIDrawingContext.h>
#include <Bibim/UIPickingContext.h>

namespace Bibim
{
    BBImplementsComponent(UIImage);

    UIImage::UIImage()
        : source(nullptr),
          autoResize(true),
          horizontalFlip(false),
          verticalFlip(false)
    {
        SetSize(1.0f, 1.0f);
        SetSizeMode(ContentSize, ContentSize);
    }

    UIImage::~UIImage()
    {
    }

    void UIImage::SetSource(Image* value)
    {
        source = value;
    }

    Texture2D* UIImage::GetTexture() const
    {
        if (source)
            return source->GetTexture();
        else
            return nullptr;
    }

    void UIImage::SetTexture(Texture2D* value)
    {
        source = new Image(value);
    }

    Vector2 UIImage::GetContentSize()
    {
        if (source)
            return Vector2(source->GetWidth(), source->GetHeight());
        else
            return Vector2::Zero;
    }

    void UIImage::OnDraw(UIDrawingContext& context)
    {
        UIVisual::OnDraw(context);

        if (GetSource() == nullptr || GetSource()->GetTexture() == nullptr)
            return;

        context.Draw(GetSource(), GetHorizontalFlip(), GetVerticalFlip());
    }

    void UIImage::OnPick(UIPickingContext& context)
    {
        if (GetPickable() && context.Contains(context.GetCurrentClippedBounds()))
        {
            if (mask == nullptr || source == nullptr)
                context.SetResult(this);
            else
            {
                const RectF unclippedBounds = context.GetCurrentBounds();
                const Rect clippingRect = source->GetClippingRect();

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

    void UIImage::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        source = static_cast<Image*>(reader.ReadAsset());
        autoResize = reader.ReadBool();
        horizontalFlip = reader.ReadBool();
        verticalFlip = reader.ReadBool();
        mask = static_cast<BitMask*>(reader.ReadAsset());
    }

    void UIImage::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        source = o->source;
        autoResize = o->autoResize;
        horizontalFlip = o->horizontalFlip;
        verticalFlip = o->verticalFlip;
        mask = o->mask;
    }
}