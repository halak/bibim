#include <Bibim/Config.h>
#include <Bibim/UIEditText.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Math.h>

namespace Bibim
{
    BBImplementsComponent(UIEditText);

    UIEditText::UIEditText()
        : ime(nullptr),
          format(IME::Plain),
          maxLength(IME::NO_MAX_LENGTH),
          frozen(false)
    {
    }

    UIEditText::~UIEditText()
    {
    }

    void UIEditText::SetIME(IME* value)
    {
        if (ime != value)
        {
            ime = value;
        }
    }

    void UIEditText::SetFormat(IME::TextFormat value)
    {
        if (format != value)
        {
            format = value;
        }
    }

    void UIEditText::SetMaxLength(int value)
    {
        value = Math::Max(value, 0);

        if (maxLength != value)
        {
            maxLength = value;
        }
    }

    void UIEditText::OnDraw(UIDrawingContext& context)
    {
        if (GetText().IsEmpty() && GetFont() && GetPlaceholder().IsEmpty() == false)
        {
            SetText(GetPlaceholder());
            Base::OnDraw(context);
            SetText(String::Empty);
        }
        else
            Base::OnDraw(context);
    }

    bool UIEditText::OnMouseClick(const UIMouseEventArgs& /*args*/)
    {
        if (ime == nullptr || frozen)
            return true;

        String editorDescription = GetEditorDescription();
        if (editorDescription.IsEmpty())
            editorDescription = GetPlaceholder();

        int maxLength = GetMaxLength();
        if (GetFormat() == IME::Number)
            maxLength = Math::Min(maxLength, 12);

        ime->Edit(GetText(),
                  GetEditorTitle(),
                  editorDescription,
                  GetFormat(),
                  maxLength,
                  this);

        return true;
    }

    void UIEditText::OnTextEdited(const String& text)
    {
        SetText(text);
    }

    void UIEditText::OnTextEditCancelled()
    {
    }

    void UIEditText::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        format = static_cast<IME::TextFormat>(reader.ReadByte());
        placeholder = reader.ReadString();
        maxLength = reader.ReadInt();
        frozen = reader.ReadBool();
        editorTitle = reader.ReadString();
        editorDescription = reader.ReadString();
    }

    void UIEditText::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        format = o->format;
        placeholder = o->placeholder;
        maxLength = o->maxLength;
        frozen = o->frozen;
        editorTitle = o->editorTitle;
        editorDescription = o->editorDescription;
    }

    IME::TextFormat UIEditText::ConvertFromStringToFormat(const char* value)
    {
             if (value == nullptr)                                       return IME::Plain;
        else if (String::EqualsCharsIgnoreCase(value, "Number"))         return IME::Number;
        else if (String::EqualsCharsIgnoreCase(value, "Email"))          return IME::Email;
        else if (String::EqualsCharsIgnoreCase(value, "Password"))       return IME::Password;
        else                                                             return IME::Plain;
    }

    const char* UIEditText::ConvertFromFormatToString(IME::TextFormat value)
    {
        switch (value)
        {
            case IME::Plain:    return "Plain";
            case IME::Number:   return "Number";
            case IME::Email:    return "Email";
            case IME::Password: return "Password";
            default:            return "Default";
        }
    }
}