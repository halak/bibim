#include <Bibim/PCH.h>
#include <Bibim/UIFrame.h>
#include <Bibim/Exception.h>

namespace Bibim
{
    UIFrame::UIFrame()
    {
    }

    UIFrame::~UIFrame()
    {
    }

    void UIFrame::Move(Vector2 /*displacement*/)
    {
        BBThrow(NotSupportedException());
    }

    bool UIFrame::IsMovable() const
    {
        return false;
    }

    void UIFrame::Resize(float /*left*/, float /*top*/, float /*right*/, float /*bottom*/)
    {
        BBThrow(NotSupportedException());
    }

    void UIFrame::ResizeTo(Vector2 /*size*/)
    {
        BBThrow(NotSupportedException());
    }

    bool UIFrame::IsResizable() const
    {
        return false;
    }

    void UIFrame::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }

    void UIFrame::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
    }
}