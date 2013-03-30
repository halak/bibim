#pragma once
#ifndef __BIBIM_ENVIRONMENT_WINDOWS_H__
#define __BIBIM_ENVIRONMENT_WINDOWS_H__

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

            private:
                Environment();

            private:
                String localeName;
                String workingDirectory;
                String appDataDirectoryBase;

                static Environment PrivateInstance;
        };
    }

#   include <Bibim/Environment.Windows.inl>

#endif