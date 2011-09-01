#pragma once
#ifndef __BIBIM_WORKFLOW_FLOWCHARTBLOCK_H__
#define __BIBIM_WORKFLOW_FLOWCHARTBLOCK_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Any.h>
#   include <map>
#   include <set>

    namespace Bibim
    {
        class FlowchartBlock : public SharedObject
        {
            public:
                typedef std::map<Any, FlowchartBlockPtr> BlockDictionary;

            public:
                FlowchartBlock();
                FlowchartBlock(IFlowchartProcessPtr process);
                virtual ~FlowchartBlock();

                FlowchartBlockPtr Execute(FlowingContext& context);

                std::set<FlowchartBlockPtr> Flatten();
                void FlattenTo(std::set<FlowchartBlockPtr>& collection);

                void AddNextBlock(const Any& key, FlowchartBlockPtr item);
                bool RemoveNextBlock(const Any& key);
                void ClearNextBlocks();

                FlowchartBlockPtr FindNextBlock(const Any& key) const;

                IFlowchartProcessPtr GetProcess() const;
                void SetProcess(IFlowchartProcessPtr value);

                const BlockDictionary& GetNextBlocks() const;

            private:
                IFlowchartProcessPtr process;
                BlockDictionary nextBlocks;
                FlowchartBlockPtr defaultNextBlock;
        };
    }

#endif