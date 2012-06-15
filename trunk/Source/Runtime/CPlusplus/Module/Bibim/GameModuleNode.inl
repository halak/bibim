namespace Bibim
{
    template <typename T>
    T* GameModuleNode::CreateAndAttachChild()
    {
        T* component = new T();
        AttachChild(component);
        return component;
    }

    template <typename T> T* GameModuleNode::FindChild(bool searchAllChildren) const
    {
        return static_cast<T*>(FindChildByClassID(T::ClassID, searchAllChildren));
    }

    GameModule* GameModuleNode::GetModule() const
    {
        return module;
    }

    GameModuleNode* GameModuleNode::GetParnet() const
    {
        return parent;
    }
    
    const GameModuleNode::NodeCollection& GameModuleNode::GetChildren() const
    {
        return children;
    }

    GameModuleTree* GameModuleNode::GetTree() const
    {
        return tree;
    }

    bool GameModuleNode::IsRoot() const
    {
        return parent != nullptr && tree != nullptr;
    }
}