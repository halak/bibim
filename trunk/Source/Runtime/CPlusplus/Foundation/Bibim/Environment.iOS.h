#pragma once
#ifndef __BIBIM_ENVIRONMENT_IOS_H__
#define __BIBIM_ENVIRONMENT_IOS_H__

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

                static void Setup(const String& localeName,
                                  const String& workingDirectory,
                                  const String& appDataDirectoryBase);

            private:
                Environment();

            private:
                String localeName;
                String workingDirectory;
                String appDataDirectoryBase;

                static Environment PrivateInstance;
        };
    }

#   include <Bibim/Environment.iOS.inl>

#endif