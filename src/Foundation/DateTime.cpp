#include <Bibim/Config.h>
#include <Bibim/DateTime.h>
#include <time.h>

namespace Bibim
{
    DateTime DateTime::Now()
    {
		time_t rawTime;
		time(&rawTime);

		struct tm* timeInformation = localtime(&rawTime);

		return DateTime(
			timeInformation->tm_year + 1900,
			timeInformation->tm_mon + 1,
			timeInformation->tm_mday,
			timeInformation->tm_hour,
			timeInformation->tm_min,
			timeInformation->tm_sec);
    }

    DateTime DateTime::Today()
    {
		DateTime now = Now();
		return DateTime(now.Year, now.Month, now.Day);
    }
}