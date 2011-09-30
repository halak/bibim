#pragma once
#ifndef __BIBIM_SCRIPTSTACK_H__
#define __BIBIM_SCRIPTSTACK_H__

#   include <Bibim/FWD.h>
#   include <vector>

    namespace Bibim
    {
        class ScriptStack
        {
            BBThisIsNoncopyableClass(ScriptStack);
            public:
                ScriptStack();
                ~ScriptStack();

            private:
        };
    }

#   include <Bibim/ScriptStack.inl>

#endif