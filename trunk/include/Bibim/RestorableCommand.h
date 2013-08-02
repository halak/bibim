#pragma once
#ifndef __BIBIM_RESTORABLECOMMAND_H__
#define __BIBIM_RESTORABLECOMMAND_H__

#include <Bibim/FWD.h>
#include <Bibim/Command.h>

namespace Bibim
{
    class RestorableCommand : public Command
    {
        public:
            virtual ~RestorableCommand();

            virtual void Undo() = 0;
            virtual void Redo();

            virtual bool CanUndo() const;
            virtual bool CanRedo() const;

            virtual bool IsRestorable() const;

        protected:
            RestorableCommand();
    };
}

#endif