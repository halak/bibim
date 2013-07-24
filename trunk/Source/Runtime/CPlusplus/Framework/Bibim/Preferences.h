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

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        const String& Preferences::GetName() const
        {
            return name;
        }

        bool Preferences::IsModified() const
        {
            return isModified;
        }

        bool Preferences::IsLoaded() const
        {
            return isLoaded;
        }

        bool Preferences::CanStore(Any::Type type)
        {
            switch (type)
            {
                case Any::BoolType:
                case Any::IntType:
                case Any::StringType:
                    return true;
                default:
                    return false;
            }
        }
    }

#endif