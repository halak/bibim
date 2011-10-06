#pragma once
#ifndef __BIBIM_SCRIPTPROCESS_H__
#define __BIBIM_SCRIPTPROCESS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>

    namespace Bibim
    {
        class ScriptProcess : public SharedObject
        {
            BBObjectClass(ScriptProcess, SharedObject, 'S', 'C', 'P', 'S');
            public:
                enum CommandID
                {
                    JumpCommand = 0,
                    IfTrueThenJumpCommand = 1,
                    IfFalseThenJumpCommand = 2,
                    IfTrueThenJumpElseJumpCommand = 3,
                    IfFalseThenJumpElseJumpCommand = 4,
                    CallCommand = 5,
                    CallNativeCommand = 6,
                    ReturnCommand = 7,
                    YieldCommand = 8,
                };
  
            public:
                ScriptProcess(Script* script);
                virtual ~ScriptProcess();

                void Resume();
                void Suspend();

            private:
                ScriptPtr script;
                uint position;
        };
    }

#   include <Bibim/ScriptProcess.inl>

#endif