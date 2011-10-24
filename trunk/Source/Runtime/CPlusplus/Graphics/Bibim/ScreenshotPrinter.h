#pragma once
#ifndef __BIBIM_SCREENSHOTPRINTER_H__
#define __BIBIM_SCREENSHOTPRINTER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>

    namespace Bibim
    {
        class ScreenshotPrinter : public GameModule
        {
            BBModuleClass(ScreenshotPrinter, GameModule, 'S', 'S', 'P', 'R');
            public:
                ScreenshotPrinter();
                ScreenshotPrinter(GraphicsDevice* graphicsDevice);
                virtual ~ScreenshotPrinter();

                void BeginDraw();
                void EndDraw();

                inline GraphicsDevice* GetGraphicsDevice() const;
                void SetGraphicsDevice(GraphicsDevice* value);

            private:
                GraphicsDevice* graphicsDevice;
                RenderTargetTexture2DPtr renderTarget;
        };
    }

#   include <Bibim/ScreenshotPrinter.inl>

#endif