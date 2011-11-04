namespace Bibim
{
    UIRendererBase::Effector::Effector()
        : shaderEffectNameHint(0x00000000),
          isMaskEffector(false)
    {
    }

    UIRendererBase::Effector::Effector(uint32 shaderEffectNameHint)
        : shaderEffectNameHint(shaderEffectNameHint),
          isMaskEffector(false)
    {
    }

    UIRendererBase::Effector::Effector(bool isMaskEffector)
        : shaderEffectNameHint(0x00000000),
          isMaskEffector(isMaskEffector)
    {
    }

    UIRendererBase::Effector::Effector(uint32 shaderEffectNameHint, bool isMaskEffector)
        : shaderEffectNameHint(shaderEffectNameHint),
          isMaskEffector(isMaskEffector)
    {
    }

    uint32 UIRendererBase::Effector::GetShaderEffectNameHint() const
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