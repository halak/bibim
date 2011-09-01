#pragma once
#ifndef __BIBIM_UIFUNCTIONTABLE_H__
#define __BIBIM_UIFUNCTIONTABLE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameComponent.h>
#   include <Bibim/String.h>
#   include <map>

    namespace Bibim
    {
        class UIFunctionTable : public GameComponent
        {
            public:
                typedef bool (*GlobalFunctionType)(const UIEventArgs&);
                typedef GlobalFunctionType FunctionType;
                typedef std::map<String, FunctionType> NamedFunctionMap;

            public:
                UIFunctionTable();
                virtual ~UIFunctionTable();

                void Add(const String& name, GlobalFunctionType function);
                bool Remove(const String& name);
                void Clear();

                FunctionType Find(const String& name) const;

            private:
                NamedFunctionMap items;
        };
    }

#   include <Bibim/UIFunctionTable.inl>

#endif