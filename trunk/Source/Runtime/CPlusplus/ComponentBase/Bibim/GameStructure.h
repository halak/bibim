#pragma once
#ifndef __BIBIM_GAMESTRUCTURE_H__
#define __BIBIM_GAMESTRUCTURE_H__

#   include <Bibim/FWD.h>
#   include <map>

    namespace Bibim
    {
        class GameStructure
        {
            BBThisIsNoncopyableClass(GameStructure);
            public:
                GameStructure();
                ~GameStructure();

                GameComponent* Find(uint32 id) const;
                GameNode* FindNode(uint32 id) const;

                inline GameNode* GetRoot() const;

            public:
                uint32 GenerateID() const;

            private:
                void OnComponentIDChanged(GameComponent* component, uint32 old); // call in GameComponent

                // 아래 Attach/Detach의 의미는 Tree로의 Attach/Detach를 의미합니다.
                // 그래서 같은 Container내에 GameComponentNode의 이동(Deatch=>Attach)에서는 호출할 필요 없다.
                void OnGameNodeAttached(GameNode* parent, GameNode* child); // call in GameComponentNode
                void OnGameNodeDetached(GameNode* parent, GameNode* child); // call in GameComponentNode

            private:
                typedef std::map<uint32, GameNode*> UIntNodeDictionary;

            private:
                GameNode* root;
                UIntNodeDictionary idNodes;

                friend class GameComponent;
                friend class GameNode;
        };
    }

#   include <Bibim/GameStructure.inl>

#endif