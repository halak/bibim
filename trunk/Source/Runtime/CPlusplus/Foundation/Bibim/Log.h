#pragma once
#ifndef __BIBIM_LOG_H__
#define __BIBIM_LOG_H__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class Log
        {
            BBThisIsStaticClass(Log);
            public:
                class Listener
                {
                    public:
                        virtual ~Listener() { }
                        virtual void Error(const char* category, const char* message) = 0;
                        virtual void Warning(const char* category, const char* message) = 0;
                        virtual void Information(const char* category, const char* message) = 0;
                };

            public:
                static inline void Error(const char* message);
                static inline void Warning(const char* message);
                static inline void Information(const char* message);

                static void Error(const char* category, const char* message);
                static void Warning(const char* category, const char* message);
                static void Information(const char* category, const char* message);

                static void Add(Listener* item);
                static void Remove(Listener* item);
        };
    }

#   include <Bibim/Log.inl>

#endif