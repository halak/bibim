#pragma once
#ifndef __BIBIM_WORKFLOW_FLOWINGCONTEXT_H__
#define __BIBIM_WORKFLOW_FLOWINGCONTEXT_H__

#   include <Bibim/FWD.h>
#   include <map>

#   if (defined(BIBIM_PLATFORM_WINDOWS))
#       undef Yield // WinBase.h (Windows ȯ��)���� Yield�� define�Ͽ� FlowingContext::Yield ������ �� ���� ������ ������ #undef�մϴ�.
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