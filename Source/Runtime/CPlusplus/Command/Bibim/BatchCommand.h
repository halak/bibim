#pragma once
#ifndef __BIBIM_BATCHCOMMAND_H__
#define __BIBIM_BATCHCOMMAND_H__

#   include <Bibim/FWD.h>
#   include <Bibim/RestorableCommand.h>
#   include <Bibim/ICloneable.h>
#   include <vector>

    namespace Bibim
    {
        class BatchCommand : public RestorableCommand, public ICloneable
        {
            public:
                typedef std::vector<Command*> CommandCollection;
                typedef std::vector<RestorableCommand*> RestorableCommandCollection;

            public:
                BatchCommand(const CommandCollection commands);
                BatchCommand(const BatchCommand& original, CloningContext& context);
                virtual ~BatchCommand();

                virtual BatchCommand* CloneWith(CloningContext& context) const;

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

            private:
                friend void __Startup__();
                static void __Startup__();
        };
    }

#   include <Bibim/BatchCommand.inl>

#endif