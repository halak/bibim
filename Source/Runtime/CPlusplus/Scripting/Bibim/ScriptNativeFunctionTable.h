#pragma once
#ifndef __BIBIM_SCRIPTNATIVEFUNCTIONTABLE_H__
#define __BIBIM_SCRIPTNATIVEFUNCTIONTABLE_H__

#   include <Bibim/FWD.h>

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
                static void AddRange(const Entry* items, int count);

                static NativeFunction Find(uint32 id);
        };

        typedef ScriptNativeFunctionTable::NativeFunction ScriptNativeFunction;

#       define BBBeginScriptNativeFunction() Bibim::ScriptNativeFunctionTable::Entry entries[] = {
#       define BBScriptNativeFunction(name)  { name##ID, &name },
#       define BBEndScriptNativeFunction()   }; Bibim::ScriptNativeFunctionTable::AddRange(entries, sizeof(entries) / sizeof(entries[0]));
    }

#   include <Bibim/ScriptNativeFunctionTable.inl>

#endif