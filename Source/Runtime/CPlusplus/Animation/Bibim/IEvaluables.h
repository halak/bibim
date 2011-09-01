#ifndef __BIBIM_EVALUABLE_INTERFACE_H__
#define __BIBIM_EVALUABLE_INTERFACE_H__

#   include <Bibim/IBoolEvaluable.h>
#   include <Bibim/ICharEvaluable.h>
#   include <Bibim/IColorEvaluable.h>
#   include <Bibim/IDoubleEvaluable.h>
#   include <Bibim/IFloatEvaluable.h>
#   include <Bibim/IIntEvaluable.h>
#   include <Bibim/ILongEvaluable.h>
#   include <Bibim/IPointEvaluable.h>
#   include <Bibim/IQuaternionEvaluable.h>
#   include <Bibim/IRectangleEvaluable.h>
#   include <Bibim/IShortEvaluable.h>
#   include <Bibim/ISpriteEvaluable.h>
#   include <Bibim/IUCharEvaluable.h>
#   include <Bibim/IUIntEvaluable.h>
#   include <Bibim/IULongEvaluable.h>
#   include <Bibim/IUShortEvaluable.h>
#   include <Bibim/IVector2Evaluable.h>
#   include <Bibim/IVector3Evaluable.h>
#   include <Bibim/IVector4Evaluable.h>

#   include <Bibim/IFloatRangeEvaluable.h>

    namespace Bibim
    {
        template <typename T> struct SelectEvaluableInterface
        {
        };

        template <> struct SelectEvaluableInterface<bool>            { typedef IBoolEvaluable         Result; };
        template <> struct SelectEvaluableInterface<char>            { typedef ICharEvaluable         Result; };
        template <> struct SelectEvaluableInterface<unsigned char>   { typedef IUCharEvaluable        Result; };
        template <> struct SelectEvaluableInterface<short>           { typedef IShortEvaluable        Result; };
        template <> struct SelectEvaluableInterface<unsigned short>  { typedef IUShortEvaluable       Result; };
        template <> struct SelectEvaluableInterface<int>             { typedef IIntEvaluable          Result; };
        template <> struct SelectEvaluableInterface<unsigned int>    { typedef IUIntEvaluable         Result; };
        template <> struct SelectEvaluableInterface<long>            { typedef ILongEvaluable         Result; };
        template <> struct SelectEvaluableInterface<unsigned long>   { typedef IULongEvaluable        Result; };
        template <> struct SelectEvaluableInterface<float>           { typedef IFloatEvaluable        Result; };
        template <> struct SelectEvaluableInterface<double>          { typedef IDoubleEvaluable       Result; };
        template <> struct SelectEvaluableInterface<Point>           { typedef IPointEvaluable        Result; };
        template <> struct SelectEvaluableInterface<Rectangle>       { typedef IRectangleEvaluable    Result; };
        template <> struct SelectEvaluableInterface<Vector2>         { typedef IVector2Evaluable      Result; };
        template <> struct SelectEvaluableInterface<Vector3>         { typedef IVector3Evaluable      Result; };
        template <> struct SelectEvaluableInterface<Vector4>         { typedef IVector4Evaluable      Result; };
        template <> struct SelectEvaluableInterface<Quaternion>      { typedef IQuaternionEvaluable   Result; };
        template <> struct SelectEvaluableInterface<Color>           { typedef IColorEvaluable        Result; };
        template <> struct SelectEvaluableInterface<Sprite>          { typedef ISpriteEvaluable       Result; };

        template <> struct SelectEvaluableInterface<FloatRange>      { typedef IFloatRangeEvaluable   Result; };
    }

#endif