#include <Bibim/PCH.h>
#include <Bibim/GlyphSurface.h>
#include <Bibim/DynamicTexture2D.h>
#include <Bibim/RectangleStorage.h>

namespace Bibim
{
    GlyphSurface::GlyphSurface(GraphicsDevice* graphicsDevice, int width, int height)
        : storage(new RectangleStorage(width, height)),
          texture(new DynamicTexture2D(graphicsDevice, width, height, Texture2D::A8Pixels))
    {
    }

    GlyphSurface::~GlyphSurface()
    {
        delete storage;
    }

    Rectangle GlyphSurface::Allocate(const void* buffer, int width, int height, int pitch)
    {
        // Texture Filtering의 이유로 상하좌우 1Pixel씩을 비워둡니다.
        Rectangle allocatedRectangle = storage->Allocate(width + 2, height + 2);
        if (allocatedRectangle != Rectangle::Empty)
        {
            DynamicTexture2D::LockedInfo lockedInfo;
            if (texture->Lock(lockedInfo, allocatedRectangle))
            {
                // 비워둔 외곽을 투명한 Pixel로 채웁니다.
                {
                    byte* destination = static_cast<byte*>(lockedInfo.GetBuffer());
                    const int destinationPitch = lockedInfo.GetPitch() / sizeof(*destination);

                    for (int x = 0; x < allocatedRectangle.Width; x++)
                        destination[x] = 0x00;

                    destination += destinationPitch;
                    const int yFirst = 1;
                    const int yLast  = allocatedRectangle.Height - 1;
                    const int xFirst = 0;
                    const int xLast  = allocatedRectangle.Width - 1;
                    for (int y = yFirst; y < yLast; y++)
                    {
                        destination[xFirst] = 0x00;
                        destination[xLast]  = 0x00;
                        destination += destinationPitch;
                    }

                    for (int x = 0; x < allocatedRectangle.Width; x++)
                        destination[x] = 0x00;
                }

                // 문자를 기록합니다.
                {
                    byte* destination = static_cast<byte*>(lockedInfo.GetBuffer());
                    const int destinationPitch = lockedInfo.GetPitch() / sizeof(*destination);
                    const byte* source = static_cast<const byte*>(buffer);
                    const int sourcePitch = pitch;

                    destination += destinationPitch; // y로 한 Step.
                    destination += 1;                // x로 한 Step.
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

            return Rectangle(allocatedRectangle.X + 1, allocatedRectangle.Y + 1,
                             allocatedRectangle.Width - 2, allocatedRectangle.Height - 2);
        }
        else
            return Rectangle::Empty;
    }

    void GlyphSurface::Deallocate(const Rectangle& rectangle)
    {
        storage->Deallocate(rectangle);
    }
}