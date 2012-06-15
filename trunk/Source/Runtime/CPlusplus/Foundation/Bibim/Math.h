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
        /// @brief 산술 수학 관련 함수들이 주로 정의되어 있는 static class
        class Math
        {
            BBThisIsStaticClass(Math);
            public:
                static const float E;       ///< \f$e\f$
                static const float Log10E;  ///< \f$log_{10}{e}\f$
                static const float Log2E;   ///< \f$log_{2}{e}\f$
                static const float Pi;      ///< \f$pi\f$
                static const float PiOver2; ///< \f$\frac{pi}{2}\f$
                static const float PiOver4; ///< \f$\frac{pi}{4}\f$
                static const float TwoPi;   ///< \f$2\pi\f$

                /// 입력한 값의 제곱근을 반환합니다. \f$sqrt(x)\f$
                static float Sqrt(float value);
                /// x를 y만큼 제곱하여 반환합니다. \f$x^y\f$
                static float Pow(float x, float y);
                /// 입력한 호도법 각의 sine 값을 반환합니다. \f$sin(x)\f$
                static float Sin(float radian);
                /// 입력한 호도법 각의 cosine 값을 반환합니다. \f$cos(x)\f$
                static float Cos(float radian);
                /// 입력한 호도법 각의 tangent 값을 반환합니다. \f$tan(x)\f$
                static float Tan(float radian);
                /// 입력한 호도법 각의 arc-sine 값을 반환합니다. \f$asin(x)\f$
                static float Asin(float radian);
                /// 입력한 호도법 각의 arc-cosine 값을 반환합니다. \f$acos(x)\f$
                static float Acos(float radian);
                /// 입력한 높이와 밑변의 길이를 이용하여 arc-tangent 값을 계산한 후 반환합니다. \f$atan(\frac{y}{x})\f$
                static float Atan2(float y, float x);
                /// 입력한 높이와 밑변의 길이를 이용하여 arc-tangent 값을 계산한 후 반환합니다. \f$atan(\frac{y}{x})\f$
                static inline float Atan2(Vector2 xy);
                static float Exp(float value);

                static inline short   Abs(short value);   ///< 입력한 값의 절대값을 반환합니다.
                static inline int     Abs(int value);     ///< 입력한 값의 절대값을 반환합니다.
                static inline longint Abs(longint value); ///< 입력한 값의 절대값을 반환합니다.
                static inline float   Abs(float value);   ///< 입력한 값의 절대값을 반환합니다.
                static inline double  Abs(double value);  ///< 입력한 값의 절대값을 반환합니다.

                static inline byte    Min(byte a, byte b);       ///< 입력한 두 값 중 작은 값을 반환합니다.
                static inline short   Min(short a, short b);     ///< 입력한 두 값 중 작은 값을 반환합니다.
                static inline int     Min(int a, int b);         ///< 입력한 두 값 중 작은 값을 반환합니다.
                static inline longint Min(longint a, longint b); ///< 입력한 두 값 중 작은 값을 반환합니다.
                static inline float   Min(float a, float b);     ///< 입력한 두 값 중 작은 값을 반환합니다.
                static inline double  Min(double a, double b);   ///< 입력한 두 값 중 작은 값을 반환합니다.

                static inline byte    Max(byte a, byte b);       ///< 입력한 두 값 중 큰 값을 반환합니다.
                static inline short   Max(short a, short b);     ///< 입력한 두 값 중 큰 값을 반환합니다.
                static inline int     Max(int a, int b);         ///< 입력한 두 값 중 큰 값을 반환합니다.
                static inline longint Max(longint a, longint b); ///< 입력한 두 값 중 큰 값을 반환합니다.
                static inline float   Max(float a, float b);     ///< 입력한 두 값 중 큰 값을 반환합니다.
                static inline double  Max(double a, double b);   ///< 입력한 두 값 중 큰 값을 반환합니다.

                static inline byte    Min(byte a, byte b, byte c);          ///< 입력한 세 값 중 작은 값을 반환합니다.
                static inline short   Min(short a, short b, short c);       ///< 입력한 세 값 중 작은 값을 반환합니다.
                static inline int     Min(int a, int b, int c);             ///< 입력한 세 값 중 작은 값을 반환합니다.
                static inline longint Min(longint a, longint b, longint c); ///< 입력한 세 값 중 작은 값을 반환합니다.
                static inline float   Min(float a, float b, float c);       ///< 입력한 세 값 중 작은 값을 반환합니다.
                static inline double  Min(double a, double b, double c);    ///< 입력한 세 값 중 작은 값을 반환합니다.

                static inline byte    Max(byte a, byte b, byte c);          ///< 입력한 세 값 중 큰 값을 반환합니다.
                static inline short   Max(short a, short b, short c);       ///< 입력한 세 값 중 큰 값을 반환합니다.
                static inline int     Max(int a, int b, int c);             ///< 입력한 세 값 중 큰 값을 반환합니다.
                static inline longint Max(longint a, longint b, longint c); ///< 입력한 세 값 중 큰 값을 반환합니다.
                static inline float   Max(float a, float b, float c);       ///< 입력한 세 값 중 큰 값을 반환합니다.
                static inline double  Max(double a, double b, double c);    ///< 입력한 세 값 중 큰 값을 반환합니다.

                static inline byte    Clamp(byte value, byte min, byte max);          ///< value를 [min, max] 범위에 맞춰 반환합니다.
                static inline short   Clamp(short value, short min, short max);       ///< value를 [min, max] 범위에 맞춰 반환합니다.
                static inline int     Clamp(int value, int min, int max);             ///< value를 [min, max] 범위에 맞춰 반환합니다.
                static inline longint Clamp(longint value, longint min, longint max); ///< value를 [min, max] 범위에 맞춰 반환합니다.
                static inline float   Clamp(float value, float min, float max);       ///< value를 [min, max] 범위에 맞춰 반환합니다.
                static inline double  Clamp(double value, double min, double max);    ///< value를 [min, max] 범위에 맞춰 반환합니다.

                static float  Mod(float a, float b);
                static double Mod(double a, double b);

                static inline int Wrap(int value, int upper);

                static int GetNearestPowerOfTwo(int value);

                /// @brief 근사 비교법을 이용하여 입력한 두 값이 같은지 확인합니다.
                /// 
                /// 부동소수점 실수형은 연산시 오차로 인하여,
                /// 같은 결과의 식도 == 연산자로 비교했을 때 false 결과가 나올 수 있습니다 <br />
                /// @code
                /// 17.0f * (1.0f / 17.0f) == 1.0f // false
                /// @endcode
                /// Equals 함수는 두 부동소수점의 차를 구하여
                /// Epsilon(0.00001f)보다 작은지 비교하는 방식으로 두 값이 같은지 확인합니다.
                static bool Equals(float a, float b);
                /// @copybrief   Equals(float, float)
                /// @copydetails Equals(float, float)
                static bool Equals(Vector2 a, Vector2 b);
                /// @copybrief   Equals(float, float)
                /// @copydetails Equals(float, float)
                static bool Equals(Vector3 a, Vector3 b);

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