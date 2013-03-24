#include <Bibim/PCH.h>
#include <Bibim/UILabel.h>
#include <Bibim/Colors.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/GameModuleTree.h>
#include <Bibim/Font.h>
#include <Bibim/Numerics.h>
#include <Bibim/UIDrawingContext.h>

namespace Bibim
{
    BBImplementsComponent(UILabel);

    UILabel::UILabel()
        : text(String::Empty),
          font(nullptr),
          fontString(FontString::Empty),
          fontRevision(-1)
    {
        SetSize(1.0f, 1.0f);
        SetSizeMode(ContentSize, ContentSize);
    }

    UILabel::~UILabel()
    {
    }

    Font::Metric UILabel::Measure()
    {
        return Measure(Float::Max);
    }

    Font::Metric UILabel::Measure(float boundary)
    {
        if (GetFont() == nullptr)
            return Font::Metric::Empty;
        
        UpdateFontString();
        return GetFont()->Measure(fontString, boundary);
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

    Vector2 UILabel::GetContentSize()
    {
        if (font)
        {
            UpdateFontString();
            return Vector2(fontString.GetTotalWidth(), fontString.GetFont()->GetLineHeight());
        }
        else
            return Vector2::Zero;
    }

    void UILabel::OnDraw(UIDrawingContext& context)
    {
        UIVisual::OnDraw(context);

        if (GetFont() == nullptr || GetText().IsEmpty())
            return;

        UpdateFontString();
        context.DrawString(fontString);
    }

    void UILabel::UpdateFontString()
    {
        if (fontStringChanged || fontRevision != GetFont()->GetRevision())
        {
            fontStringChanged = false;
            fontRevision = GetFont()->GetRevision();
            fontString = FontString(GetFont(), GetText());
        }
    }

    void UILabel::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        font = static_cast<Font*>(reader.ReadAsset());
        text = reader.ReadString();
    }

    void UILabel::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        font = o->font;
        text = o->text;
        fontStringChanged = true;
    }
}