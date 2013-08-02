#pragma once
#ifndef __BIBIM_COMMANDHISTORY_H__
#define __BIBIM_COMMANDHISTORY_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>
#   include <list>

    namespace Bibim
    {
        class CommandHistory : public GameModule
        {
            BBModuleClass(CommandHistory, GameModule, 'C', 'M', 'D', 'H');
            public:
                typedef std::list<CommandPtr> CommandCollection;

            public:
                CommandHistory();
                virtual ~CommandHistory();

                void Execute(Command* command);
                void Undo(int level);
                void Redo(int level);
                inline void Undo();
                inline void Redo();
                void ProgressTo(Command* command);

                bool CanUndo(int level) const;
                bool CanRedo(int level) const;
                inline bool CanUndo() const;
                inline bool CanRedo() const;

                bool Contains(Command* command) const;

                inline const CommandCollection& GetCommands() const;
                inline const CommandCollection& GetCancelledCommands() const;

            protected:
                void OnExecuted(Command* command, const CommandCollection& cancelledCommands);
                void OnUndone(const CommandCollection& commands);
                void OnRedone(const CommandCollection& commands);

            private:
                CommandCollection commands;
                CommandCollection cancelledCommands;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

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

#endif