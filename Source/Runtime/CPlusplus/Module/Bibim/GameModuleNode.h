#pragma once
#ifndef __BIBIM_GAMEMODULENODE_H__
#define __BIBIM_GAMEMODULENODE_H__

#   include <Bibim/FWD.h>
#   include <vector>

    namespace Bibim
    {
        class GameModuleNode
        {
            BBThisIsNoncopyableClass(GameModuleNode);
            public:
                typedef std::vector<GameModuleNode*> NodeCollection;

            public:
                explicit GameModuleNode();
                explicit GameModuleNode(GameModule* module);
                GameModuleNode(GameModule* module, int childrenCapacity);
                ~GameModuleNode();

                GameModuleNode* AttachChild(GameModule* item);
                void AttachChild(GameModuleNode* item);
                bool DetachChild(GameModuleNode* item);
                void DetachAllChildren();

                template <typename T>
                T* CreateAndAttachChild();

                GameModule* FindChild(int id) const;
                GameModule* FindChildByClassID(int id) const;
                GameModuleNode* FindChildNode(int id) const;
                GameModuleNode* FindChildNode(GameModule* item) const;
                GameModuleNode* FindChildNodeByClassID(int id) const;

                template <typename T> T* FindChild(bool searchAllChildren) const;

                inline GameModule* GetModule() const;
                inline GameModuleNode* GetParnet() const;
                inline const NodeCollection& GetChildren() const;
                inline GameModuleTree* GetTree() const;

                inline bool IsRoot() const;

            private:
                void OnModuleDestructed();
                void OnModuleAliveChanged();

            private:
                GameModule* module;
                GameModuleNode* parent;
                NodeCollection children;
                GameModuleTree* tree;

            private:
                friend class GameModule;
                friend class GameModuleTree;
        };
    }

#   include <Bibim/GameModuleNode.inl>

#endif