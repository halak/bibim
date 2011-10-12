#include <Bibim/PCH.h>
#include <Bibim/UIVideo.h>

namespace Bibim
{
    UIVideo::UIVideo()
    {
    }

    UIVideo::~UIVideo()
    {
    }

    UIElement* UIVideo::Create(StreamReader& /*reader*/, UIElement* /*existingInstance*/)
    {
        return nullptr;
    }
}