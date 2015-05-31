#pragma once
#ifndef __BIBIM_DATETIME_H__
#define __BIBIM_DATETIME_H__

#include <Bibim/Foundation.h>

namespace Bibim
{
    struct DateTime
    {
        int Year;
        int Month;
        int Day;
        int Hour;
        int Minute;
        int Second;

        inline DateTime();
        inline DateTime(int year, int month, int day);
        inline DateTime(int year, int month, int day, int hour, int minute, int second);
        inline DateTime(const DateTime& original);
        inline ~DateTime();

        inline DateTime& operator = (const DateTime& right);
        inline bool operator == (const DateTime& right);
        inline bool operator != (const DateTime& right);

        static DateTime Now();
        static DateTime Today();
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    DateTime::DateTime()
        : Year(0),
          Month(0),
          Day(0),
          Hour(0),
          Minute(0),
          Second(0)
    {
    }

    DateTime::DateTime(int year, int month, int day)
        : Year(year),
          Month(month),
          Day(day),
          Hour(0),
          Minute(0),
          Second(0)
    {
    }

    DateTime::DateTime(int year, int month, int day, int hour, int minute, int second)
        : Year(year),
          Month(month),
          Day(day),
          Hour(hour),
          Minute(minute),
          Second(second)
    {   
    }
    
    DateTime::DateTime(const DateTime& original)
        : Year(original.Year),
          Month(original.Month),
          Day(original.Day),
          Hour(original.Hour),
          Minute(original.Minute),
          Second(original.Second)
    {
    }

    DateTime::~DateTime()
    {
    }

    DateTime& DateTime::operator = (const DateTime& right)
    {
        Year = right.Year;
        Month = right.Month;
        Day = right.Day;
        Hour = right.Hour;
        Minute = right.Minute;
        Second = right.Second;
        return *this;
    }

    bool DateTime::operator == (const DateTime& right)
    {
        return
            Year == right.Year &&
            Month == right.Month &&
            Day == right.Day &&
            Hour == right.Hour &&
            Minute == right.Minute &&
            Second == right.Second;
    }

    bool DateTime::operator != (const DateTime& right)
    {
        return !operator == (right);
    }
}

#endif