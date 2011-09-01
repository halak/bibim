#pragma once
#ifndef __BIBIM_WORKFLOW_FLOWCHART_H__
#define __BIBIM_WORKFLOW_FLOWCHART_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Asset.h>
#   include <set>

    namespace Bibim
    {
        class Flowchart : public Asset
        {
            public:
                typedef std::set<FlowchartBlockPtr> BlockCollection;

            public:
                Flowchart();
                virtual ~Flowchart();

                void AddMajorBlock(FlowchartBlockPtr item);
                bool RemoveMajorBlock(FlowchartBlockPtr item);
                void ClearMajorBlocks();

                FlowchartBlockPtr GetStartupBlock() const;
                void SetStartupBlock(FlowchartBlockPtr value);

                const BlockCollection& GetMajorBlocks() const;

            private:
                FlowchartBlockPtr startupBlock;
                BlockCollection majorBlocks;
        };
    }

#endif