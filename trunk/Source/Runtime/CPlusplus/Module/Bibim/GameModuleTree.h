#pragma once
#ifndef __BIBIM_GAMEMODULETREE_H__
#define __BIBIM_GAMEMODULETREE_H__

#   include <Bibim/FWD.h>
#   include <map>

    namespace Bibim
    {
        class GameModuleTree
        {
            BBThisIsNoncopyableClass(GameModuleTree);
            public:
                GameModuleTree();
                ~GameModuleTree();

                GameModule* Find(uint32 id) const;
                GameModuleNode* FindNode(uint32 id) const;

                inline GameModuleNode* GetRoot() const;

            private:
                void OnModuleIDChanged(GameModule* module, uint32 old); // call in GameModule

                // �Ʒ� Attach/Detach�� �ǹ̴� Tree���� Attach/Detach�� �ǹ��մϴ�.
                // �׷��� ���� Container���� GameModuleNode�� �̵�(Deatch=>Attach)������ ȣ���� �ʿ� ����.
                void OnNodeAttached(GameModuleNode* parent, GameModuleNode* child); // call in GameModuleNode
                void OnNodeDetached(GameModuleNode* parent, GameModuleNode* child); // call in GameModuleNode

            private:
                typedef std::map<uint32, GameModuleNode*> UIntNodeDictionary;

            private:
                GameModuleNode* root;
                UIntNodeDictionary idNodes;

                friend class GameModule;
                friend class GameModuleNode;
        };
    }

#   include <Bibim/GameModuleTree.inl>

#endif