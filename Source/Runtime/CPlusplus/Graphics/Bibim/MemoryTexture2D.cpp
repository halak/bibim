#include <Bibim/PCH.h>
#include <Bibim/MemoryTexture2D.h>
#include <Bibim/GraphicsDevice.h>
#include <Bibim/Assert.h>
#include <Bibim/Color.h>

namespace Bibim
{
    MemoryTexture2D::MemoryTexture2D(GraphicsDevice* graphicsDevice, int width, int height, int pitch, const std::vector<byte>& red, const std::vector<byte>& green, const std::vector<byte>& blue)
        : Texture2D(graphicsDevice)
    {
        Construct(width, height, pitch, &red[0], red.size(), &green[0], green.size(), &blue[0], blue.size(), nullptr, 0);
    }

    MemoryTexture2D::MemoryTexture2D(GraphicsDevice* graphicsDevice, int width, int height, int pitch, const std::vector<byte>& red, const std::vector<byte>& green, const std::vector<byte>& blue, const std::vector<byte>& alpha)
        : Texture2D(graphicsDevice)
    {
        Construct(width, height, pitch, &red[0], red.size(), &green[0], green.size(), &blue[0], blue.size(), &alpha[0], alpha.size());
    }

    MemoryTexture2D::~MemoryTexture2D()
    {
    }

    void MemoryTexture2D::Construct(int width, int height, int /*pitch*/, const byte* red, int redSize, const byte* green, int greenSize, const byte* blue, int blueSize, const byte* alpha, int alphaSize)
    {
        BBStaticAssert(sizeof(Color) == 4);
        BBAssert(alpha == nullptr || (redSize == greenSize && greenSize == blueSize && blueSize == alphaSize));

        this->width  = width;
        this->height = height;

        if (red && green && blue)
        {
            this->pitch  = width * sizeof(Color);
            this->format = Texture2D::ARGB32Pixels;
            this->buffer.resize(this->pitch * this->height);

            if (alpha)
            {
                for (std::vector<byte>::size_type i = 0, k = 0; i < this->buffer.size(); i += sizeof(Color), k++)
                {
                    this->buffer[i + 0] = blue [k];
                    this->buffer[i + 1] = green[k];
                    this->buffer[i + 2] = red  [k];
                    this->buffer[i + 3] = alpha[k];
                }
            }
            else
            {
                for (std::vector<byte>::size_type i = 0, k = 0; i < this->buffer.size(); i += sizeof(Color), k++)
                {
                    this->buffer[i + 0] = blue [k];
                    this->buffer[i + 1] = green[k];
                    this->buffer[i + 2] = red  [k];
                    this->buffer[i + 3] = 0xFF;
                }
            }
        }
        else
        {
            if (alpha)
            {
                this->pitch  = width;
                this->format = Texture2D::A8Pixels;
                this->buffer.resize(width * height);

                for (std::vector<byte>::size_type i = 0; i < this->buffer.size(); i++)
                    this->buffer[i] = alpha[i];
            }
        }
    }

    Texture2D::D3DTextureInfo MemoryTexture2D::CreateD3DTexture()
    {
        D3DFORMAT d3dFormat = D3DFMT_UNKNOWN;
        switch (format)
        {
            case Texture2D::ARGB32Pixels:
                d3dFormat = D3DFMT_A8R8G8B8;
                break;
            case Texture2D::A8Pixels:
                d3dFormat = D3DFMT_A8;
                break;
        }

        IDirect3DTexture9* newD3DTexture = NULL;
        HRESULT result = D3DXCreateTexture(GetGraphicsDevice()->GetD3DDevice(), width, height, 0, D3DUSAGE_DYNAMIC, d3dFormat, D3DPOOL_DEFAULT, &newD3DTexture);
        if (result == D3D_OK)
        {
            D3DLOCKED_RECT lockInfo = { 0, };
            RECT d3dLockingRect = { 0, 0, width, height };

            HRESULT result = newD3DTexture->LockRect(0, &lockInfo, &d3dLockingRect, 0x00000000);
            if (result == D3D_OK)
            {
                switch (format)
                {
                    case Texture2D::ARGB32Pixels:
                        {
                            const Color* source = reinterpret_cast<const Color*>(&buffer[0]);
                            const int sourcePitch = this->pitch / sizeof(Color);

                            Color* destination = static_cast<Color*>(lockInfo.pBits);
                            const int destinationPitch = lockInfo.Pitch / sizeof(Color);

                            for (int y = 0; y < this->height; y++)
                            {
                                for (int x = 0; x < this->width; x++)
                                {
                                    destination[x] = source[x];
                                }
                                source      += sourcePitch;
                                destination += destinationPitch;
                            }
                        }
                        break;
                    case Texture2D::A8Pixels:
                        throw std::exception("Not Implemented.");
                }

                newD3DTexture->UnlockRect(0);
            }

            D3DSURFACE_DESC surfaceDesc;
            if (newD3DTexture->GetLevelDesc(0, &surfaceDesc) == D3D_OK)
            {
                return D3DTextureInfo(newD3DTexture, width, height,
                                      static_cast<int>(surfaceDesc.Width), static_cast<int>(surfaceDesc.Height));
            }
            else
                return D3DTextureInfo(newD3DTexture, width, height);
        }
        else
            return D3DTextureInfo();
    }
}