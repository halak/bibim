#include <Bibim/PCH.h>
#include <Bibim/UIVideo.h>

namespace Bibim
{
    BBImplementsComponent(UIVideo);

    UIVideo::UIVideo()
    {
    }

    UIVideo::~UIVideo()
    {
    }

    void UIVideo::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }

    void UIVideo::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
    }
}