#pragma once
#ifndef __BIBIM_ENVIRONMENT_WINDOWS_H__
#define __BIBIM_ENVIRONMENT_WINDOWS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/String.h>

#   if (defined(BIBIM_PLATFORM_WINDOWS))

        namespace Bibim
        {
            class Environment
            {
                BBThisIsNoncopyableClass(Environment);
                public:
                    static inline const String& GetWorkingDirectory();

                private:
                    Environment();

                    inline const String& PrivateGetWorkingDirectory() const;

                private:
                    String workingDirectory;

                    static Environment PrivateInstance;
            };
        }

#       include <Bibim/Environment.Windows.inl>

#   endif

#   endif