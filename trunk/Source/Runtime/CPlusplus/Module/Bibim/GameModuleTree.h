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

                GameModule* Find(int id) const;
                GameModuleNode* FindNode(int id) const;

                inline GameModuleNode* GetRoot() const;

            private:
                void OnModuleIDChanged(GameModule* module, int old); // call in GameModule

                // 아래 Attach/Detach의 의미는 Tree로의 Attach/Detach를 의미합니다.
                // 그래서 같은 Container내에 GameModuleNode의 이동(Deatch=>Attach)에서는 호출할 필요 없다.
                void OnNodeAttached(GameModuleNode* parent, GameModuleNode* child); // call in GameModuleNode
                void OnNodeDetached(GameModuleNode* parent, GameModuleNode* child); // call in GameModuleNode

            private:
                typedef std::map<int, GameModuleNode*> UIntNodeDictionary;

            private:
                GameModuleNode* root;
                UIntNodeDictionary idNodes;

                friend class GameModule;
                friend class GameModuleNode;
        };
    }

#   include <Bibim/GameModuleTree.inl>

#endif