namespace Bibim
{
    template <typename T>
    T* GameNode::CreateAndAttachChild()
    {
        T* component = new T();
        AttachChild(component);
        return component;
    }

    template <typename T> T* GameNode::FindChild(bool searchAllChildren) const
    {
        return static_cast<T*>(FindChildByClassID(T::ClassID, searchAllChildren));
    }

    GameComponent* GameNode::GetComponent() const
    {
        return component;
    }

    GameNode* GameNode::GetParnet() const
    {
        return parent;
    }
    
    const GameNode::NodeCollection& GameNode::GetChildren() const
    {
        return children;
    }

    GameStructure* GameNode::GetStructure() const
    {
        return structure;
    }

    bool GameNode::IsRoot() const
    {
        return parent != nullptr;
    }
}