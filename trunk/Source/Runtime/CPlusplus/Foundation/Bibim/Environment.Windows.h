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
                static inline const String& GetWorkingDirectory();
                static inline const String& GetLocaleName();

            private:
                Environment();

            private:
                String workingDirectory;
                String localeName;

                static Environment PrivateInstance;
        };
    }

#   include <Bibim/Environment.Windows.inl>

#endif