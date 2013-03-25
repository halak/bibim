#include <Bibim/PCH.h>
#include <Bibim/UIEditText.h>
#include <Bibim/ComponentStreamReader.h>

namespace Bibim
{
    BBImplementsComponent(UIEditText);

    UIEditText::UIEditText()
    {
    }

    UIEditText::~UIEditText()
    {
    }
            
    void UIEditText::SetFormat(Format value)
    {
        if (format != value)
        {
            format = value;
        }
    }

    void UIEditText::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        format = static_cast<Format>(reader.ReadByte());
        frozen = reader.ReadBool();
    }

    void UIEditText::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        format = o->format;
        frozen = o->frozen;
    }
}