#pragma once
#ifndef __BIBIM_RANDOM_H__
#define __BIBIM_RANDOM_H__

#include <Bibim/Foundation.h>
#include <Bibim/Color.h>
#include <Bibim/Point2.h>
#include <Bibim/Point3.h>
#include <Bibim/Point4.h>
#include <Bibim/Rect.h>
#include <Bibim/RectF.h>
#include <Bibim/Vector2.h>
#include <Bibim/Vector3.h>
#include <Bibim/Vector4.h>

namespace Bibim
{
    /// `WELL512a` 난수 생성 알고리즘을 클래스로 래핑하였습니다.
    /// http://www.iro.umontreal.ca/~panneton/WELLRNG.html
    class Random
    {
        public:
            Random();
            Random(uint seed);
            Random(const Random& original);

            double Next();

            bool    TrueOrFalse();
            int     Range(int a, int b);
            float   Range(float a, float b);
            double  Range(double a, double b);
            Vector2 Range(Vector2 a, Vector2 b);
            Vector3 Range(Vector3 a, Vector3 b);
            Vector4 Range(Vector4 a, Vector4 b);
            Color   Range(Color a, Color b);

            Random& operator = (const Random& right);

        private:
            static const int W = 32;
            static const int R = 16;
            static const int P = 0;
            static const int M1 = 13;
            static const int M2 = 9;
            static const int M3 = 5;
            static const double FACT;

            uint index;
            uint states[R];
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    /// 편리하게 사용하기 위하여 만들어놓은 class.
    /// std::rand()와 비슷한 느낌을 내기 위해 Rand라고 이름지었습니다.
    class Rand
    {
        BBThisIsStaticClass(Rand);
        public:
            static inline bool    TrueOrFalse();
            static inline int     Range(int a, int b);
            static inline float   Range(float a, float b);
            static inline double  Range(double a, double b);
            static inline Vector2 Range(Vector2 a, Vector2 b);
            static inline Vector3 Range(Vector3 a, Vector3 b);
            static inline Vector4 Range(Vector4 a, Vector4 b);
            static inline Color   Range(Color a, Color b);

        private:
            static Random Global;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Rand::TrueOrFalse()
    {
        return Global.TrueOrFalse();
    }

    int Rand::Range(int a, int b)
    {
        return Global.Range(a, b);
    }

    float Rand::Range(float a, float b)
    {
        return Global.Range(a, b);
    }

    double Rand::Range(double a, double b)
    {
        return Global.Range(a, b);
    }

    Vector2 Rand::Range(Vector2 a, Vector2 b)
    {
        return Global.Range(a, b);
    }

    Vector3 Rand::Range(Vector3 a, Vector3 b)
    {
        return Global.Range(a, b);
    }

    Vector4 Rand::Range(Vector4 a, Vector4 b)
    {
        return Global.Range(a, b);
    }

    Color Rand::Range(Color a, Color b)
    {
        return Global.Range(a, b);
    }

}

/* ***************************************************************************** */
/* Copyright:      Francois Panneton and Pierre L'Ecuyer, University of Montreal */
/*                 Makoto Matsumoto, Hiroshima University                        */
/* Notice:         This code can be used freely for personal, academic,          */
/*                 or non-commercial purposes. For commercial purposes,          */
/*                 please contact P. L'Ecuyer at: lecuyer@iro.UMontreal.ca       */
/* ***************************************************************************** */

#endif