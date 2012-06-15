namespace Bibim
{
    UIRendererBase::Effector::Effector()
        : shaderEffectNameHint(0x00000000),
          isMaskEffector(false)
    {
    }

    UIRendererBase::Effector::Effector(int shaderEffectNameHint)
        : shaderEffectNameHint(shaderEffectNameHint),
          isMaskEffector(false)
    {
    }

    UIRendererBase::Effector::Effector(bool isMaskEffector)
        : shaderEffectNameHint(0x00000000),
          isMaskEffector(isMaskEffector)
    {
    }

    UIRendererBase::Effector::Effector(int shaderEffectNameHint, bool isMaskEffector)
        : shaderEffectNameHint(shaderEffectNameHint),
          isMaskEffector(isMaskEffector)
    {
    }

    int UIRendererBase::Effector::GetShaderEffectNameHint() const
    {
        return shaderEffectNameHint;
    }

    bool UIRendererBase::Effector::IsMaskEffector() const
    {
        return isMaskEffector;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////

    //template <typename T> UIEffectorAllocator<T> UIEffectorAllocator<T>::Instance;
}