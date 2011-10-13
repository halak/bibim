#include <Bibim/PCH.h>
#include <Bibim/UILayout.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/GameComponentFactory.h>
#include <Bibim/UIWindow.h>

namespace Bibim
{
    UILayout::UILayout()
    {
    }

    UILayout::UILayout(UIWindow* root)
        : root(root)
    {
    }

    UILayout::~UILayout()
    {
    }

    GameAsset* UILayout::Create(StreamReader& reader, GameAsset* /*existingInstance*/)
    {
        ComponentStreamReader uiReader(reader.GetSource(), reader.GetModules());
        return new UILayout(static_cast<UIWindow*>(uiReader.ReadComponent()));
    }
}