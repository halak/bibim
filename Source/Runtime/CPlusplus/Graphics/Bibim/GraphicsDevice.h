#pragma once
#ifndef __BIBIM_GRAPHICSDEVICE_H__
#define __BIBIM_GRAPHICSDEVICE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>
#   include <Bibim/Color.h>
#   include <Bibim/Rect.h>
#   include <vector>
#   include <d3d9.h>

    namespace Bibim
    {
        class GraphicsDevice : public GameModule
        {
            BBModuleClass(GraphicsDevice, GameModule, 'G', 'R', 'P', 'D');
            public:
                GraphicsDevice();
                virtual ~GraphicsDevice();

                void Clear();
                void Clear(Color color);

                void BeginDraw();
                void EndDraw();
                void Present();

                inline Window* GetWindow() const;
                void SetWindow(Window* value);

                inline bool GetFullscreen() const;
                void SetFullscreen(bool value);

                inline const Rect& GetViewport() const;
                void SetViewport(const Rect& value);

                DisplaySwapChain* GetDefaultSwapChain();

                inline IDirect3D9*       GetD3DObject();
                inline IDirect3DDevice9* GetD3DDevice();

            private:
                void InitializeDevice();
                void FinalizeDevice();

                void AcquireDefaultSwapChain();

                void Add(DisplaySwapChain* item);
                void Remove(DisplaySwapChain* item);

            private:
                IDirect3D9*       d3dObject;
                IDirect3DDevice9* d3dDevice;
                Window* window;

                DisplaySwapChain* defaultSwapChain;
                std::vector<DisplaySwapChain*> swapChains;

                Rect viewport;
                bool fullscreen;

                friend class DisplaySwapChain;
        };
    }

#   include <Bibim/GraphicsDevice.inl>

#endif