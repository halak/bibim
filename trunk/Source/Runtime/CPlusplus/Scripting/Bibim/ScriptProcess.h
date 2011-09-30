#pragma once
#ifndef __BIBIM_SCRIPTPROCESS_H__
#define __BIBIM_SCRIPTPROCESS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>

    namespace Bibim
    {
        class ScriptProcess : public SharedObject
        {
            public:
                ScriptProcess(Script* script);
                virtual ~ScriptProcess();

                void Run();

            private:
                ScriptPtr script;
                int position;
        };
    }

#   include <Bibim/ScriptProcess.inl>

#endif