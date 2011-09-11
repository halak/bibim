#pragma once
#ifndef __BIBIM_GAMEMODULE_H__
#define __BIBIM_GAMEMODULE_H__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        /// Game이란 Program을 구성하는 요소의 기반 class.
        class GameModule
        {
            BBClassFOURCC('G', 'M', 'O', 'D');
            BBThisIsNoncopyableClass(GameModule);
            public:
                enum Status
                {
                    DeadStatus,
                    AliveStatus,
                    ActiveStatus
                };

            public:
                static const uint UnspecifiedID;

            public:
                virtual ~GameModule();

                inline uint32 GetID() const;
                       void SetID(uint32 value);

                inline Status GetStatus() const;

                inline bool GetAlive() const;
                       void SetAlive(bool value);

                inline bool GetActive() const;
                       void SetActive(bool value);

                virtual void* QueryClass(uint32 classID);

            protected:
                GameModule();
                GameModule(uint32 id);

                virtual void OnStatusChanged(Status old);

            private:
                GameModuleNode* node;
                uint32 id;
                bool alive;
                bool active;

            private:
                friend class GameModuleNode;
                friend class GameModuleTree;
        };
    }

#   include <Bibim/GameModule.inl>

#endif