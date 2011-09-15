#pragma once
#ifndef __BIBIM_GAMEASSET_H__
#define __BIBIM_GAMEASSET_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>
#   include <Bibim/URI.h>

    namespace Bibim
    {
#       define BBGameAssetClass(a, b, c, d) public: \
                                                static const uint32 ClassID = BBMakeFOURCC(a, b, c, d); \
                                                virtual uint32 GetClassID() const { return ClassID; } \
                                            private:

        class GameAsset : public SharedObject
        {
            BBGameAssetClass('G', 'A', 'S', 'T');
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