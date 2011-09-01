#pragma once
#ifndef __BIBIM_DISPLAYSWAPCHAIN_H__
#define __BIBIM_DISPLAYSWAPCHAIN_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameComponent.h>

    namespace Bibim
    {
        class DisplaySwapChain : public GameComponent
        {
            BBClassFOURCC('S', 'W', 'C', 'H');
            public:
                DisplaySwapChain(GraphicsDevice* graphicsDevice, Window* window);
                DisplaySwapChain(GraphicsDevice* graphicsDevice, Window* window, Point size);
                virtual ~DisplaySwapChain();

                void BeginDraw();
                void EndDraw();
                void Present();

                GraphicsDevice* GetGraphicsDevice() const;
                Window* GetWindow() const;

                Point GetBackbufferSize() const;

                const Rectangle& GetViewport() const;
                void SetViewport(const Rectangle& value);

            protected:
                DisplaySwapChain(GraphicsDevice* graphicsDevice, Window* window, void* swapChainInterface);

                void Construct(Window* window, Point size);

            private:
                struct Fields;
                Fields* mPointer;
                Fields& m;

                friend class GraphicsDevice;
        };
    }

#endif