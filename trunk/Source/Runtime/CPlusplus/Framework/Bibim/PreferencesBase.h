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
        class PreferencesBase : public GameModule
        {
            BBAbstractModuleClass(PreferencesBase, GameModule);
            public:
                virtual ~PreferencesBase();

                inline const String& GetName() const;

                const Any& GetValue(const String& key);
                void       SetValue(const String& key, const Any& value);

                void Commit();

                inline bool IsModified() const;
                
                static inline bool CanStore(Any::Type type);

            protected:
                PreferencesBase(const String& name);

                void Update();

                virtual String Load() = 0;
                virtual void   Save(const String& document) = 0;

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

#   include <Bibim/PreferencesBase.inl>

#endif