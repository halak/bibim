#pragma once
#ifndef __BIBIM_GAMEASSET_H__
#define __BIBIM_GAMEASSET_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>
#   include <Bibim/URI.h>

    namespace Bibim
    {
#       define BBGameAssetClass(a, b, c, d) BBObjectClass(_, _, a, b, c, d)
#       define BBReadableGameAssetClass(a, b, c, d) BBObjectClass(_, _, a, b, c, d); \
                                                    public: \
                                                        static GameAsset* Read(AssetStreamReader& reader, GameAsset* existingInstance); \
                                                    private:

        class GameAsset : public SharedObject
        {
            BBGameAssetClass('G', 'A', 'S', 'T');
            BBThisIsNoncopyableClass(GameAsset);
            public:
                enum Status
                {
                    EmptyStatus = 0,
                    LoadingStatus = 1,
                    CompletedStatus = 2,
                    FaultStatus = 3,
                };

            public:
                virtual ~GameAsset();

                inline Status GetStatus() const;
                inline uint GetRevision() const;

            protected:
                GameAsset(); // call in derived classes, GameAssetStorage

                inline void SetStatus(Status value);
                inline void IncreaseRevision();

            private:
                Status status;
                uint revision;

                friend class GameAssetStorage;
        };
    }

#   include <Bibim/GameAsset.inl>

#endif