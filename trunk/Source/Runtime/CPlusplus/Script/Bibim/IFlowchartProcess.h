#pragma once
#ifndef __BIBIM_WORKFLOW_FLOWCHARTPROCESS_INTERFACE_H__
#define __BIBIM_WORKFLOW_FLOWCHARTPROCESS_INTERFACE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Any.h>

    namespace Bibim
    {
        class IFlowchartProcess
        {
            public:
                virtual ~IFlowchartProcess() { }

                virtual Any Execute(FlowingContext& context) = 0;
        };
    }

#endif