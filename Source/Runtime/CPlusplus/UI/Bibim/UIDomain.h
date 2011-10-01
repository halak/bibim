#pragma once
#ifndef __BIBIM_UIDOMAIN_H__
#define __BIBIM_UIDOMAIN_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>

    namespace Bibim
    {
        class UIDomain : public GameModule
        {
            BBAbstractObjectClass(UIDomain, GameModule);
            public:
                virtual ~UIDomain();

                inline UIWindow* GetRoot() const;
                void SetRoot(UIWindow* value);

                virtual UIVisual* GetFocus() const = 0;
                virtual void SetFocus(UIVisual* value) = 0;

            protected:
                UIDomain();
                UIDomain(UIWindow* root);

            private:
                UIWindowPtr root;
        };
    }

#   include <Bibim/UIDomain.inl>

#endif