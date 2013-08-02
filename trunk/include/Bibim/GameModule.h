﻿#pragma once
#ifndef __BIBIM_GAMEMODULE_H__
#define __BIBIM_GAMEMODULE_H__

#include <Bibim/FWD.h>
#include <Bibim/Object.h>

namespace Bibim
{
#   define BBAbstractModuleClass(classname, parent) private: \
                                                        typedef classname This; \
                                                        typedef parent Base;
#   define BBModuleClass(classname, parent, a, b, c, d) private: \
                                                            typedef classname This; \
                                                            typedef parent Base; \
                                                        public: \
                                                            static const int ClassID = BBMakeFOURCC(a, b, c, d); \
                                                            virtual int GetClassID() const { return ClassID; } \
                                                        private:

    /// Game이란 Program을 구성하는 요소의 기반 class.
    class GameModule : public Object
    {
        BBAbstractModuleClass(GameModule, Object);
        BBThisIsNoncopyableClass(GameModule);
        public:
            enum Status
            {
                DeadStatus,
                AliveStatus,
                ActiveStatus
            };

        public:
            static const int UnspecifiedID;

        public:
            virtual ~GameModule();

            inline int GetID() const;
                   void SetID(int value);

            inline Status GetStatus() const;

            inline bool GetAlive() const;
                   void SetAlive(bool value);

            inline bool GetActive() const;
                   void SetActive(bool value);

            virtual void* QueryClass(int classID);

        protected:
            GameModule();
            GameModule(int id);

            virtual void OnStatusChanged(Status old);

        private:
            GameModuleNode* node;
            int id;
            bool alive;
            bool active;

        private:
            friend class GameModuleNode;
            friend class GameModuleTree;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    int GameModule::GetID() const
    {
        return id;
    }

    GameModule::Status GameModule::GetStatus() const
    {
        if (alive)
        {
            if (active)
                return ActiveStatus;
            else
                return AliveStatus;
        }
        else
            return DeadStatus;
    }

    bool GameModule::GetAlive() const
    {
        return alive;
    }

    bool GameModule::GetActive() const
    {
        return active;
    }
}

#endif