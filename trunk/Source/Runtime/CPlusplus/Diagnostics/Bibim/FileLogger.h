#pragma once
#ifndef __BIBIM_FILELOGGER_H__
#define __BIBIM_FILELOGGER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Logger.h>
#   include <Bibim/String.h>

    namespace Bibim
    {
        class FileLogger : public Logger
        {
            BBModuleClass(FileLogger, Logger, 'F', 'L', 'O', 'G');
            public:
                FileLogger();
                FileLogger(const String& path);
                virtual ~FileLogger();

                virtual void Error(const char* category, const char* message);
                virtual void Warning(const char* category, const char* message);
                virtual void Information(const char* category, const char* message);

                inline const String& GetPath() const;
                void SetPath(const String& value);

            private:
                inline void Write(const char* head, int headLength, const char* category, const char* message);

            private:
                FileStreamPtr stream;
                String path;
                int lastFlushTime;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        const String& FileLogger::GetPath() const
        {
            return path;
        }
    }

#endif