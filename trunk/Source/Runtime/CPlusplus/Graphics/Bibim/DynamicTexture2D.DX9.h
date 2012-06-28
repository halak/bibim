#pragma once
#ifndef __BIBIM_DYNAMICTEXTURE2D_DX9_H__
#define __BIBIM_DYNAMICTEXTURE2D_DX9_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Texture2D.h>
#   include <Bibim/Rect.h>

    namespace Bibim
    {
        class DynamicTexture2D : public Texture2D
        {
            BBAssetClass(DynamicTexture2D, Texture2D, 'D', 'T', 'X', '2');
            public:
                class LockedInfo
                {
                    BBThisIsNoncopyableClass(LockedInfo);
                    public:
                        LockedInfo();
                        ~LockedInfo();

                        inline void* GetBuffer();
                        inline int GetPitch() const;

                    private:
                        void SetData(DynamicTexture2D* texture, void* buffer, int pitch);

                    private:
                        DynamicTexture2DPtr texture;
                        void* buffer;
                        int   pitch;

                    private:
                        friend class DynamicTexture2D;
                };

            public:
                DynamicTexture2D(GraphicsDevice* graphicsDevice, int width, int height, PixelFormat pixelFormat);
                virtual ~DynamicTexture2D();

                bool Lock(LockedInfo& outLockedInfo);
                bool Lock(LockedInfo& outLockedInfo, const Rect& rect);
                void Unlock(LockedInfo& outLockedInfo);

                inline bool IsLocked() const;

            private:
                IDirect3DTexture9* d3dSystemMemoryTexture;
                IDirect3DTexture9* d3dLockableTexture;
                bool isLocked;
        };
    }

#   include <Bibim/DynamicTexture2D.DX9.inl>

#endif