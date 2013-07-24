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

                template <typename T> T* FindChild() const;

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

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        template <typename T>
        T* GameModuleNode::CreateAndAttachChild()
        {
            T* component = new T();
            AttachChild(component);
            return component;
        }

        template <typename T> T* GameModuleNode::FindChild() const
        {
            return static_cast<T*>(FindChildByClassID(T::ClassID));
        }

        GameModule* GameModuleNode::GetModule() const
        {
            return module;
        }

        GameModuleNode* GameModuleNode::GetParnet() const
        {
            return parent;
        }
        
        const GameModuleNode::NodeCollection& GameModuleNode::GetChildren() const
        {
            return children;
        }

        GameModuleTree* GameModuleNode::GetTree() const
        {
            return tree;
        }

        bool GameModuleNode::IsRoot() const
        {
            return parent != nullptr && tree != nullptr;
        }
    }

#endif