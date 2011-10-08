#pragma once
#ifndef __BIBIM_SCRIPTPROCESS_H__
#define __BIBIM_SCRIPTPROCESS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>
#   include <Bibim/ScriptStack.h>

    namespace Bibim
    {
        class ScriptProcess : public SharedObject
        {
            BBObjectClass(ScriptProcess, SharedObject, 'S', 'C', 'P', 'S');
            public:
                ScriptProcess(Script* script);
                ScriptProcess(Script* script, int stackSize);
                virtual ~ScriptProcess();

                void Resume();
                void Suspend();
            
            private:
                void Process(BinaryReader& reader);

            private:
                ScriptPtr script;
                ScriptStack stack;
                uint position;
        };
    }

#   include <Bibim/ScriptProcess.inl>

#endif