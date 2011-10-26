#include <Bibim/PCH.h>
#include <Bibim/GraphicsCapabilities.h>

namespace Bibim
{
    GraphicsCapabilities::DisplayMode::DisplayMode(int width, int height, int bitsPerPixel, int refreshRate)
        : Width(width),
          Height(height),
          BitsPerPixel(bitsPerPixel),
          RefreshRate(refreshRate)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    GraphicsCapabilities::GraphicsCapabilities()
        : vertexShaderVersion(VSUnknown),
          pixelShaderVersion(PSUnknown)
    {
    }

    GraphicsCapabilities::GraphicsCapabilities(const GraphicsCapabilities& original)
    {
        operator = (original);
    }

    GraphicsCapabilities::~GraphicsCapabilities()
    {
    }

    GraphicsCapabilities& GraphicsCapabilities::operator = (const GraphicsCapabilities& right)
    {
        displayModes = right.displayModes;
        vertexShaderVersion = right.vertexShaderVersion;
        pixelShaderVersion = right.pixelShaderVersion;
        return *this;
    }
}