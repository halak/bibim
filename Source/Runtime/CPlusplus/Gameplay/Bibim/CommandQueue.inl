namespace Bibim
{
    float CommandQueue::Event::GetTime() const
    {
        return time;
    }

    int CommandQueue::Event::GetFrame() const
    {
        return frame;
    }

    Command* CommandQueue::Event::GetCommand() const
    {
        return command;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    void CommandQueue::Reset()
    {
        Reset(0.0f, 0);
    }

    const CommandQueue::EventCollection& CommandQueue::GetEvents() const
    {
        return events;
    }
}