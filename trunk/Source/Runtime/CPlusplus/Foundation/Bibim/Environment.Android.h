#pragma once
#ifndef __BIBIM_ENVIRONMENT_ANDROID_H__
#define __BIBIM_ENVIRONMENT_ANDROID_H__

#   include <Bibim/FWD.h>
#   include <Bibim/String.h>

    namespace Bibim
    {
        class Environment
        {
            BBThisIsNoncopyableClass(Environment);
            public:
                static inline const String& GetLocaleName();
                static inline const String& GetWorkingDirectory();
                static String GetAppDataPath(const String& appName, const String& filename);


                static void Setup(const String& localeName, const String& workingDirectory);

            private:
                Environment();

            private:
                String localeName;
                String workingDirectory;
                
                static Environment PrivateInstance;
        };
    }

#   include <Bibim/Environment.Android.inl>

#endif