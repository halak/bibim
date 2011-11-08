#pragma once
#ifndef __BIBIM_MATH_H__
#define __BIBIM_MATH_H__

#   include <Bibim/Foundation.h>
#   include <Bibim/Color.h>
#   include <Bibim/Point2.h>
#   include <Bibim/Point3.h>
#   include <Bibim/Point4.h>
#   include <Bibim/Rect.h>
#   include <Bibim/RectF.h>
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

                static inline short   Abs(short value);
                static inline int     Abs(int value);
                static inline longint Abs(longint value);
                static inline float   Abs(float value);
                static inline double  Abs(double value);

                static inline byte    Min(byte a, byte b);
                static inline short   Min(short a, short b);
                static inline int     Min(int a, int b);
                static inline longint Min(longint a, longint b);
                static inline float   Min(float a, float b);
                static inline double  Min(double a, double b);

                static inline byte    Max(byte a, byte b);
                static inline short   Max(short a, short b);
                static inline int     Max(int a, int b);
                static inline longint Max(longint a, longint b);
                static inline float   Max(float a, float b);
                static inline double  Max(double a, double b);

                static inline byte    Min(byte a, byte b, byte c);
                static inline short   Min(short a, short b, short c);
                static inline int     Min(int a, int b, int c);
                static inline longint Min(longint a, longint b, longint c);
                static inline float   Min(float a, float b, float c);
                static inline double  Min(double a, double b, double c);

                static inline byte    Max(byte a, byte b, byte c);
                static inline short   Max(short a, short b, short c);
                static inline int     Max(int a, int b, int c);
                static inline longint Max(longint a, longint b, longint c);
                static inline float   Max(float a, float b, float c);
                static inline double  Max(double a, double b, double c);

                static inline byte   Clamp(byte value, byte min, byte max);
                static inline short   Clamp(short value, short min, short max);
                static inline int     Clamp(int value, int min, int max);
                static inline longint Clamp(longint value, longint min, longint max);
                static inline float   Clamp(float value, float min, float max);
                static inline double  Clamp(double value, double min, double max);

                static float  Mod(float a, float b);
                static double Mod(double a, double b);

                static inline int Wrap(int value, int upper);

                static int  GetNearestPowerOfTwo(int value);

                static bool Equals(float a, float b);
                static bool Equals(Vector2 a, Vector2 b);
                static bool Equals(Vector3 a, Vector3 b);

                static Vector2 GetClosestPoint(Vector2 origin, Vector2 direction, float length, Vector2 point);

                static bool IsClockwise(Vector2 a, Vector2 b, Vector2 c);
                static bool IsClockwise(const Vector2* points, int numberOfPoints);

                static inline short   Lerp(short a, short b, float t);
                static inline int     Lerp(int a, int b, float t);
                static inline longint Lerp(longint a, longint b, float t);
                static inline float   Lerp(float a, float b, float t);
                static inline double  Lerp(double a, double b, float t);
                static inline Point2  Lerp(Point2 a, Point2 b, float t);
                static inline Point3  Lerp(Point3 a, Point3 b, float t);
                static inline Point4  Lerp(Point4 a, Point4 b, float t);
                static inline Rect    Lerp(Rect a, Rect b, float t);
                static inline RectF   Lerp(RectF a, RectF b, float t);
                static inline Vector2 Lerp(Vector2 a, Vector2 b, float t);
                static inline Vector3 Lerp(Vector3 a, Vector3 b, float t);
                static inline Vector4 Lerp(Vector4 a, Vector4 b, float t);
                static inline Color   Lerp(Color a, Color b, float t);

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