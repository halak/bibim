#pragma once
#ifndef __BIBIM_COMMANDHISTORY_H__
#define __BIBIM_COMMANDHISTORY_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameComponent.h>
#   include <Bibim/Signal.h>
#   include <list>

    namespace Bibim
    {
        class CommandHistory : public GameComponent
        {
            BBClassFOURCC('C', 'M', 'D', 'H');
            public:
                typedef std::list<Command*> CommandCollection;

            public:
                CommandHistory();
                virtual ~CommandHistory();

                void Execute(Command* command);
                void Undo();
                void Undo(int level);
                void Redo();
                void Redo(int level);
                void ProgressTo(Command* command);

                bool CanUndo() const;
                bool CanUndo(int level) const;
                bool CanRedo() const;
                bool CanRedo(int level) const;

                bool Contains(Command* command) const;

                const CommandCollection& GetCommands() const;
                const CommandCollection& GetCancelledCommands() const;

                Signal<CommandHistory*, Command*, const CommandCollection&>& Executed();
                Signal<CommandHistory*, const CommandCollection&>& Undone();
                Signal<CommandHistory*, const CommandCollection&>& Redone();

            private:
                CommandCollection commands;
                CommandCollection cancelledCommands;

                Signal<CommandHistory*, Command*, const CommandCollection&> executed;
                Signal<CommandHistory*, const CommandCollection&> undone;
                Signal<CommandHistory*, const CommandCollection&> redone;

            private:
                friend void __Startup__();
                static void __Startup__();
        };
    }

#endif