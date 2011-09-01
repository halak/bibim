#pragma once
#ifndef __BIBIM_WORKFLOW_FLOWINGCONTEXT_H__
#define __BIBIM_WORKFLOW_FLOWINGCONTEXT_H__

#   include <Bibim/FWD.h>
#   include <map>

#   if (defined(BIBIM_PLATFORM_WINDOWS))
#       undef Yield // WinBase.h (Windows 환경)에서 Yield를 define하여 FlowingContext::Yield 선언할 수 없기 때문에 강제로 #undef합니다.
#   endif

    namespace Bibim
    {
        class FlowingContext
        {
            public:
                enum Status
                {
                    ExecutingStatus,
                    SuspendedStatus,
                    FinishedStatus,
                };

            public:
                FlowingContext(FlowchartPtr source);
                FlowingContext(FlowchartPtr source, VariableStoragePtr parentVariables);
                ~FlowingContext();

                void Execute();
                void Resume(const Any& result);

                const Any& Yield();
                const Any& Break();

                FlowchartPtr GetSource() const;
                FlowchartBlockPtr GetCurrent() const;
                Status GetStatus() const;
                VariableStoragePtr GetVariables() const;

            private:
                void ExecuteActually(FlowchartBlockPtr next);

            private:
                FlowchartPtr source;
                FlowchartBlockPtr current;
                Status status;
                VariableStoragePtr variables;
        };
    }

#endif