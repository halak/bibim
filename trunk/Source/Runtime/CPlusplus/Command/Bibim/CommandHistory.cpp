#include <Bibim/PCH.h>
#include <Bibim/CommandHistory.h>
#include <Bibim/Assert.h>
#include <Bibim/Delete.h>
#include <Bibim/RestorableCommand.h>
#include <algorithm>

namespace Bibim
{
    CommandHistory::CommandHistory()
    {
    }

    CommandHistory::~CommandHistory()
    {
        DeleteAll(commands);
        DeleteAll(cancelledCommands);
    }

    void CommandHistory::Execute(Command* command)
    {
        BBAssert(command);
        command->Execute();
        commands.push_back(command);

        CommandCollection temporaryCancelledCommands;
        temporaryCancelledCommands.swap(cancelledCommands);

        executed.Emit(this, command, temporaryCancelledCommands);

        DeleteAll(temporaryCancelledCommands);
    }

    void CommandHistory::Undo()
    {
        Undo(1);
    }

    void CommandHistory::Undo(int level)
    {
        if (level <= 0)
            return;

        CommandCollection undoneCommands;
        const bool signalAlive = undone.GetNumberOfSlots() > 0;

        for (CommandCollection::reverse_iterator it = commands.rbegin(); it != commands.rend() && level > 0; level--)
        {
            if ((*it)->IsRestorable() == false)
                continue;

            RestorableCommand* command = dynamic_cast<RestorableCommand*>(*it);

            command->Undo();
            cancelledCommands.push_front(command);

            commands.pop_back();
            it = commands.rbegin();

            if (signalAlive)
                undoneCommands.push_back(command);
        }

        if (signalAlive && undoneCommands.empty() == false)
            undone.Emit(this, undoneCommands);
    }

    void CommandHistory::Redo()
    {
        Redo(1);
    }

    void CommandHistory::Redo(int level)
    {
        if (level <= 0)
            return;

        CommandCollection redoneCommands;
        const bool signalAlive = redone.GetNumberOfSlots() > 0;

        for (CommandCollection::iterator it = cancelledCommands.begin(); it != cancelledCommands.end() && level > 0; level--)
        {
            BBAssertDebug((*it)->IsRestorable());

            RestorableCommand* command = static_cast<RestorableCommand*>(*it);
            command->Redo();
            commands.push_back(*it);
            cancelledCommands.erase(it++);

            if (signalAlive)
                redoneCommands.push_back(command);
        }

        if (signalAlive && redoneCommands.empty() == false)
            redone.Emit(this, redoneCommands);
    }

    void CommandHistory::ProgressTo(Command* command)
    {
        if (command == nullptr)
            return;

        // Undo
        {
            int level = 0;
            for (CommandCollection::reverse_iterator it = commands.rbegin(); it != commands.rend(); it++, level++)
            {
                if ((*it) == command)
                {
                    Undo(level);
                    return;
                }
            }
        }

        // Redo
        {
            int level = 1;
            for (CommandCollection::iterator it = cancelledCommands.begin(); it != cancelledCommands.end(); it++, level++)
            {
                if ((*it) == command)
                {
                    Redo(level);
                    return;
                }
            }
        }
    }

    bool CommandHistory::CanUndo() const
    {
        return CanUndo(1);
    }

    bool CommandHistory::CanUndo(int level) const
    {
        if (level <= 0)
            return true;

        for (CommandCollection::const_reverse_iterator it = commands.rbegin(); it != commands.rend() && level > 0; it++, level--)
        {
            if ((*it)->IsRestorable() && static_cast<RestorableCommand*>(*it)->CanUndo() == false)
                return false;
        }

        return true;
    }

    bool CommandHistory::CanRedo() const
    {
        return CanRedo(1);
    }

    bool CommandHistory::CanRedo(int level) const
    {
        if (level <= 0)
            return true;

        for (CommandCollection::const_iterator it = cancelledCommands.begin(); it != cancelledCommands.end() && level > 0; it++, level--)
        {
            if ((*it)->IsRestorable() && static_cast<RestorableCommand*>(*it)->CanRedo() == false)
                return false;
        }

        return true;
    }

    bool CommandHistory::Contains(Command* command) const
    {
        return (std::find(commands.begin(), commands.end(), command) != commands.end() ||
                std::find(cancelledCommands.begin(), cancelledCommands.end(), command) != cancelledCommands.end());
    }

    const CommandHistory::CommandCollection& CommandHistory::GetCommands() const
    {
        return commands;
    }

    const CommandHistory::CommandCollection& CommandHistory::GetCancelledCommands() const
    {
        return cancelledCommands;
    }

    Signal<CommandHistory*, Command*, const CommandHistory::CommandCollection&>& CommandHistory::Executed()
    {
        return executed;
    }

    Signal<CommandHistory*, const CommandHistory::CommandCollection&>& CommandHistory::Undone()
    {
        return undone;
    }

    Signal<CommandHistory*, const CommandHistory::CommandCollection&>& CommandHistory::Redone()
    {
        return redone;
    }
}