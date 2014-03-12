#include <Bibim/Config.h>
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
            // Detach를 거치지 않고 직접 제거합니다.
            NodeCollection::iterator it = std::find(oldParent->children.begin(), oldParent->children.end(), item);
            BBAssertDebug(it != oldParent->children.end());
            oldParent->children.erase(it);
            item->parent = nullptr;

            // GameModuleTree::OnNodeDetached의 명세대로 GameModuleTree가 바뀌었을 때만 호출합니다.
            if (oldParent->tree && treeChanged)
                oldParent->tree->OnNodeDetached(oldParent, item);
        }

        BBAssertDebug(item->parent == nullptr);

        item->parent = this;
        item->tree = tree;
        children.push_back(item);

        // GameModuleTree::OnNodeAttached의 명세대로 GameModuleTree가 바뀌었을 때만 호출합니다.
        if (tree && treeChanged)
            tree->OnNodeAttached(this, item);
    }

    bool GameModuleNode::DetachChild(GameModuleNode* item)
    {
        BBAssert(item);

        if (item->parent != this || item->tree != this->tree)
            return false;

        NodeCollection::iterator it = std::find(children.begin(), children.end(), item);
        BBAssertDebug(it != children.end()); // 이미 item의 부모가 this인지 확인했기 때문에 반드시 있어야합니다.
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
            for (NodeCollection::reverse_iterator it = temporaryChildren.rbegin(); it != temporaryChildren.rend(); ++it)
            {
                tree->OnNodeDetached(this, *it);
                delete (*it);
            }
        }
        else
        {
            for (NodeCollection::reverse_iterator it = temporaryChildren.rbegin(); it != temporaryChildren.rend(); ++it)
                delete (*it);
        }
    }

    GameModule* GameModuleNode::FindChild(int id) const
    {
        if (GameModuleNode* foundNode = FindChildNode(id))
            return foundNode->GetModule();
        else
            return nullptr;
    }

    GameModule* GameModuleNode::FindChildByClassID(int id) const
    {
        if (GameModuleNode* foundNode = FindChildNodeByClassID(id))
            return foundNode->GetModule();
        else
            return nullptr;
    }

    GameModuleNode* GameModuleNode::FindChildNode(int id) const
    {
        if (id == GameModule::UnspecifiedID)
            return nullptr;

        for (NodeCollection::const_iterator it = children.begin(); it != children.end(); ++it)
        {
            if ((*it)->GetModule() && (*it)->GetModule()->GetID() == id)
                return (*it);
        }

        for (NodeCollection::const_iterator it = children.begin(); it != children.end(); ++it)
        {
            if (GameModuleNode* foundNode = (*it)->FindChildNode(id))
                return foundNode;
        }

        return nullptr;
    }

    GameModuleNode* GameModuleNode::FindChildNodeByClassID(int id) const
    {
        for (NodeCollection::const_iterator it = children.begin(); it != children.end(); ++it)
        {
            if ((*it)->GetModule() && (*it)->GetModule()->GetClassID() == id)
                return (*it);
        }

        for (NodeCollection::const_iterator it = children.begin(); it != children.end(); ++it)
        {
            if (GameModuleNode* foundNode = (*it)->FindChildNodeByClassID(id))
                return foundNode;
        }

        return nullptr;
    }

    GameModuleNode* GameModuleNode::FindChildNode(GameModule* item) const
    {
        // 원래는 모든 자식 Node들을 순회하며 검사해야하지만,
        // GameModule에서 자신을 가진 Node를 아는 관계로 최적화할 수 있었습니다.
        // GameModule의 조상Node중 this가 있는지 확인합니다.

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
        // Alive => 상위 GameModule와 하위 GameModule들을 모두 Alive로 만듭니다.
        // Dead  => 하위 GameModule들을 모두 Dead상태로 만듭니다.

        const bool alive = module->GetAlive();

        if (alive && parent)
            parent->module->SetAlive(true);
        for (NodeCollection::iterator it = children.begin(); it != children.end(); ++it)
            (*it)->module->SetAlive(alive);
    }
}