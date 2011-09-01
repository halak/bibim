#pragma once
#ifndef __BIBIM_GAMENODE_H__
#define __BIBIM_GAMENODE_H__

#   include <Bibim/FWD.h>
#   include <vector>

    namespace Bibim
    {
        class GameNode
        {
            BBThisIsNoncopyableClass(GameNode);
            public:
                typedef std::vector<GameNode*> NodeCollection;

            public:
                GameNode(GameComponent* component);
                ~GameNode();

                GameNode* AttachChild(GameComponent* item);
                void AttachChild(GameNode* item);
                bool DetachChild(GameNode* item);
                void DetachAllChildren();

                template <typename T>
                T* CreateAndAttachChild();

                GameComponent* FindChild(uint32 id, bool searchAllChildren) const;
                GameComponent* FindChildByClassID(uint32 id, bool searchAllChildren) const;
                GameNode* FindChildNode(uint32 id, bool searchAllChildren) const;
                GameNode* FindChildNode(GameComponent* item, bool searchAllChildren) const;
                GameNode* FindChildNodeByClassID(uint32 id, bool searchAllChildren) const;

                template <typename T> T* FindChild(bool searchAllChildren) const;

                inline GameComponent* GetComponent() const;
                inline GameNode* GetParnet() const;
                inline const NodeCollection& GetChildren() const;
                inline GameStructure* GetStructure() const;

                inline bool IsRoot() const;

            private:
                struct NullComponentTag {};
                GameNode(NullComponentTag);

                void OnComponentDestructed();
                void OnComponentAliveChanged();

            private:
                GameComponent* component;
                GameNode* parent;
                NodeCollection children;
                GameStructure* structure;

            private:
                friend class GameComponent;
                friend class GameStructure;
        };
    }

#   include <Bibim/GameNode.inl>

#endif