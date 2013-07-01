namespace Bibim
{
    GameModuleNode* GameModuleTree::GetRoot() const
    {
        return root;
    }

    template <typename T> T* GameModuleTree::FindModule() const
    {
        return static_cast<T*>(root->FindChildByClassID(T::ClassID));
    }
}