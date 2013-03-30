#pragma once
#ifndef __BIBIM_PREFERENCES_BASE_H__
#define __BIBIM_PREFERENCES_BASE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>
#   include <Bibim/String.h>
#   include <Bibim/Any.h>
#   include <map>

    namespace Bibim
    {
        class Preferences : public GameModule
        {
            BBAbstractModuleClass(Preferences, GameModule);
            public:
                Preferences(const String& name);
                virtual ~Preferences();

                inline const String& GetName() const;

                const Any& GetValue(const String& key);
                void       SetValue(const String& key, const Any& value);

                void Commit();

                inline bool IsModified() const;
                
                static inline bool CanStore(Any::Type type);

            protected:
                void Update();

                String Load();
                void   Save(const String& document);

            private:
                inline bool IsLoaded() const;

            private:
                typedef std::map<String, Any> Dictionary;

                String name;
                Dictionary items;
                bool isModified;
                bool isLoaded;
        };
    }

#   include <Bibim/Preferences.inl>

#endif