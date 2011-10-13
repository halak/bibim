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

                GameComponent* ReadComponent();

            private:
                GameModuleTree* modules;
                std::vector<GameComponentPtr> localComponents;
        };
    }

#   include <Bibim/ComponentStreamReader.inl>

#endif