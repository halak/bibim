#pragma once
#ifndef __BIBIM_DYNAMICTEXTURE2D_GLES2_H__
#define __BIBIM_DYNAMICTEXTURE2D_GLES2_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Texture2D.GLES2.h>
#   include <Bibim/Rect.h>
#   include <vector>

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
                        inline Rect GetRect() const;

                    private:
                        void SetData(DynamicTexture2D* texture, void* buffer, int pitch, Rect rect);

                    private:
                        DynamicTexture2DPtr texture;
                        void* buffer;
                        int   pitch;
                        Rect  rect;

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

                virtual GLuint GetHandle();

            private:
                std::vector<byte> surface;
                int pitch;
                bool isLocked;
                Rect dirtyRect;
        };
    }

#endif