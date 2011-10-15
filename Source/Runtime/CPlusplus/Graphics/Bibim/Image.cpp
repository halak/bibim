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
          clippingRect(clippingRect)
    {
    }

    Image::Image(const String& textureURI, const Rect& clippingRect, Texture2D* texture)
        : textureURI(textureURI),
          clippingRect(clippingRect),
          texture(texture)
    {
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
            const float w = static_cast<float>(texture->GetWidth());
            const float h = static_cast<float>(texture->GetHeight());
            this->normalizedClippingRect.X = static_cast<float>(clippingRect.X) / w;
            this->normalizedClippingRect.Y = static_cast<float>(clippingRect.Y) / h;
            this->normalizedClippingRect.Width = static_cast<float>(clippingRect.Width) / w;
            this->normalizedClippingRect.Height = static_cast<float>(clippingRect.Height) / h;
        }
        else
            this->normalizedClippingRect = RectF::Empty;
    }

    GameAsset* Image::Create(StreamReader& reader, GameAsset* /*existingInstance*/)
    {
        const String textureURI = reader.ReadString();
        const Rect clippingRect = reader.ReadRect();
        Texture2D* texture = static_cast<Texture2D*>(reader.GetStorage()->Load(textureURI));

        return new Image(textureURI, clippingRect, texture);
    }
}