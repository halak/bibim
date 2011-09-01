#pragma once
#ifndef __BIBIM_MATH_H__
#define __BIBIM_MATH_H__

#   include <Bibim/Foundation.h>
#   include <Bibim/Color.h>
#   include <Bibim/Point.h>
#   include <Bibim/Vector2.h>
#   include <Bibim/Vector3.h>
#   include <Bibim/Vector4.h>

    namespace Bibim
    {
        class Math
        {
            BBThisIsStaticClass(Math);
            public:
                static const float E;
                static const float Log10E;
                static const float Log2E;
                static const float Pi;
                static const float PiOver2;
                static const float PiOver4;
                static const float TwoPi;

                static float Sqrt(float value);
                static float Sin(float radian);
                static float Cos(float radian);
                static float Tan(float radian);
                static float Acos(float radian);
                static float Atan2(float y, float x);
                static inline float Atan2(Vector2 xy);

                static inline char   Abs(char value);
                static inline short  Abs(short value);
                static inline int    Abs(int value);
                static inline long   Abs(long value);
                static inline float  Abs(float value);
                static inline double Abs(double value);

                static inline char   Min(char a, char b);
                static inline uchar  Min(uchar a, uchar b);
                static inline short  Min(short a, short b);
                static inline ushort Min(ushort a, ushort b);
                static inline int    Min(int a, int b);
                static inline uint   Min(uint a, uint b);
                static inline long   Min(long a, long b);
                static inline ulong  Min(ulong a, ulong b);
                static inline float  Min(float a, float b);
                static inline double Min(double a, double b);

                static inline char   Max(char a, char b);
                static inline uchar  Max(uchar a, uchar b);
                static inline short  Max(short a, short b);
                static inline ushort Max(ushort a, ushort b);
                static inline int    Max(int a, int b);
                static inline uint   Max(uint a, uint b);
                static inline long   Max(long a, long b);
                static inline ulong  Max(ulong a, ulong b);
                static inline float  Max(float a, float b);
                static inline double Max(double a, double b);

                static inline char   Min(char a, char b, char c);
                static inline uchar  Min(uchar a, uchar b, uchar c);
                static inline short  Min(short a, short b, short c);
                static inline ushort Min(ushort a, ushort b, ushort c);
                static inline int    Min(int a, int b, int c);
                static inline uint   Min(uint a, uint b, uint c);
                static inline long   Min(long a, long b, long c);
                static inline ulong  Min(ulong a, ulong b, ulong c);
                static inline float  Min(float a, float b, float c);
                static inline double Min(double a, double b, double c);

                static inline char   Max(char a, char b, char c);
                static inline uchar  Max(uchar a, uchar b, uchar c);
                static inline short  Max(short a, short b, short c);
                static inline ushort Max(ushort a, ushort b, ushort c);
                static inline int    Max(int a, int b, int c);
                static inline uint   Max(uint a, uint b, uint c);
                static inline long   Max(long a, long b, long c);
                static inline ulong  Max(ulong a, ulong b, ulong c);
                static inline float  Max(float a, float b, float c);
                static inline double Max(double a, double b, double c);

                static inline char   Min(char a, char b, char c, char d);
                static inline uchar  Min(uchar a, uchar b, uchar c, uchar d);
                static inline short  Min(short a, short b, short c, short d);
                static inline ushort Min(ushort a, ushort b, ushort c, ushort d);
                static inline int    Min(int a, int b, int c, int d);
                static inline uint   Min(uint a, uint b, uint c, uint d);
                static inline long   Min(long a, long b, long c, long d);
                static inline ulong  Min(ulong a, ulong b, ulong c, ulong d);
                static inline float  Min(float a, float b, float c, float d);
                static inline double Min(double a, double b, double c, double d);

                static inline char   Max(char a, char b, char c, char d);
                static inline uchar  Max(uchar a, uchar b, uchar c, uchar d);
                static inline short  Max(short a, short b, short c, short d);
                static inline ushort Max(ushort a, ushort b, ushort c, ushort d);
                static inline int    Max(int a, int b, int c, int d);
                static inline uint   Max(uint a, uint b, uint c, uint d);
                static inline long   Max(long a, long b, long c, long d);
                static inline ulong  Max(ulong a, ulong b, ulong c, ulong d);
                static inline float  Max(float a, float b, float c, float d);
                static inline double Max(double a, double b, double c, double d);

                static inline char   Clamp(char value, char min, char max);
                static inline uchar  Clamp(uchar value, uchar min, uchar max);
                static inline short  Clamp(short value, short min, short max);
                static inline ushort Clamp(ushort value, ushort min, ushort max);
                static inline int    Clamp(int value, int min, int max);
                static inline uint   Clamp(uint value, uint min, uint max);
                static inline long   Clamp(long value, long min, long max);
                static inline ulong  Clamp(ulong value, ulong min, ulong max);
                static inline float  Clamp(float value, float min, float max);
                static inline double Clamp(double value, double min, double max);

                static float  Mod(float a, float b);
                static double Mod(double a, double b);

                static inline int Wrap(int value, int upper);

                static int  GetNearestMorePowerOfTwo(int value);
                static uint GetNearestMorePowerOfTwo(uint value);

                static bool Equals(float a, float b);
                static bool Equals(Vector2 a, Vector2 b);
                static bool Equals(Vector3 a, Vector3 b);

                static Vector2 GetClosestPoint(Vector2 origin, Vector2 direction, float length, Vector2 point);

                static bool IsClockwise(Vector2 a, Vector2 b, Vector2 c);
                static bool IsClockwise(const Vector2* points, int numberOfPoints);

                static inline int     Interpolate(int a, int b, float t);
                static inline float   Interpolate(float a, float b, float t);
                static inline double  Interpolate(double a, double b, float t);
                static inline Point   Interpolate(Point a, Point b, float t);
                static inline Vector2 Interpolate(Vector2 a, Vector2 b, float t);
                static inline Vector3 Interpolate(Vector3 a, Vector3 b, float t);
                static inline Vector4 Interpolate(Vector4 a, Vector4 b, float t);
                static inline Color   Interpolate(Color a, Color b, float t);

                static int     Random(int a, int b);
                static float   Random(float a, float b);
                static Vector2 Random(Vector2 a, Vector2 b);
                static Vector3 Random(Vector3 a, Vector3 b);
                static Vector4 Random(Vector4 a, Vector4 b);
                static Color   Random(Color a, Color b);
        };
    }

#   include <Bibim/Math.inl>

#endif