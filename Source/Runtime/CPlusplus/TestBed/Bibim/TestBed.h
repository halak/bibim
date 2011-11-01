#pragma once
#ifndef __BIBIM_TESTBED_H__
#define __BIBIM_TESTBED_H__

#   include <Bibim/FWD.h>
#   include <vector>

    namespace Bibim
    {
        namespace TestBed
        {
            typedef std::vector<const char*> CommandLines;

            void PipeStream(CommandLines commands);
            void Sprite(CommandLines commands);
            void UI(CommandLines commands);
            void UIRender(CommandLines commands);
        }
    }

#endif