#pragma once
#ifndef __BIBIM_GAMEASSET_H__
#define __BIBIM_GAMEASSET_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>
#   include <Bibim/URI.h>

    namespace Bibim
    {
        class GameAsset : public SharedObject
        {
            BBThisIsNoncopyableClass(GameAsset);
            public:
                virtual ~GameAsset();

                inline const URI& GetURI() const;

            protected:
                GameAsset();
                GameAsset(const URI& uri);

            private:
                URI uri;
        };
    }

#   include <Bibim/GameAsset.inl>

#endif