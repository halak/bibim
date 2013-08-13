#include <Bibim/Config.h>
#include <Bibim/UILabel.h>
#include <Bibim/Color.h>
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
            fontRevision = -1;
        }
    }

    Vector2 UILabel::GetContentSize()
    {
        if (font)
        {
            UpdateFontString();
            return fontString.GetSize() + Vector2(font->GetShadowOffset().X, 0.0f);
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
        // context.DrawString(FontString(GetFont(), GetText()));
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
        fontStringChanged = true;
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