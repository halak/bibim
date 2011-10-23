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
        switch (appliedTransform)
        {
            case Identity:
                width = clippingRect.Width;
                height = clippingRect.Height;
                break;
            case RotateCW90:
                width = clippingRect.Height;
                height = clippingRect.Width;
                break;
        }

        Setup(texture);
    }

    Image::~Image()
    {
    }

    void Image::Setup(Texture2D* texture)
    {
        this->texture = texture;

        if (texture)
        {
            const float w = static_cast<float>(texture->GetSurfaceWidth());
            const float h = static_cast<float>(texture->GetSurfaceHeight());
            this->normalizedClippingRect.X = static_cast<float>(clippingRect.X) / w;
            this->normalizedClippingRect.Y = static_cast<float>(clippingRect.Y) / h;
            this->normalizedClippingRect.Width = static_cast<float>(clippingRect.Width) / w;
            this->normalizedClippingRect.Height = static_cast<float>(clippingRect.Height) / h;

            SetStatus(CompletedStatus);
        }
        else
        {
            this->normalizedClippingRect = RectF::Empty;
            SetStatus(FaultStatus);
        }
    }

    GameAsset* Image::Create(StreamReader& reader, GameAsset* /*existingInstance*/)
    {
        const String textureURI = reader.ReadString();
        const Rect clippingRect = reader.ReadRect();
        const Transform appliedTransform = static_cast<Transform>(reader.ReadUInt8());
        Texture2D* texture = static_cast<Texture2D*>(reader.GetStorage()->Load(textureURI));

        return new Image(textureURI, clippingRect, appliedTransform, texture);
    }
}