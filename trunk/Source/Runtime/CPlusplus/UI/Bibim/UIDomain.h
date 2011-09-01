#pragma once
#ifndef __BIBIM_UIDOMAIN_H__
#define __BIBIM_UIDOMAIN_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameComponent.h>

    namespace Bibim
    {
        class UIDomain : public GameComponent
        {
            BBClassFOURCC('U', 'I', 'D', 'M');
            public:
                UIDomain();
                UIDomain(UIWindow* root);
                virtual ~UIDomain();

                inline UIWindow* GetRoot() const;
                void SetRoot(UIWindow* value);

                virtual UIVisual* GetFocus() const = 0;
                virtual void SetFocus(UIVisual* value) = 0;

            private:
                UIWindowPtr root;
        };
    }

#   include <Bibim/UIDomain.inl>

#endif