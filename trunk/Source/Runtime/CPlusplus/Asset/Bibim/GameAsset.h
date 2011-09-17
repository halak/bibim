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
#       define BBReadableGameAssetClass(a, b, c, d) BBGameAssetClass(a, b, c, d); \
                                                    public: \
                                                        static GameAsset* Read(AssetReader& reader, GameAsset* existingInstance); \
                                                    private:
                                                    

        class GameAsset : public SharedObject
        {
            BBGameAssetClass('G', 'A', 'S', 'T');
            BBThisIsNoncopyableClass(GameAsset);
            public:
                virtual ~GameAsset();

                inline uint GetRevision() const;

            protected:
                GameAsset();

                inline void IncreaseRevision();

            private:
                uint revision;
        };
    }

#   include <Bibim/GameAsset.inl>

#endif