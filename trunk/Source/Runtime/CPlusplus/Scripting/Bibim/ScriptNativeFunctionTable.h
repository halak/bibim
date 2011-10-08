#pragma once
#ifndef __BIBIM_SCRIPTNATIVEFUNCTIONTABLE_H__
#define __BIBIM_SCRIPTNATIVEFUNCTIONTABLE_H__

#   include <Bibim/FWD.h>
#   include <vector>

    namespace Bibim
    {
        class ScriptNativeFunctionTable
        {
            BBThisIsStaticClass(ScriptNativeFunctionTable);
            public:
                typedef void (*NativeFunction)(ScriptingContext& context);
                struct Entry
                {
                    uint32 ID;
                    NativeFunction Function;
                };

            public:
                static void Add(uint32 id, NativeFunction function);
                static void Add(Entry item);
                static void AddRange(const std::vector<Entry>& items);

                static NativeFunction Find(uint32 id);
        };

        typedef ScriptNativeFunctionTable::NativeFunction ScriptNativeFunction;
    }

#   include <Bibim/ScriptNativeFunctionTable.inl>

#endif