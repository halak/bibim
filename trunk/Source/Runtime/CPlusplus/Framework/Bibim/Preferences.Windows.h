#pragma once
#ifndef __BIBIM_PREFERENCES_WINDOWS_H__
#define __BIBIM_PREFERENCES_WINDOWS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/PreferencesBase.h>

    namespace Bibim
    {
        class Preferences : public PreferencesBase
        {
            BBModuleClass(Preferences, PreferencesBase, 'P', 'R', 'E', 'F');
            public:
                Preferences(const String& name);
                virtual ~Preferences();

            private:
                virtual String Load();
                virtual void   Save(const String& document);
        };
    }

#endif