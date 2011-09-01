#pragma once
#ifndef __BIBIM_UIFUNCTIONEVENTHANDLER_H__
#define __BIBIM_UIFUNCTIONEVENTHANDLER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIEventHandler.h>
#   include <Bibim/UIFunctionTable.h>
#   include <vector>

    namespace Bibim
    {
        class UIFunctionEventHandler : public UIEventHandler
        {
            public:
                UIFunctionEventHandler();
                UIFunctionEventHandler(const UIFunctionTable* table, const String& functionName);
                virtual ~UIFunctionEventHandler();

                virtual bool Invoke(const UIEventArgs& args);

                inline const UIFunctionTable* GetTable() const;
                void SetTable(const UIFunctionTable* value);
 
                inline const String& GetFunctionName() const;
                void SetFunctionName(const String& value);

            private:
                const UIFunctionTable* table;
                String functionName;

                UIFunctionTable::FunctionType callable;
                bool callableChanged;
        };
    }

#   include <Bibim/UIFunctionEventHandler.inl>

#endif