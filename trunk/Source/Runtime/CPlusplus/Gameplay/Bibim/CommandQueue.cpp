#include <Bibim/Config.h>
#include <Bibim/CommandQueue.h>
#include <Bibim/Command.h>

namespace Bibim
{
    CommandQueue::Event::Event(float time, int frame, Command* command)
        : time(time),
          frame(frame),
          command(command)
    {
    }

    CommandQueue::Event::Event(const Event& original)
        : time(original.time),
          frame(original.frame),
          command(original.command)
    {
    }

    CommandQueue::Event& CommandQueue::Event::operator = (const Event& original)
    {
        time = original.time;
        frame = original.frame;
        command = original.command;
        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    CommandQueue::CommandQueue()
        : time(0.0f),
          frame(0)
    {
    }

    CommandQueue::~CommandQueue()
    {
    }

    void CommandQueue::Reset(float time, int frame)
    {
        this->time = time;
        this->frame = frame;
    }

    void CommandQueue::Update(float dt, int /*timestamp*/)
    {
        time += dt;
        frame++;
    }

    void CommandQueue::Execute(Command* command)
    {
        if (command == nullptr)
            return;

        command->Execute();
        events.push_back(Event(time, frame, command));
    }
}