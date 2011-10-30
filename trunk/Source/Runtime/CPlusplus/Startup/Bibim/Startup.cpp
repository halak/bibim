#include <Bibim/Startup.h>
#include <Bibim/All.h>

namespace Bibim
{
    void Startup::All()
    {
        GameAssetFactory::AddEntry<Image>();
        GameAssetFactory::AddEntry<Script>();
        GameAssetFactory::AddEntry<SourceTexture2D>();
        GameAssetFactory::AddEntry<ShaderEffect>();
        GameAssetFactory::AddEntry<UILayout>();
        GameAssetFactory::SortEntries();

        GameComponentFactory::AddEntry<UISineCurveEffect>();
        GameComponentFactory::AddEntry<UITintEffect>();
        GameComponentFactory::AddEntry<UIColorMatrixEffect>();
        GameComponentFactory::AddEntry<UIOpacityMaskEffect>();
        GameComponentFactory::AddEntry<UIEffectMap>();
        GameComponentFactory::AddEntry<UIFunctionEventHandler>();
        GameComponentFactory::AddEntry<UISequentialEventHandler>();
        GameComponentFactory::AddEntry<UIEventMap>();
        GameComponentFactory::AddEntry<UIAlignedFrame>();
        GameComponentFactory::AddEntry<UIFittedFrame>();
        GameComponentFactory::AddEntry<UIFixedFrame>();
        GameComponentFactory::AddEntry<UITransform3D>();
        GameComponentFactory::AddEntry<UILabel>();
//      GameComponentFactory::AddEntry<UIMarkupTextBox>();
        GameComponentFactory::AddEntry<UIPanel>();
        GameComponentFactory::AddEntry<UIButton>();
        GameComponentFactory::AddEntry<UICheckBox>();
        GameComponentFactory::AddEntry<UIWindow>();
        GameComponentFactory::AddEntry<UISprite>();
        GameComponentFactory::AddEntry<UIVideo>();
        GameComponentFactory::SortEntries();

        BBBeginScriptNativeFunction()
            BBScriptNativeFunction(ScriptLibrary::IO::Print)
        BBEndScriptNativeFunction();
    }
}