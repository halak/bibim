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
                    VSUnknown,
                    VSNotSupported,
                    VS1X,
                    VS20,
                    VS20Ex,
                    VS30,
                    VS40,
                    VSUpperVersion,
                };

                enum PixelShader
                {
                    PSUnknown,
                    PSNotSupported,
                    PS1X,
                    PS20,
                    PS20Ex,
                    PS30,
                    PS40,
                    PSUpperVersion,
                };

            public:
                GraphicsCapabilities();
                GraphicsCapabilities(const GraphicsCapabilities& original);
                ~GraphicsCapabilities();

                inline const DisplayModeCollection& GetDisplayModes() const;
                inline VertexShader GetVertexShaderVersion() const;
                inline PixelShader  GetPixelShaderVersion() const;

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
    }

#   include <Bibim/GraphicsCapabilities.inl>

#endif