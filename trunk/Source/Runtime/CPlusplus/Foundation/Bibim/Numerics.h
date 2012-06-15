#pragma once
#ifndef __BIBIM_NUMERICS_H__
#define __BIBIM_NUMERICS_H__

#   include <Bibim/Foundation.h>
#   include <Bibim/String.h>

    namespace Bibim
    {
        /// @brief byte형에 관련된 정보와 Method가 정의된 class
        ///
        /// byte형은 음수가 없는 8bit 정수형입니다. <br/>
        /// C++의 unsigned char, C#의 System.Byte와 같습니다. <br/>
        class Byte
        {
            BBThisIsStaticClass(Byte);
            public:
                static const byte Min; ///< byte형으로 표현할 수 있는 최소값
                static const byte Max; ///< byte형으로 표현할 수 있는 최대값

                /// @brief 입력받은 문자열을 byte형으로 변환하여 반환합니다.
                /// 
                /// 만약 변환할 수 없는 문자열일 경우 0을 반환합니다. <br />
                /// 만약 변환된 값이 byte형의 범위를 넘어가면 가장 가까운 값을 반환합니다. 
                /// <i>Math::Clamp(x, Byte::Min, Byte::Max)</i>
                static inline byte Parse(const char* s);
                /// @copybrief   Byte::Parse(const char*)
                /// @copydetails Byte::Parse(const char*)
                static inline byte Parse(const String& s);
                /// @copybrief   Parse(const char*)
                /// @copydetails Parse(const char*)
                static byte Parse(const char* s, int length);
        };

        /// @brief short형에 관련된 정보와 Method가 정의된 class
        ///
        /// short형은 16bit 정수형입니다.
        /// C++의 short, C#의 System.Int16과 같습니다.
        class  ShortInt
        {
            BBThisIsStaticClass(ShortInt);
            public:
                static const short Min; ///< short형으로 표현할 수 있는 최소값
                static const short Max; ///< short형으로 표현할 수 있는 최대값

                /// @brief 입력받은 문자열을 short형으로 변환하여 반환합니다.
                /// 
                /// 만약 변환할 수 없는 문자열일 경우 0을 반환합니다. <br />
                /// 만약 변환된 값이 short형의 범위를 넘어가면 가장 가까운 값을 반환합니다. 
                /// <i>Math::Clamp(x, ShortInt::Min, ShortInt::Max)</i>
                static inline short Parse(const char* s);
                /// @copybrief   Parse(const char*)
                /// @copydetails Parse(const char*)
                static inline short Parse(const String& s);
                /// @copybrief   Parse(const char*)
                /// @copydetails Parse(const char*)
                static short Parse(const char* s, int length);
        };

        /// @brief int형에 관련된 정보와 Method가 정의된 class
        ///
        /// int형은 32bit 정수형입니다. 가장 일반적으로 사용됩니다.
        /// C++의 int, C#의 System.Int32과 같습니다.
        class Int
        {
            BBThisIsStaticClass(Int);
            public:
                static const int Min; ///< int형으로 표현할 수 있는 최소값
                static const int Max; ///< int형으로 표현할 수 있는 최대값

                /// @brief 입력받은 문자열을 int형으로 변환하여 반환합니다.
                /// 
                /// 만약 변환할 수 없는 문자열일 경우 0을 반환합니다. <br />
                /// 만약 변환된 값이 int형의 범위를 넘어가면 가장 가까운 값을 반환합니다. 
                /// <i>Math::Clamp(x, Int::Min, Int::Max)</i>
                static inline int Parse(const char* s);
                /// @copybrief   Parse(const char*)
                /// @copydetails Parse(const char*)
                static inline int Parse(const String& s);
                /// @copybrief   Parse(const char*)
                /// @copydetails Parse(const char*)
                static int Parse(const char* s, int length);
        };

        /// @brief longint형에 관련된 정보와 Method가 정의된 class
        ///
        /// longint형은 64bit 정수형입니다.
        /// C#의 System.Int64과 같습니다.
        class LongInt
        {
            BBThisIsStaticClass(LongInt);
            public:
                static const longint Min; ///< longint형으로 표현할 수 있는 최소값
                static const longint Max; ///< longint형으로 표현할 수 있는 최대값

                /// @brief 입력받은 문자열을 longint형으로 변환하여 반환합니다.
                /// 
                /// 만약 변환할 수 없는 문자열일 경우 0을 반환합니다. <br />
                /// 만약 변환된 값이 longint형의 범위를 넘어가면 가장 가까운 값을 반환합니다. 
                /// <i>Math::Clamp(x, LongInt::Min, LongInt::Max)</i>
                static inline longint Parse(const char* s);
                /// @copybrief   Parse(const char*)
                /// @copydetails Parse(const char*)
                static inline longint Parse(const String& s);
                /// @copybrief   Parse(const char*)
                /// @copydetails Parse(const char*)
                static longint Parse(const char* s, int length);
        };

        /// @brief float형에 관련된 정보와 Method가 정의된 class
        ///
        /// float형은 32bit 부동소수점 실수형입니다.
        /// C++의 float, C#의 System.Single과 같습니다.
        class Float
        {
            BBThisIsStaticClass(Float);
            public:
                static const float Min; ///< float형으로 표현할 수 있는 최소값
                static const float Max; ///< float형으로 표현할 수 있는 최대값

                /// @brief 입력받은 문자열을 float형으로 변환하여 반환합니다.
                /// 
                /// 만약 변환할 수 없는 문자열일 경우 0.0f을 반환합니다. <br />
                /// 만약 변환된 값이 float형의 범위를 넘어가면 가장 가까운 값을 반환합니다. 
                /// <i>Math::Clamp(x, Float::Min, Float::Max)</i>
                static inline float Parse(const char* s);
                /// @copybrief   Parse(const char*)
                /// @copydetails Parse(const char*)
                static inline float Parse(const String& s);
                /// @copybrief   Parse(const char*)
                /// @copydetails Parse(const char*)
                static float Parse(const char* s, int length);
        };

        /// @brief double형에 관련된 정보와 Method가 정의된 class
        ///
        /// double형은 64bit 부동소수점 실수형입니다.
        /// C++의 double, C#의 System.Double과 같습니다.
        class Double
        {
            BBThisIsStaticClass(Double);
            public:
                static const double Min; ///< double형으로 표현할 수 있는 최대값
                static const double Max; ///< double형으로 표현할 수 있는 최대값

                /// @brief 입력받은 문자열을 double형으로 변환하여 반환합니다.
                /// 
                /// 만약 변환할 수 없는 문자열일 경우 0.0을 반환합니다. <br />
                /// 만약 변환된 값이 double형의 범위를 넘어가면 가장 가까운 값을 반환합니다. 
                /// <i>Math::Clamp(x, Double::Min, Double::Max)</i>
                static inline double Parse(const char* s);
                /// @copybrief   Parse(const char*)
                /// @copydetails Parse(const char*)
                static inline double Parse(const String& s);
                /// @copybrief   Parse(const char*)
                /// @copydetails Parse(const char*)
                static double Parse(const char* s, int length);
        };
    }

#   include <Bibim/Numerics.inl>

#endif