#pragma once
#ifndef __BIBIM_BATCHCOMMAND_H__
#define __BIBIM_BATCHCOMMAND_H__

#   include <Bibim/FWD.h>
#   include <Bibim/RestorableCommand.h>
#   include <vector>

    namespace Bibim
    {
        class BatchCommand : public RestorableCommand
        {
            public:
                typedef std::vector<CommandPtr> CommandCollection;
                typedef std::vector<RestorableCommandPtr> RestorableCommandCollection;

            public:
                BatchCommand();
                BatchCommand(const CommandCollection commands);
                virtual ~BatchCommand();

                virtual void Execute();
                virtual void Undo();
                virtual void Redo();

                virtual bool CanUndo() const;
                virtual bool CanRedo() const;

                inline const CommandCollection& GetCommands() const;
                void SetCommands(const CommandCollection& value);

            private:
                CommandCollection commands;
                RestorableCommandCollection restorableCommands;
        };
    }

#   include <Bibim/BatchCommand.inl>

#endif