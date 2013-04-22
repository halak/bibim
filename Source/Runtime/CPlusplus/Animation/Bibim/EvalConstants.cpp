#include <Bibim/Config.h>
#include <Bibim/EvalConstants.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/GameAsset.h>

namespace Bibim
{
    BBImplementsComponent(EvalGameAssetConstant);

    EvalGameAssetConstant::EvalGameAssetConstant()
        : value()
    {
    }

    EvalGameAssetConstant::EvalGameAssetConstant(GameAsset* value)
        : value(value)
    {
    }

    EvalGameAssetConstant::~EvalGameAssetConstant()
    {
    }

    GameAsset* EvalGameAssetConstant::Evaluate(EvalContext& /*context*/)
    {
        return value;
    }

    void EvalGameAssetConstant::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        value = reader.ReadAsset();
    }

    void EvalGameAssetConstant::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        value = o->value;
    }
}