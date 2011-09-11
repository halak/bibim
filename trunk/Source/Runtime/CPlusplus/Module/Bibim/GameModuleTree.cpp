#include <Bibim/PCH.h>
#include <Bibim/GameModuleTree.h>
#include <Bibim/Assert.h>
#include <Bibim/GameModule.h>
#include <Bibim/GameModuleNode.h>

namespace Bibim
{
    GameModuleTree::GameModuleTree()
        : root(new GameModuleNode())
    {
        root->tree = this;
    }

    GameModuleTree::~GameModuleTree()
    {
        root->tree = nullptr;
        delete root;
    }

    GameModule* GameModuleTree::Find(uint32 id) const
    {
        if (GameModuleNode* foundNode = FindNode(id))
            return foundNode->GetModule();
        else
            return nullptr;
    }

    GameModuleNode* GameModuleTree::FindNode(uint32 id) const
    {
        UIntNodeDictionary::const_iterator it = idNodes.find(id);
        if (it != idNodes.end())
            return (*it).second;
        else
            return nullptr;
    }

    void GameModuleTree::OnModuleIDChanged(GameModule* module, uint32 oldID)
    {
        // Precondition
        BBAssertDebug(module->node && module->node->tree == this);

        if (oldID != GameModule::UnspecifiedID)
        {
            UIntNodeDictionary::iterator itOld = idNodes.find(oldID);
            if (itOld != idNodes.end())
                idNodes.erase(itOld);
        }

        const uint32 id = module->GetID();
        if (id != GameModule::UnspecifiedID)
            idNodes.insert(UIntNodeDictionary::value_type(id, module->node));
    }

    void GameModuleTree::OnNodeAttached(GameModuleNode* parent, GameModuleNode* child)
    {
        // Precondition
        BBAssertDebug(parent->tree == this);

        struct SetContainerAndRegisterID
        {
            static void Do(GameModuleTree* tree, GameModuleNode* node)
            {
                // Precondition
                BBAssertDebug(tree->idNodes.find(node->GetModule()->GetID()) == tree->idNodes.end()); // GameModuleTree���� �� Method�� ȣ���ϱ� ���� �˻��Ͽ� ���ܸ� �������մϴ�.

                node->tree = tree;

                const uint32 id = node->GetModule()->GetID();
                if (id != GameModule::UnspecifiedID)
                    tree->idNodes.insert(UIntNodeDictionary::value_type(id, node));

                typedef GameModuleNode::NodeCollection NodeCollection;
                const NodeCollection& children = node->GetChildren();
                for (NodeCollection::const_iterator it = children.begin(); it != children.end(); it++)
                    Do(tree, *it);
            }
        };

        SetContainerAndRegisterID::Do(this, child);
    }

    void GameModuleTree::OnNodeDetached(GameModuleNode* parent, GameModuleNode* child)
    {
        // Precondition
        BBAssertDebug(parent->tree == this);

        struct ResetContainerAndUnregisterID
        {
            static void Do(GameModuleTree* tree, GameModuleNode* node)
            {
                node->tree = nullptr;

                const uint32 id = node->GetModule()->GetID();
                if (id != GameModule::UnspecifiedID)
                {
                    UIntNodeDictionary::iterator it = tree->idNodes.find(id);
                    BBAssertDebug(it != tree->idNodes.end());
                    tree->idNodes.erase(it);
                }

                typedef GameModuleNode::NodeCollection NodeCollection;
                const NodeCollection& children = node->GetChildren();
                for (NodeCollection::const_iterator it = children.begin(); it != children.end(); it++)
                    Do(tree, *it);
            }
        };

        ResetContainerAndUnregisterID::Do(this, child);
    }
}