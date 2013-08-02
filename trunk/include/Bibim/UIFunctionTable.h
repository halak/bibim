#pragma once
#ifndef __BIBIM_UIFUNCTIONTABLE_H__
#define __BIBIM_UIFUNCTIONTABLE_H__

#include <Bibim/FWD.h>
#include <Bibim/GameModule.h>
#include <Bibim/String.h>
#include <map>

namespace Bibim
{
    class UIFunctionTable : public GameModule
    {
        BBModuleClass(UIFunctionTable, GameModule, 'U', 'F', 'C', 'T');
        public:
            typedef bool (*GlobalFunctionType)(const UIEventArgs&, void*);
            typedef std::pair<GlobalFunctionType, void*> FunctionType;
            typedef std::map<String, FunctionType> NamedFunctionMap;

        public:
            UIFunctionTable();
            virtual ~UIFunctionTable();

            inline void Add(const String& name, GlobalFunctionType function);
            void Add(const String& name, GlobalFunctionType function, void* userData);
            bool Remove(const String& name);
            void Clear();

            FunctionType Find(const String& name) const;

        private:
            NamedFunctionMap items;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    void UIFunctionTable::Add(const String& name, GlobalFunctionType function)
    {
        Add(name, function, nullptr);
    }
}

#endif