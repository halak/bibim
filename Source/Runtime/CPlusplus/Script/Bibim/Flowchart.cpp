#include <Bibim/PCH.h>
#include <Bibim/Flowchart.h>
#include <Bibim/FlowchartBlock.h>

namespace Bibim
{
    Flowchart::Flowchart()
    {
    }

    Flowchart::~Flowchart()
    {
    }

    void Flowchart::AddMajorBlock(FlowchartBlockPtr item)
    {
        majorBlocks.insert(item);
    }

    bool Flowchart::RemoveMajorBlock(FlowchartBlockPtr item)
    {
        BlockCollection::iterator it = majorBlocks.find(item);
        if (it != majorBlocks.end())
        {
            majorBlocks.erase(it);
            return true;
        }
        else
            return false;
    }

    void Flowchart::ClearMajorBlocks()
    {
        majorBlocks.clear();
    }

    FlowchartBlockPtr Flowchart::GetStartupBlock() const
    {
        return startupBlock;
    }

    void Flowchart::SetStartupBlock(FlowchartBlockPtr value)
    {
        if (startupBlock != value)
        {
            FlowchartBlockPtr old = startupBlock;

            startupBlock = value;
        }
    }

    const Flowchart::BlockCollection& Flowchart::GetMajorBlocks() const
    {
        return majorBlocks;
    }
}