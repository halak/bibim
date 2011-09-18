#include <Bibim/PCH.h>
#include <Bibim/GlyphSurface.h>
#include <Bibim/DynamicTexture2D.h>
#include <Bibim/RectStorage.h>

namespace Bibim
{
    GlyphSurface::GlyphSurface(GraphicsDevice* graphicsDevice, int width, int height)
        : storage(new RectStorage(width, height)),
          texture(new DynamicTexture2D(graphicsDevice, width, height, Texture2D::A8Pixels))
    {
    }

    GlyphSurface::~GlyphSurface()
    {
        delete storage;
    }

    Rect GlyphSurface::Allocate(const void* buffer, int width, int height, int pitch)
    {
        // Texture Filtering�� ������ �����¿� 1Pixel���� ����Ӵϴ�.
        Rect allocatedRect = storage->Allocate(width + 2, height + 2);
        if (allocatedRect != Rect::Empty)
        {
            DynamicTexture2D::LockedInfo lockedInfo;
            if (texture->Lock(lockedInfo, allocatedRect))
            {
                // ����� �ܰ��� ������ Pixel�� ä��ϴ�.
                {
                    byte* destination = static_cast<byte*>(lockedInfo.GetBuffer());
                    const int destinationPitch = lockedInfo.GetPitch() / sizeof(*destination);

                    for (int x = 0; x < allocatedRect.Width; x++)
                        destination[x] = 0x00;

                    destination += destinationPitch;
                    const int yFirst = 1;
                    const int yLast  = allocatedRect.Height - 1;
                    const int xFirst = 0;
                    const int xLast  = allocatedRect.Width - 1;
                    for (int y = yFirst; y < yLast; y++)
                    {
                        destination[xFirst] = 0x00;
                        destination[xLast]  = 0x00;
                        destination += destinationPitch;
                    }

                    for (int x = 0; x < allocatedRect.Width; x++)
                        destination[x] = 0x00;
                }

                // ���ڸ� ����մϴ�.
                {
                    byte* destination = static_cast<byte*>(lockedInfo.GetBuffer());
                    const int destinationPitch = lockedInfo.GetPitch() / sizeof(*destination);
                    const byte* source = static_cast<const byte*>(buffer);
                    const int sourcePitch = pitch;

                    destination += destinationPitch; // y�� �� Step.
                    destination += 1;                // x�� �� Step.
                    for (int y = 0; y < height; ++y)
                    {
                        for (int x = 0; x < width; ++x)
                        {
                            destination[x] = source[x];
                        }
                        destination += destinationPitch;
                        source += sourcePitch;
                    }
                }

                texture->Unlock(lockedInfo);
            }

            return Rect(allocatedRect.X + 1, allocatedRect.Y + 1,
                             allocatedRect.Width - 2, allocatedRect.Height - 2);
        }
        else
            return Rect::Empty;
    }

    void GlyphSurface::Deallocate(const Rect& Rect)
    {
        storage->Deallocate(Rect);
    }
}