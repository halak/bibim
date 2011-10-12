#include <Bibim/PCH.h>
#include <Bibim/UIElement.h>
#include <Bibim/UIStreamReader.h>

namespace Bibim
{
    const uint UIElement::UnspecifiedID = 0xFFFFFFFF;

    UIElement::UIElement()
        : id(UnspecifiedID)
    {
    }

    UIElement::~UIElement()
    {
    }

    void UIElement::Read(StreamReader& reader, UIElement* o)
    {
        o->id = reader.ReadUInt32();
        o->name = reader.ReadString();
    }
}