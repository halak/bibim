#include <Bibim/PCH.h>
#include <Bibim/UILabel.h>
#include <Bibim/Colors.h>
#include <Bibim/Font.h>
#include <Bibim/UIDrawingContext.h>

namespace Bibim
{
    BBImplementsComponent(UILabel);

    UILabel::UILabel()
        : text(String::Empty),
          font(nullptr),
          fontString(FontString::Empty),
          autoResize(true)
    {
    }

    UILabel::~UILabel()
    {
    }

    void UILabel::SetText(const String& value)
    {
        if (text != value)
        {
            text = value;
            fontStringChanged = true;
        }
    }

    void UILabel::SetFont(Font* value)
    {
        if (font != value)
        {
            font = value;
            fontStringChanged = true;
        }
    }

    void UILabel::SetAutoResize(bool value)
    {
        if (autoResize != value)
        {
            autoResize = value;
        }
    }

    void UILabel::OnDraw(UIDrawingContext& context)
    {
        UIVisual::OnDraw(context);

        if (GetFont() == nullptr || GetText().IsEmpty())
            return;

        if (fontStringChanged)
        {
            fontStringChanged = false;
            fontString = FontString(GetFont(), GetText());
        }

        context.DrawString(fontString);
    }

    void UILabel::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }

    void UILabel::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
    }
}