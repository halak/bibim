#pragma once
#ifndef __BIBIM_GRAPHICSCAPABILITIES_H__
#define __BIBIM_GRAPHICSCAPABILITIES_H__

#   include <Bibim/FWD.h>
#   include <vector>

    namespace Bibim
    {
        class GraphicsCapabilities
        {
            public:
                struct DisplayMode
                {
                    int Width;
                    int Height;
                    int BitsPerPixel;
                    int RefreshRate;

                    DisplayMode(int width, int height, int bitsPerPixel, int refreshRate);
                };
                typedef std::vector<DisplayMode> DisplayModeCollection;

                enum VertexShader
                {
                    VSUnknown = -1,
                    VSNotSupported = 0,
                    VS1x = 10,
                    VS20 = 20,
                    VS2x = 25,
                    VS30 = 30,
                    VS40 = 40,
                    VSUpperVersion = 1000,
                };

                enum PixelShader
                {
                    PSUnknown = -1,
                    PSNotSupported = 0,
                    PS1x = 10,
                    PS20 = 20,
                    PS2x = 25,
                    PS30 = 30,
                    PS40 = 40,
                    PSUpperVersion = 1000,
                };

            public:
                GraphicsCapabilities();
                GraphicsCapabilities(const GraphicsCapabilities& original);
                ~GraphicsCapabilities();

                inline const DisplayModeCollection& GetDisplayModes() const;
                inline VertexShader GetVertexShaderVersion() const;
                inline PixelShader  GetPixelShaderVersion() const;
                inline bool IsShaderSupported() const;

                GraphicsCapabilities& operator = (const GraphicsCapabilities& right);

            private:
                DisplayModeCollection displayModes;
                VertexShader vertexShaderVersion;
                PixelShader  pixelShaderVersion;

                friend class GraphicsDevice;
        };

        typedef GraphicsCapabilities GraphicsCaps;
        typedef GraphicsCapabilities::DisplayMode DisplayMode;
        typedef GraphicsCapabilities::DisplayModeCollection DisplayModeCollection;
        typedef GraphicsCapabilities::VertexShader VertexShaderVersion;
        typedef GraphicsCapabilities::PixelShader PixelShaderVersion;

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        const GraphicsCapabilities::DisplayModeCollection& GraphicsCapabilities::GetDisplayModes() const
        {
            return displayModes;
        }

        GraphicsCapabilities::VertexShader GraphicsCapabilities::GetVertexShaderVersion() const
        {
            return vertexShaderVersion;
        }

        GraphicsCapabilities::PixelShader GraphicsCapabilities::GetPixelShaderVersion() const
        {
            return pixelShaderVersion;
        }

        bool GraphicsCapabilities::IsShaderSupported() const
        {
            return vertexShaderVersion >= VS20 && pixelShaderVersion >= PS20;
        }
    }

#endif