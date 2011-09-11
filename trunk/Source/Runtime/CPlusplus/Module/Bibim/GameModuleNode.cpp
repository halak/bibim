#include <Bibim/PCH.h>
#include <Bibim/GameModuleNode.h>
#include <Bibim/Assert.h>
#include <Bibim/GameModule.h>
#include <Bibim/GameModuleTree.h>
#include <algorithm>

namespace Bibim
{
    GameModuleNode::GameModuleNode()
        : module(nullptr),
          parent(nullptr),
          tree(nullptr)
    {
    }

    GameModuleNode::GameModuleNode(GameModule* module)
        : module(module),
          parent(nullptr),
          tree(nullptr)
    {
        BBAssert(module);
    }

    GameModuleNode::GameModuleNode(GameModule* module, int childrenCapacity)
        : module(module),
          parent(nullptr),
          tree(nullptr)
    {
        BBAssert(module);
        children.reserve(childrenCapacity);
    }

    GameModuleNode::~GameModuleNode()
    {
        DetachAllChildren();

        if (module)
        {
            GameModule* temporaryModule = nullptr;
            std::swap(temporaryModule, module);
     
            temporaryModule->node = nullptr;
            delete temporaryModule;
        }
    }

    GameModuleNode* GameModuleNode::AttachChild(GameModule* item)
    {
        BBAssert(item);

        if (item->node == nullptr)
            item->node = new GameModuleNode(item);

        AttachChild(item->node);

        return item->node;
    }

    void GameModuleNode::AttachChild(GameModuleNode* item)
    {
        BBAssert(item);

        if (item->parent == this)
        {
            BBAssertDebug(std::find(children.begin(), children.end(), item) != children.end());
            return;
        }

        const bool treeChanged = (item->parent == nullptr || item->parent->tree != tree);

        if (GameModuleNode* oldParent = item->parent)
        {
            // Detach�� ��ġ�� �ʰ� ���� �����մϴ�.
            NodeCollection::iterator it = std::find(oldParent->children.begin(), oldParent->children.end(), item);
            BBAssertDebug(it != oldParent->children.end());
            oldParent->children.erase(it);
            item->parent = nullptr;

            // GameModuleTree::OnNodeDetached�� ����� GameModuleTree�� �ٲ���� ���� ȣ���մϴ�.
            if (oldParent->tree && treeChanged)
                oldParent->tree->OnNodeDetached(oldParent, item);
        }

        BBAssertDebug(item->parent == nullptr);

        item->parent = this;
        item->tree = tree;
        children.push_back(item);

        // GameModuleTree::OnNodeAttached�� ����� GameModuleTree�� �ٲ���� ���� ȣ���մϴ�.
        if (tree && treeChanged)
            tree->OnNodeAttached(this, item);
    }

    bool GameModuleNode::DetachChild(GameModuleNode* item)
    {
        BBAssert(item);

        if (item->parent != this || item->tree != this->tree)
            return false;

        NodeCollection::iterator it = std::find(children.begin(), children.end(), item);
        BBAssertDebug(it != children.end()); // �̹� item�� �θ� this���� Ȯ���߱� ������ �ݵ�� �־���մϴ�.
        children.erase(it);

        item->parent = nullptr;

        if (tree)
            tree->OnNodeDetached(this, item);

        delete item;

        return true;
    }

    void GameModuleNode::DetachAllChildren()
    {
        NodeCollection temporaryChildren;
        temporaryChildren.swap(children);

        if (tree)
        {
            for (NodeCollection::reverse_iterator it = temporaryChildren.rbegin(); it != temporaryChildren.rend(); it++)
            {
                tree->OnNodeDetached(this, *it);
                delete (*it);
            }
        }
        else
        {
            for (NodeCollection::reverse_iterator it = temporaryChildren.rbegin(); it != temporaryChildren.rend(); it++)
                delete (*it);
        }
    }

    GameModule* GameModuleNode::FindChild(uint32 id) const
    {
        if (GameModuleNode* foundNode = FindChildNode(id))
            return foundNode->GetModule();
        else
            return nullptr;
    }

    GameModule* GameModuleNode::FindChildByClassID(uint32 id) const
    {
        if (GameModuleNode* foundNode = FindChildNodeByClassID(id))
            return foundNode->GetModule();
        else
            return nullptr;
    }

    GameModuleNode* GameModuleNode::FindChildNode(uint32 id) const
    {
        if (id == GameModule::UnspecifiedID)
            return nullptr;

        for (NodeCollection::const_iterator it = children.begin(); it != children.end(); it++)
        {
            if ((*it)->GetModule() && (*it)->GetModule()->GetID() == id)
                return (*it);
        }

        for (NodeCollection::const_iterator it = children.begin(); it != children.end(); it++)
        {
            if (GameModuleNode* foundNode = (*it)->FindChildNode(id))
                return foundNode;
        }

        return nullptr;
    }

    GameModuleNode* GameModuleNode::FindChildNodeByClassID(uint32 id) const
    {
        for (NodeCollection::const_iterator it = children.begin(); it != children.end(); it++)
        {
            if ((*it)->GetModule() && (*it)->GetModule()->GetClassID() == id)
                return (*it);
        }

        for (NodeCollection::const_iterator it = children.begin(); it != children.end(); it++)
        {
            if (GameModuleNode* foundNode = (*it)->FindChildNodeByClassID(id))
                return foundNode;
        }

        return nullptr;
    }

    GameModuleNode* GameModuleNode::FindChildNode(GameModule* item) const
    {
        // ������ ��� �ڽ� Node���� ��ȸ�ϸ� �˻��ؾ�������,
        // GameModule���� �ڽ��� ���� Node�� �ƴ� ����� ����ȭ�� �� �־����ϴ�.
        // GameModule�� ����Node�� this�� �ִ��� Ȯ���մϴ�.

        if (item->node == nullptr || item->node->tree != tree)
            return nullptr;

        struct ThisIsAncestor
        {
            static bool Do(GameModuleNode* descendant, const GameModuleNode* ancestor)
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

    void GameModuleNode::OnModuleDestructed()
    {
        module = nullptr;
    }

    void GameModuleNode::OnModuleAliveChanged()
    {
        // Alive => ���� GameModule�� ���� GameModule���� ��� Alive�� ����ϴ�.
        // Dead  => ���� GameModule���� ��� Dead���·� ����ϴ�.

        const bool alive = module->GetAlive();

        if (alive && parent)
            parent->module->SetAlive(true);
        for (NodeCollection::iterator it = children.begin(); it != children.end(); it++)
            (*it)->module->SetAlive(alive);
    }
}