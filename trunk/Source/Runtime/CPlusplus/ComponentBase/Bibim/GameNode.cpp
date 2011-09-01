#include <Bibim/PCH.h>
#include <Bibim/GameNode.h>
#include <Bibim/Assert.h>
#include <Bibim/Exception.h>
#include <Bibim/GameComponent.h>
#include <Bibim/GameStructure.h>
#include <algorithm>

namespace Bibim
{
    GameNode::GameNode(GameComponent* component)
        : component(component),
          parent(nullptr),
          structure(nullptr)
    {
        BBAssert(component);
    }
  
    GameNode::GameNode(NullComponentTag)
        : component(nullptr),
          parent(nullptr),
          structure(nullptr)
    {
    }

    GameNode::~GameNode()
    {
        DetachAllChildren();

        if (component)
        {
            GameComponent* temporaryComponent = nullptr;
            std::swap(temporaryComponent, component);
     
            temporaryComponent->node = nullptr;
            delete temporaryComponent;
        }
    }

    GameNode* GameNode::AttachChild(GameComponent* item)
    {
        BBAssert(item);

        if (item->node == nullptr)
            item->node = new GameNode(item);

        AttachChild(item->node);

        return item->node;
    }

    void GameNode::AttachChild(GameNode* item)
    {
        BBAssert(item);

        if (item->parent == this)
            return;

        const bool structureChanged = (item->parent == nullptr || item->parent->structure != structure);

        if (GameNode* oldParent = item->parent)
        {
            NodeCollection::iterator it = std::find(oldParent->children.begin(), oldParent->children.end(), item);
            BBAssertDebug(it != oldParent->children.end());

            oldParent->children.erase(it);
            item->parent = nullptr;

            // GameStructure::OnGameNodeDetached�� ����� GameStructure�� �ٲ���� ���� ȣ���մϴ�.
            if (oldParent->structure && structureChanged)
                oldParent->structure->OnGameNodeDetached(oldParent, item);
        }

        item->parent = this;
        children.push_back(item);

        // GameStructure::OnGameNodeAttached�� ����� GameStructure�� �ٲ���� ���� ȣ���մϴ�.
        if (structure && structureChanged)
            structure->OnGameNodeAttached(this, item);
    }

    bool GameNode::DetachChild(GameNode* item)
    {
        BBAssert(item);

        if (item->parent != this || item->structure != this->structure)
            return false;

        NodeCollection::iterator it = std::find(children.begin(), children.end(), item);
        BBAssertDebug(it != children.end()); // �̹� item�� �θ� this���� Ȯ���߱� ������ �ݵ�� �־���մϴ�.

        children.erase(it);
        item->parent = nullptr;

        if (structure)
            structure->OnGameNodeDetached(this, item);

        delete item;

        return true;
    }

    void GameNode::DetachAllChildren()
    {
        NodeCollection temporaryChildren;
        temporaryChildren.swap(children);

        for (NodeCollection::reverse_iterator it = temporaryChildren.rbegin(); it != temporaryChildren.rend(); it++)
        {
            if (structure)
                structure->OnGameNodeDetached(this, *it);

            delete (*it);
        }
    }

    GameComponent* GameNode::FindChild(uint32 id, bool searchAllChildren) const
    {
        if (GameNode* foundNode = FindChildNode(id, searchAllChildren))
            return foundNode->GetComponent();
        else
            return nullptr;
    }

    GameComponent* GameNode::FindChildByClassID(uint32 id, bool searchAllChildren) const
    {
        if (GameNode* foundNode = FindChildNodeByClassID(id, searchAllChildren))
            return foundNode->GetComponent();
        else
            return nullptr;
    }

    GameNode* GameNode::FindChildNode(uint32 id, bool searchAllChildren) const
    {
        if (id == GameComponent::UnspecifiedID)
            return nullptr;

        if (searchAllChildren)
        {
            for (NodeCollection::const_iterator it = children.begin(); it != children.end(); it++)
            {
                if ((*it)->GetComponent() && (*it)->GetComponent()->GetID() == id)
                    return (*it);
                if (GameNode* foundNode = (*it)->FindChildNode(id, true))
                    return foundNode;
            }
        }
        else
        {
            for (NodeCollection::const_iterator it = children.begin(); it != children.end(); it++)
            {
                if ((*it)->GetComponent() && (*it)->GetComponent()->GetID() == id)
                    return (*it);
            }
        }

        return nullptr;
    }

    GameNode* GameNode::FindChildNodeByClassID(uint32 id, bool searchAllChildren) const
    {
        if (searchAllChildren)
        {
            for (NodeCollection::const_iterator it = children.begin(); it != children.end(); it++)
            {
                if ((*it)->GetComponent() && (*it)->GetComponent()->GetClassID() == id)
                    return (*it);
                if (GameNode* foundNode = (*it)->FindChildNodeByClassID(id, true))
                    return foundNode;
            }
        }
        else
        {
            for (NodeCollection::const_iterator it = children.begin(); it != children.end(); it++)
            {
                if ((*it)->GetComponent() && (*it)->GetComponent()->GetClassID() == id)
                    return (*it);
            }
        }

        return nullptr;
    }

    GameNode* GameNode::FindChildNode(GameComponent* item, bool searchAllChildren) const
    {
        // ������ ��� �ڽ� Node���� ��ȸ�ϸ� �˻��ؾ�������,
        // GameComponent���� �ڽ��� ���� Node�� �ƴ� ����� ����ȭ�� �� �־����ϴ�.
        // searchAllChildren == true  : GameComponent�� ����Node�� this�� �ִ��� Ȯ���մϴ�.
        //                   == false : GameComponent�� �θ�Node�� this���� Ȯ���մϴ�.

        if (item->node == nullptr || item->node->structure != structure)
            return nullptr;

        if (searchAllChildren)
        {
            struct ThisIsAncestor
            {
                static bool Do(GameNode* descendant, const GameNode* ancestor)
                {
                    if (descendant->parent == nullptr)
                        return false;

                    if (descendant->parent == ancestor)
                        return true;
                    else
                        return Do(descendant->parent, ancestor);
                }
            };

            if (ThisIsAncestor::Do(item->node, this))
                return item->node;
            else
                return nullptr;
        }
        else
        {
            if (item->node->parent == this)
            {
                BBAssertDebug(std::find(children.begin(), children.end(), item->node) != children.end());
                return item->node;
            }
            else
                return nullptr;
        }
    }

    void GameNode::OnComponentDestructed()
    {
        component = nullptr;
    }

    void GameNode::OnComponentAliveChanged()
    {
        // Alive => ���� GameComponent�� ���� GameComponent���� ��� Alive�� ����ϴ�.
        // Dead  => ���� GameComponent���� ��� Dead���·� ����ϴ�.

        const bool alive = component->GetAlive();

        if (alive && parent)
            parent->component->SetAlive(true);
        for (NodeCollection::iterator it = children.begin(); it != children.end(); it++)
            (*it)->component->SetAlive(alive);
    }
}