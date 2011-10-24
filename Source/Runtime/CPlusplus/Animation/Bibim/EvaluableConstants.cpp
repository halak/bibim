#include <Bibim/PCH.h>
#include <Bibim/EvaluableConstants.h>
#include <Bibim/GameAsset.h>
#include <Bibim/EvaluableRangedSequences.h>

namespace Bibim
{
    BBImplementsComponent(EvaluableGameAssetConstant);

    EvaluableGameAssetConstant::EvaluableGameAssetConstant()
        : value()
    {
    }

    EvaluableGameAssetConstant::EvaluableGameAssetConstant(GameAsset* value)
        : value(value)
    {
    }

    EvaluableGameAssetConstant::~EvaluableGameAssetConstant()
    {
    }

    GameAsset* EvaluableGameAssetConstant::Evaluate(EvaluationContext& /*context*/)
    {
        return value;
    }

    void EvaluableGameAssetConstant::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        value = reader.ReadAsset();
    }

    void EvaluableGameAssetConstant::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        value = o->value;
    }
}