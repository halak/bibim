#include <Bibim/PCH.h>
#include <Bibim/Image.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/GameAssetStorage.h>
#include <Bibim/Texture2D.h>

namespace Bibim
{
    Image::Image()
    {
        // for cloning and deserialization
    }

    Image::Image(const String& textureURI, const Rect& clippingRect)
        : textureURI(textureURI),
          clippingRect(clippingRect),
          appliedTransform(Identity),
          width(clippingRect.Width),
          height(clippingRect.Height)
    {
    }

    Image::Image(Texture2D* texture)
        : clippingRect(0, 0, texture->GetWidth(), texture->GetHeight()),
          appliedTransform(Identity),
          width(clippingRect.Width),
          height(clippingRect.Height)
    {
        Setup(texture);
    }

    Image::Image(Texture2D* texture, const Rect& clippingRect)
        : clippingRect(clippingRect),
          appliedTransform(Identity),
          width(clippingRect.Width),
          height(clippingRect.Height)
    {
        Setup(texture);
    }

    Image::Image(const String& textureURI, const Rect& clippingRect, Transform appliedTransform, Texture2D* texture)
        : textureURI(textureURI),
          clippingRect(clippingRect),
          appliedTransform(appliedTransform),
          width(0),
          height(0),
          texture(texture)
    {
        CalculateSize(width, height, clippingRect, appliedTransform);
        Setup(texture);
    }

    Image::Image(Texture2D* texture, const RectF& normalizedClippingRect, Transform appliedTransform)
        : GameAsset(CompletedStatus),
          texture(texture),
          normalizedClippingRect(normalizedClippingRect),
          appliedTransform(appliedTransform)
    {
    }

    Image::~Image()
    {
    }

    void Image::Setup(Texture2D* texture)
    {
        this->texture = texture;

        normalizedClippingRect = CalculateNormalizedRect(clippingRect, texture);
        SetStatus(texture ? CompletedStatus : FaultStatus);
    }

    void Image::CalculateSize(int& outWidth, int& outHeight, const Rect& clippingRect, Transform transform)
    {
        switch (transform)
        {
            case Identity:
                outWidth = clippingRect.Width;
                outHeight = clippingRect.Height;
                break;
            case RotateCW90:
                outWidth = clippingRect.Height;
                outHeight = clippingRect.Width;
                break;
        }
    }

    RectF Image::CalculateNormalizedRect(const Rect& clippingRect, Texture2D* texture)
    {
        if (texture)
        {
            const float w = static_cast<float>(texture->GetSurfaceWidth());
            const float h = static_cast<float>(texture->GetSurfaceHeight());
            return RectF(static_cast<float>(clippingRect.X) / w,
                         static_cast<float>(clippingRect.Y) / h,
                         static_cast<float>(clippingRect.Width) / w,
                         static_cast<float>(clippingRect.Height) / h);
        }
        else
            return RectF::Empty;
    }

    GameAsset* Image::Create(StreamReader& reader, GameAsset* /*existingInstance*/)
    {
        const String textureURI = reader.ReadString();
        const Rect clippingRect = reader.ReadRect();
        const Transform appliedTransform = static_cast<Transform>(reader.ReadByte());
        Texture2D* texture = static_cast<Texture2D*>(reader.GetStorage()->Load(textureURI));

        return new Image(textureURI, clippingRect, appliedTransform, texture);
    }
}