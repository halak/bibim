#pragma once
#ifndef __BIBIM_DISPLAYSWAPCHAIN_DX9_H__
#define __BIBIM_DISPLAYSWAPCHAIN_DX9_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>
#   include <Bibim/Point2.h>
#   include <Bibim/Rect.h>
#   include <d3d9.h>

    namespace Bibim
    {
        class DisplaySwapChain : public GameModule
        {
            BBModuleClass(DisplaySwapChain, GameModule, 'S', 'W', 'C', 'H');
            public:
                DisplaySwapChain(GraphicsDevice* graphicsDevice, Window* window);
                DisplaySwapChain(GraphicsDevice* graphicsDevice, Window* window, Point2 size);
                virtual ~DisplaySwapChain();

                void BeginDraw();
                void EndDraw();
                void Present();

                inline GraphicsDevice* GetGraphicsDevice() const;
                inline Window* GetWindow() const;

                inline Point2 GetBackbufferSize() const;

                inline const Rect& GetViewport() const;
                inline void SetViewport(const Rect& value);

            protected:
                DisplaySwapChain(GraphicsDevice* graphicsDevice, Window* window, void* swapChainInterface);

                void Construct(Window* window, Point2 size);

            private:
                GraphicsDevice* graphicsDevice;
                Window* window;
                Point2 backbufferSize;
                Rect viewport;

                IDirect3DSwapChain9* swapChain;
                IDirect3DSurface9* backBuffer;

                friend class GraphicsDevice;
        };
    }

#   include <Bibim/DisplaySwapChain.DX9.inl>

#endif