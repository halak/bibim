#include <Bibim/PCH.h>
#include <Bibim/EvalContext.h>
#include <Bibim/AnyStorage.h>
#include <Bibim/GameAsset.h>

namespace Bibim
{
    EvalContext::EvalContext()
    {
    }

    EvalContext::EvalContext(AnyStorage* variables)
        : variables(variables)
    {
    }

    EvalContext::~EvalContext()
    {
    }

    template <>
    bool EvalContext::GetValue<bool>(const String& name)
    {
        if (variables)
            return variables->GetValue(name).CastBool();
        else
            return false;
    }

    template <>
    short EvalContext::GetValue<short>(const String& name)
    {
        if (variables)
            return static_cast<short>(variables->GetValue(name).CastInt());
        else
            return 0;
    }

    template <>
    int EvalContext::GetValue<int>(const String& name)
    {
        if (variables)
            return variables->GetValue(name).CastInt();
        else
            return 0;
    }

    template <>
    longint EvalContext::GetValue<longint>(const String& name)
    {
        if (variables)
            return variables->GetValue(name).CastLongInt();
        else
            return 0;
    }

    template <>
    float EvalContext::GetValue<float>(const String& name)
    {
        if (variables)
            return variables->GetValue(name).CastFloat();
        else
            return 0.0f;
    }

    template <>
    double EvalContext::GetValue<double>(const String& name)
    {
        if (variables)
            return static_cast<double>(variables->GetValue(name).CastFloat());
        else
            return 0.0;
    }

    template <>
    Color EvalContext::GetValue<Color>(const String& name)
    {
        return variables->GetValue(name).CastColor();
    }

    template <>
    Point2 EvalContext::GetValue<Point2>(const String& /*name*/)
    {
        return Point2::Zero;
    }

    template <>
    Point3 EvalContext::GetValue<Point3>(const String& /*name*/)
    {
        return Point3::Zero;
    }

    template <>
    Point4 EvalContext::GetValue<Point4>(const String& /*name*/)
    {
        return Point4::Zero;
    }

    template <>
    Rect EvalContext::GetValue<Rect>(const String& /*name*/)
    {
        return Rect::Empty;
    }

    template <>
    RectF EvalContext::GetValue<RectF>(const String& /*name*/)
    {
        return RectF::Empty;
    }

    template <>
    Vector2 EvalContext::GetValue<Vector2>(const String& /*name*/)
    {
        return Vector2::Zero;
    }

    template <>
    Vector3 EvalContext::GetValue<Vector3>(const String& /*name*/)
    {
        return Vector3::Zero;
    }

    template <>
    Vector4 EvalContext::GetValue<Vector4>(const String& /*name*/)
    {
        return Vector4::Zero;
    }

    template <>
    GameAsset* EvalContext::GetValue<GameAsset*>(const String& /*name*/)
    {
        return nullptr;
    }
}