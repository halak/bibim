#include <Bibim/Config.h>
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

        OnExecuted(command, temporaryCancelledCommands);

        DeleteAll(temporaryCancelledCommands);
    }

    void CommandHistory::Undo(int level)
    {
        if (level <= 0)
            return;

        CommandCollection undoneCommands;

        for (CommandCollection::reverse_iterator it = commands.rbegin(); it != commands.rend() && level > 0; level--)
        {
            if ((*it)->IsRestorable() == false)
                break;

            RestorableCommand* command = StaticCast<RestorableCommand>(*it);

            command->Undo();
            cancelledCommands.push_front(command);

            commands.pop_back();
            it = commands.rbegin();

            undoneCommands.push_back(command);
        }

        if (undoneCommands.empty() == false)
            OnUndone(undoneCommands);
    }

    void CommandHistory::Redo(int level)
    {
        if (level <= 0)
            return;

        CommandCollection redoneCommands;

        for (CommandCollection::iterator it = cancelledCommands.begin(); it != cancelledCommands.end() && level > 0; level--)
        {
            BBAssertDebug((*it)->IsRestorable());

            RestorableCommand* command = StaticCast<RestorableCommand>(*it);
            command->Redo();
            commands.push_back(*it);
            cancelledCommands.erase(it++);

            redoneCommands.push_back(command);
        }

        if (redoneCommands.empty() == false)
            OnRedone(redoneCommands);
    }

    void CommandHistory::ProgressTo(Command* command)
    {
        if (command == nullptr)
            return;

        // Undo
        {
            int level = 0;
            for (CommandCollection::reverse_iterator it = commands.rbegin(); it != commands.rend(); ++it, ++level)
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
            for (CommandCollection::iterator it = cancelledCommands.begin(); it != cancelledCommands.end(); ++it, ++level)
            {
                if ((*it) == command)
                {
                    Redo(level);
                    return;
                }
            }
        }
    }

    bool CommandHistory::CanUndo(int level) const
    {
        if (level <= 0)
            return true;

        for (CommandCollection::const_reverse_iterator it = commands.rbegin(); it != commands.rend() && level > 0; ++it, --level)
        {
            if ((*it)->IsRestorable() && StaticCast<RestorableCommand>(*it)->CanUndo() == false)
                return false;
        }

        return true;
    }

    bool CommandHistory::CanRedo(int level) const
    {
        if (level <= 0)
            return true;

        for (CommandCollection::const_iterator it = cancelledCommands.begin(); it != cancelledCommands.end() && level > 0; ++it, --level)
        {
            if ((*it)->IsRestorable() && StaticCast<RestorableCommand>(*it)->CanRedo() == false)
                return false;
        }

        return true;
    }

    bool CommandHistory::Contains(Command* command) const
    {
        return (std::find(commands.begin(), commands.end(), command) != commands.end() ||
                std::find(cancelledCommands.begin(), cancelledCommands.end(), command) != cancelledCommands.end());
    }

    void CommandHistory::OnExecuted(Command* /*command*/, const CommandCollection& /*cancelledCommands*/)
    {
    }

    void CommandHistory::OnUndone(const CommandCollection& /*commands*/)
    {
    }

    void CommandHistory::OnRedone(const CommandCollection& /*commands*/)
    {
    }
}