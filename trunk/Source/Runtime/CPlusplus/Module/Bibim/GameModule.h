#pragma once
#ifndef __BIBIM_GAMEMODULE_H__
#define __BIBIM_GAMEMODULE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameComponent.h>
#   include <Bibim/ICloneable.h>
#   include <Bibim/String.h>

    namespace Bibim
    {
        class GameModule : public GameComponent, public ICloneable
        {
            BBClassFOURCC('G', 'M', 'D', 'L');
            public:
                GameModule();
                explicit GameModule(uint32 id);
                GameModule(const GameModule& original, CloningContext& context);
                virtual ~GameModule();

                virtual GameModule* CloneWith(CloningContext& context) const;

                inline const String& GetName() const;
                inline void SetName(const String& value);
                inline const String& GetFilename() const;
                inline void SetFilename(const String& value);
                inline const String& GetDescription() const;
                inline void SetDescription(const String& value);

                virtual ICloneable* QueryCloneableInterface();

            private:
                String name;
                String filename;
                String description;
        };
    }

#   include <Bibim/GameModule.inl>

#endif