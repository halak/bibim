#include <Bibim/PCH.h>
#include <Bibim/GameStructure.h>
#include <Bibim/Assert.h>
#include <Bibim/GameComponent.h>
#include <Bibim/GameNode.h>

namespace Bibim
{
    GameStructure::GameStructure()
    {
        root = new GameNode(GameNode::NullComponentTag());
        root->structure = this;
    }

    GameStructure::~GameStructure()
    {
        root->structure = nullptr;
        delete root;
    }

    GameComponent* GameStructure::Find(uint32 id) const
    {
        if (GameNode* foundNode = FindNode(id))
            return foundNode->GetComponent();
        else
            return nullptr;
    }

    GameNode* GameStructure::FindNode(uint32 id) const
    {
        UIntNodeDictionary::const_iterator it = idNodes.find(id);
        if (it != idNodes.end())
            return (*it).second;
        else
            return nullptr;
    }

    uint32 GameStructure::GenerateID() const
    {
        if (idNodes.empty() == false)
        {
            const uint32 result = (*idNodes.rbegin()).second->GetComponent()->GetID() + 1;
            BBAssertDebug(idNodes.find(result) == idNodes.end());
            return result;
        }
        else
            return 1;
    }

    void GameStructure::OnComponentIDChanged(GameComponent* component, uint32 oldID)
    {
        // Precondition
        BBAssertDebug(component->node &&
                      component->node->structure == this);

        UIntNodeDictionary::iterator itOld = idNodes.find(oldID);
        if (itOld != idNodes.end())
            idNodes.erase(itOld);

        const uint32 id = component->GetID();
        if (id != GameComponent::UnspecifiedID)
            idNodes.insert(UIntNodeDictionary::value_type(id, component->node));
    }

    void GameStructure::OnGameNodeAttached(GameNode* parent, GameNode* child)
    {
        // Precondition
        BBAssertDebug(parent->structure == this);

        struct SetContainerAndRegisterID
        {
            static void Do(GameNode* node, GameStructure* structure)
            {
                // Precondition
                BBAssertDebug(structure->idNodes.find(node->GetComponent()->GetID()) == structure->idNodes.end()); // GameStructure에서 이 Method를 호출하기 전에 검사하여 예외를 던져야합니다.

                node->structure = structure;

                const uint32 id = node->GetComponent()->GetID();
                if (id != GameComponent::UnspecifiedID)
                    structure->idNodes.insert(UIntNodeDictionary::value_type(id, node));

                typedef GameNode::NodeCollection NodeCollection;
                const NodeCollection& children = node->GetChildren();
                for (NodeCollection::const_iterator it = children.begin(); it != children.end(); it++)
                    Do(*it, structure);
            }
        };

        SetContainerAndRegisterID::Do(child, this);
    }

    void GameStructure::OnGameNodeDetached(GameNode* parent, GameNode* child)
    {
        // Precondition
        BBAssertDebug(parent->structure == this);

        struct ResetContainerAndUnregisterID
        {
            static void Do(GameNode* node, GameStructure* structure)
            {
                node->structure = nullptr;

                const uint32 id = node->GetComponent()->GetID();
                if (id != GameComponent::UnspecifiedID)
                {
                    UIntNodeDictionary::iterator it = structure->idNodes.find(id);
                    BBAssertDebug(it != structure->idNodes.end());
                    structure->idNodes.erase(it);
                }

                typedef GameNode::NodeCollection NodeCollection;
                const NodeCollection& children = node->GetChildren();
                for (NodeCollection::const_iterator it = children.begin(); it != children.end(); it++)
                    Do(*it, structure);
            }
        };

        ResetContainerAndUnregisterID::Do(child, this);
    }
}