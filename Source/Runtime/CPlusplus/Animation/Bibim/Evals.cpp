#include <Bibim/Config.h>
#include <Bibim/Evals.h>

namespace Bibim
{
    EvalBase::EvalBase()
    {
    }

    void EvalBase::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }

    void EvalBase::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
    }
}