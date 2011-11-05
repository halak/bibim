#include <Bibim/PCH.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/EvalConstants.h>
#include <Bibim/GameAsset.h>
#include <Bibim/EvalRangedSequences.h>

namespace Bibim
{
    BBImplementsComponent(EvalGameAssetConstant);

    EvalGameAssetConstant::EvalGameAssetConstant()
        : value()
    {
        BoolSequence s;
        AssetStreamReader r("", nullptr, nullptr);
        BoolSequence::Create(r, nullptr);
    }

    EvalGameAssetConstant::EvalGameAssetConstant(GameAsset* value)
        : value(value)
    {
    }

    EvalGameAssetConstant::~EvalGameAssetConstant()
    {
    }

    GameAsset* EvalGameAssetConstant::Evaluate(EvaluationContext& /*context*/)
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