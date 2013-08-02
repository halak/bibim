#include <Bibim/UIEventHandler.h>

namespace Bibim
{
    UIEventHandler::UIEventHandler()
    {
    }

    UIEventHandler::~UIEventHandler()
    {
    }

    bool UIEventHandler::IsSequence() const
    {
        return false;
    }

    void UIEventHandler::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }

    void UIEventHandler::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
    }
}