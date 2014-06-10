#include <Bibim/Config.h>
#include <Bibim/GlyphSurface.h>
#include <Bibim/DynamicTexture2D.h>
#include <Bibim/RectStorage.h>

namespace Bibim
{
    GlyphSurface::GlyphSurface(GraphicsDevice* graphicsDevice, int width, int height)
        : texture(new DynamicTexture2D(graphicsDevice, width, height, Texture2D::A8Pixels))
    {
        storages[0].Clear(width, height);
        storages[1].Clear(width, height);
        storages[2].Clear(width, height);
        storages[3].Clear(width, height);
    }

    GlyphSurface::~GlyphSurface()
    {
    }

    GlyphSurface::Slot GlyphSurface::Allocate(const void* buffer, int width, int height, int pitch)
    {
//        Slot slot;
//
//#       if (defined(BIBIM_USE_DIRECTX9))
//        static const int RED   = 2;
//        static const int GREEN = 1;
//        static const int BLUE  = 0;
//        static const int ALPHA = 3;
//#       else
//        static const int RED   = 0;
//        static const int GREEN = 1;
//        static const int BLUE  = 2;
//        static const int ALPHA = 3;
//#       endif
//
//        slot = Allocate(0, RED, buffer, width, height, pitch);
//        if (slot.ClippingRect != Rect::Empty)
//            return slot;
//
//        slot = Allocate(1, GREEN, buffer, width, height, pitch);
//        if (slot.ClippingRect != Rect::Empty)
//            return slot;
//
//        slot = Allocate(2, BLUE, buffer, width, height, pitch);
//        if (slot.ClippingRect != Rect::Empty)
//            return slot;

        return Allocate(0, 0, buffer, width, height, pitch);
    }

    GlyphSurface::Slot GlyphSurface::Allocate(int depth, int component, const void* buffer, int width, int height, int pitch)
    {
        BBAssertDebug(0 <= depth && depth < sizeof(storages) / sizeof(storages[0]));

        // Texture Filtering의 이유로 상하좌우 1Pixel씩을 비워둡니다.
        Rect allocatedRect = storages[depth].Allocate(width + 2, height + 2);
        if (allocatedRect != Rect::Empty)
        {
            DynamicTexture2D::LockedInfo lockedInfo;
            if (texture->Lock(lockedInfo, allocatedRect))
            {
                static const int STRIDE = 1;

                // 비워둔 외곽을 투명한 Pixel로 채웁니다.
                {
                    byte* destination = static_cast<byte*>(lockedInfo.GetBuffer()) + component;
                    const int destinationPitch = lockedInfo.GetPitch() / sizeof(*destination);

                    for (int x = 0; x < allocatedRect.Width; x++)
                        destination[x * STRIDE] = 0x00;

                    destination += destinationPitch;
                    const int yFirst = 1;
                    const int yLast  = allocatedRect.Height - 1;
                    const int xFirst = 0;
                    const int xLast  = allocatedRect.Width - 1;
                    for (int y = yFirst; y < yLast; y++)
                    {
                        destination[xFirst * STRIDE] = 0x00;
                        destination[xLast  * STRIDE] = 0x00;
                        destination += destinationPitch;
                    }

                    for (int x = 0; x < allocatedRect.Width; x++)
                        destination[x * STRIDE] = 0x00;
                }

                // 문자를 기록합니다.
                {
                    byte* destination = static_cast<byte*>(lockedInfo.GetBuffer()) + component;
                    const int destinationPitch = lockedInfo.GetPitch() / sizeof(*destination);
                    const byte* source = static_cast<const byte*>(buffer);
                    const int sourcePitch = pitch;

                    destination += destinationPitch; // y로 한 Step.
                    destination += 1 * STRIDE;       // x로 한 Step.
                    for (int y = 0; y < height; ++y)
                    {
                        for (int x = 0; x < width; ++x)
                        {
                            destination[x * STRIDE] = source[x];
                        }
                        destination += destinationPitch;
                        source += sourcePitch;
                    }
                }

                texture->Unlock(lockedInfo);
            }

            return Slot(depth, Rect(allocatedRect.X + 1, allocatedRect.Y + 1,
                                    allocatedRect.Width - 2, allocatedRect.Height - 2));
        }
        else
            return Slot(0, Rect::Empty);
    }

    void GlyphSurface::Deallocate(const GlyphSurface::Slot& slot)
    {
        storages[slot.Depth].Deallocate(slot.ClippingRect);
    }
}