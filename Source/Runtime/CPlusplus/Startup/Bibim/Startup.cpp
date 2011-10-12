#include <Bibim/Startup.h>
#include <Bibim/All.h>

namespace Bibim
{
    void Startup::All()
    {
        GameAssetFactory::AddEntry<Script>();
        GameAssetFactory::AddEntry<SourceTexture2D>();
        GameAssetFactory::AddEntry<UILayout>();
        GameAssetFactory::SortEntries();

        UIElementFactory::AddEntry<UIImage>();
        UIElementFactory::AddEntry<UITintEffect>();
        UIElementFactory::AddEntry<UIEffectMap>();
        UIElementFactory::AddEntry<UIFunctionEventHandler>();
        UIElementFactory::AddEntry<UISequentialEventHandler>();
        UIElementFactory::AddEntry<UIEventMap>();
        UIElementFactory::AddEntry<UIAlignedFrame>();
        UIElementFactory::AddEntry<UIFittedFrame>();
        UIElementFactory::AddEntry<UIFixedFrame>();
        UIElementFactory::AddEntry<UITransform3D>();
        UIElementFactory::AddEntry<UILabel>();
//      UIElementFactory::AddEntry<UIMarkupTextBox>();
        UIElementFactory::AddEntry<UIPanel>();
        UIElementFactory::AddEntry<UIButton>();
        UIElementFactory::AddEntry<UICheckBox>();
        UIElementFactory::AddEntry<UIWindow>();
        UIElementFactory::AddEntry<UISprite>();
        UIElementFactory::AddEntry<UIVideo>();
        UIElementFactory::SortEntries();

        BBBeginScriptNativeFunction()
            BBScriptNativeFunction(ScriptLibrary::IO::Print)
        BBEndScriptNativeFunction();
    }
}