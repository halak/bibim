namespace Bibim
{
    void CommandHistory::Undo()
    {
        Undo(1);
    }

    void CommandHistory::Redo()
    {
        Redo(1);
    }

    bool CommandHistory::CanUndo() const
    {
        return CanUndo(1);
    }

    bool CommandHistory::CanRedo() const
    {
        return CanRedo(1);
    }

    const CommandHistory::CommandCollection& CommandHistory::GetCommands() const
    {
        return commands;
    }

    const CommandHistory::CommandCollection& CommandHistory::GetCancelledCommands() const
    {
        return cancelledCommands;
    }
}