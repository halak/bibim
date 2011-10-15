#pragma once
#ifndef __BIBIM_COMPONENTSTREAMREADER_H__
#define __BIBIM_COMPONENTSTREAMREADER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/BinaryReader.h>
#   include <vector>

    namespace Bibim
    {
        class ComponentStreamReader : public BinaryReader
        {
            BBThisIsNoncopyableClass(ComponentStreamReader);
            public:
                ComponentStreamReader(Stream* sourceStream, GameModuleTree* modules);
                ~ComponentStreamReader();

                GameModule* ReadModule();
                GameModule* ReadModule(uint32 defaultModuleClassID);

                GameModule* FindModuleByClassID(uint32 classID);

                GameAsset* ReadAsset();
                GameComponent* ReadComponent();

            private:
                inline GameAssetStorage* GetStorage();

            private:
                GameModuleTree* modules;
                GameAssetStorage* storage;
                std::vector<GameComponentPtr> localComponents;
        };
    }

#   include <Bibim/ComponentStreamReader.inl>

#endif