#pragma once
#ifndef __BIBIM_UIRENDERBUFFER_H__
#define __BIBIM_UIRENDERBUFFER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>

    namespace Bibim
    {
        class UIRenderBuffer : public SharedObject
        {
            public:
                class Node : public SharedObject
                {
                    public:
                        virtual ~Node() { }

                        virtual void Setup();

                    private:
                };

                enum CommandID
                {
                    Setup,
                };

                class Command : public SharedObject
                {
                    public:
                        Command();
                        virtual ~Command();

                    private:
                };

            public:
                UIRenderBuffer();
                virtual ~UIRenderBuffer();

            private:
        };
    }

#   include <Bibim/UIRenderBuffer.inl>

#endif