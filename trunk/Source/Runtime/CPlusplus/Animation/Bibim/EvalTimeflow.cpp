#include <Bibim/PCH.h>
#include <Bibim/EvalTimeflow.h>

namespace Bibim
{
    BBImplementsComponent(EvalTimeflow);

    EvalTimeflow::EvalTimeflow()
    {
    }

    EvalTimeflow::~EvalTimeflow()
    {
    }

    void EvalTimeflow::Reset()
    {
    }

    float EvalTimeflow::Evaluate(EvalContext& context)
    {
        return 0.0f;
    }

    void EvalTimeflow::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }

    void EvalTimeflow::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
    }
}