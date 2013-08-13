#include <Bibim/Config.h>
#include <Bibim/UISineCurveEffect.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Math.h>
#include <Bibim/String.h>

namespace Bibim
{
    BBImplementsComponent(UISineCurveEffect);

    UISineCurveEffect::UISineCurveEffect()
        : amplitude(0.1f),
          offset(0.0f),
          length(Math::Pi),
          form(static_cast<Form>(-1))
    {
        SetForm(VerticalWave);
    }

    UISineCurveEffect::~UISineCurveEffect()
    {
    }

    void UISineCurveEffect::SetAmplitude(float value)
    {
        amplitude = Math::Clamp(value, -0.5f, +0.5f);
    }

    void UISineCurveEffect::SetOffset(float value)
    {
        offset = value;
    }

    void UISineCurveEffect::SetLength(float value)
    {
        length = Math::Max(value, 0.00001f);
    }

    void UISineCurveEffect::SetForm(Form value)
    {
        if (form != value)
        {
            form = value;

            switch (form)
            {
                case VerticalWave:
                case HorizontalWave:
                    startAxisWeight = +1.0f;
                    endAxisWeight   = +1.0f;
                    break;
                case VerticalPot:
                case HorizontalPot:
                    startAxisWeight = +1.0f;
                    endAxisWeight   = -1.0f;
                    break;
                case Left:
                case Top:
                    startAxisWeight = +1.0f;
                    endAxisWeight   = +0.0f;
                    break;
                case Right:
                case Bottom:
                    startAxisWeight = +0.0f;
                    endAxisWeight   = +1.0f;
                    break;
                default:
                    startAxisWeight = +1.0f;
                    endAxisWeight   = +1.0f;
                    break;
            }

        }
    }

    void UISineCurveEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color color)
    {
        switch (form)
        {
            case VerticalWave:
            case VerticalPot:
            case Left:
            case Right:
                {
                    static const int COMPONENT = 0;
                    static const int OTHER_COMPONENT = 1;
                    static const int S0 = 0;
                    static const int S1 = 1;
                    static const int E0 = 2;
                    static const int E1 = 3;

                    Vector2 np[4];
                    const float actualOffset = Math::TwoPi * offset;
                    const float actualLength = Math::TwoPi / length;
                    const float actualAmplitude = amplitude * (Vector2::Get<COMPONENT>(p[S1]) - Vector2::Get<COMPONENT>(p[S0]));

                    const float sin = Math::Sin(actualOffset) * actualAmplitude;
                    np[E0] = p[S0];
                    np[E1] = p[S1];
                    Vector2::Add<COMPONENT>(np[E0], sin * startAxisWeight);
                    Vector2::Add<COMPONENT>(np[E1], sin * endAxisWeight);

                    const float size = Math::Abs(Vector2::Get<OTHER_COMPONENT>(p[E0]) - Vector2::Get<OTHER_COMPONENT>(p[S0]));
                    const int count = Math::Max(static_cast<int>(size) / 2, 2);
                    const float floatCount = static_cast<float>(count);
                    for (int i = 1; i <= count; i++)
                    {
                        const float t = static_cast<float>(i) / floatCount;
                        const float sin = Math::Sin(actualOffset + (t * actualLength)) * actualAmplitude;

                        np[S0] = np[E0];
                        np[S1] = np[E1];
                        np[E0] = Math::Lerp(p[S0], p[E0], t);
                        np[E1] = Math::Lerp(p[S1], p[E1], t);
                        Vector2::Add<COMPONENT>(np[E0], sin * startAxisWeight);
                        Vector2::Add<COMPONENT>(np[E1], sin * endAxisWeight);

                        Base::DrawQuad(renderer, np, color);
                    }
                }
                break;
            case HorizontalWave:
            case HorizontalPot:
            case Top:
            case Bottom:
                {
                    static const int COMPONENT = 1;
                    static const int OTHER_COMPONENT = 0;
                    static const int S0 = 0;
                    static const int S1 = 2;
                    static const int E0 = 1;
                    static const int E1 = 3;

                    Vector2 np[4];
                    const float actualOffset = Math::TwoPi * offset;
                    const float actualLength = Math::TwoPi / length;
                    const float actualAmplitude = amplitude * (Vector2::Get<COMPONENT>(p[S1]) - Vector2::Get<COMPONENT>(p[S0]));

                    const float sin = Math::Sin(actualOffset) * actualAmplitude;
                    np[E0] = p[S0];
                    np[E1] = p[S1];
                    Vector2::Add<COMPONENT>(np[E0], sin * startAxisWeight);
                    Vector2::Add<COMPONENT>(np[E1], sin * endAxisWeight);

                    const float size = Math::Abs(Vector2::Get<OTHER_COMPONENT>(p[E0]) - Vector2::Get<OTHER_COMPONENT>(p[S0]));
                    const int count = Math::Max(static_cast<int>(size) / 2, 2);
                    const float floatCount = static_cast<float>(count);
                    for (int i = 1; i <= count; i++)
                    {
                        const float t = static_cast<float>(i) / floatCount;
                        const float sin = Math::Sin(actualOffset + (t * actualLength)) * actualAmplitude;

                        np[S0] = np[E0];
                        np[S1] = np[E1];
                        np[E0] = Math::Lerp(p[S0], p[E0], t);
                        np[E1] = Math::Lerp(p[S1], p[E1], t);
                        Vector2::Add<COMPONENT>(np[E0], sin * startAxisWeight);
                        Vector2::Add<COMPONENT>(np[E1], sin * endAxisWeight);

                        Base::DrawQuad(renderer, np, color);
                    }
                }
                break;
        }
    }

    void UISineCurveEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color color, Vector2* uv, Texture2D* texture)
    {
        switch (form)
        {
            case VerticalWave:
            case VerticalPot:
            case Left:
            case Right:
                {
                    static const int COMPONENT = 0;
                    static const int OTHER_COMPONENT = 1;
                    static const int S0 = 0;
                    static const int S1 = 1;
                    static const int E0 = 2;
                    static const int E1 = 3;

                    Vector2 np[4];
                    Vector2 nuv[4];
                    const float actualOffset = Math::TwoPi * offset;
                    const float actualLength = Math::TwoPi / length;
                    const float actualAmplitude = amplitude * (Vector2::Get<COMPONENT>(p[S1]) - Vector2::Get<COMPONENT>(p[S0]));

                    const float sin = Math::Sin(actualOffset) * actualAmplitude;
                    np[E0] = p[S0];
                    np[E1] = p[S1];
                    Vector2::Add<COMPONENT>(np[E0], sin * startAxisWeight);
                    Vector2::Add<COMPONENT>(np[E1], sin * endAxisWeight);
                    nuv[E0] = uv[S0];
                    nuv[E1] = uv[S1];

                    const float size = Math::Abs(Vector2::Get<OTHER_COMPONENT>(p[E0]) - Vector2::Get<OTHER_COMPONENT>(p[S0]));
                    const int count = Math::Max(static_cast<int>(size) / 2, 2);
                    const float floatCount = static_cast<float>(count);
                    for (int i = 1; i <= count; i++)
                    {
                        const float t = static_cast<float>(i) / floatCount;
                        const float sin = Math::Sin(actualOffset + (t * actualLength)) * actualAmplitude;

                        np[S0] = np[E0];
                        np[S1] = np[E1];
                        np[E0] = Math::Lerp(p[S0], p[E0], t);
                        np[E1] = Math::Lerp(p[S1], p[E1], t);
                        Vector2::Add<COMPONENT>(np[E0], sin * startAxisWeight);
                        Vector2::Add<COMPONENT>(np[E1], sin * endAxisWeight);

                        nuv[S0] = nuv[E0];
                        nuv[S1] = nuv[E1];
                        nuv[E0] = Math::Lerp(uv[S0], uv[E0], t);
                        nuv[E1] = Math::Lerp(uv[S1], uv[E1], t);

                        Base::DrawQuad(renderer, np, color, nuv, texture);
                    }
                }
                break;
            case HorizontalWave:
            case HorizontalPot:
            case Top:
            case Bottom:
                {
                    static const int COMPONENT = 1;
                    static const int OTHER_COMPONENT = 0;
                    static const int S0 = 0;
                    static const int S1 = 2;
                    static const int E0 = 1;
                    static const int E1 = 3;

                    Vector2 np[4];
                    Vector2 nuv[4];
                    const float actualOffset = Math::TwoPi * offset;
                    const float actualLength = Math::TwoPi / length;
                    const float actualAmplitude = amplitude * (Vector2::Get<COMPONENT>(p[S1]) - Vector2::Get<COMPONENT>(p[S0]));

                    const float sin = Math::Sin(actualOffset) * actualAmplitude;
                    np[E0] = p[S0];
                    np[E1] = p[S1];
                    Vector2::Add<COMPONENT>(np[E0], sin * startAxisWeight);
                    Vector2::Add<COMPONENT>(np[E1], sin * endAxisWeight);
                    nuv[E0] = uv[S0];
                    nuv[E1] = uv[S1];

                    const float size = Math::Abs(Vector2::Get<OTHER_COMPONENT>(p[E0]) - Vector2::Get<OTHER_COMPONENT>(p[S0]));
                    const int count = Math::Max(static_cast<int>(size) / 2, 2);
                    const float floatCount = static_cast<float>(count);
                    for (int i = 1; i <= count; i++)
                    {
                        const float t = static_cast<float>(i) / floatCount;
                        const float sin = Math::Sin(actualOffset + (t * actualLength)) * actualAmplitude;

                        np[S0] = np[E0];
                        np[S1] = np[E1];
                        np[E0] = Math::Lerp(p[S0], p[E0], t);
                        np[E1] = Math::Lerp(p[S1], p[E1], t);
                        Vector2::Add<COMPONENT>(np[E0], sin * startAxisWeight);
                        Vector2::Add<COMPONENT>(np[E1], sin * endAxisWeight);

                        nuv[S0] = nuv[E0];
                        nuv[S1] = nuv[E1];
                        nuv[E0] = Math::Lerp(uv[S0], uv[E0], t);
                        nuv[E1] = Math::Lerp(uv[S1], uv[E1], t);

                        Base::DrawQuad(renderer, np, color, nuv, texture);
                    }
                }
                break;
        }
    }

    void UISineCurveEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color color, Vector2* uv1, Texture2D* texture1, Vector2* uv2, Texture2D* texture2)
    {
        switch (form)
        {
            case VerticalWave:
            case VerticalPot:
            case Left:
            case Right:
                {
                    static const int COMPONENT = 0;
                    static const int OTHER_COMPONENT = 1;
                    static const int S0 = 0;
                    static const int S1 = 1;
                    static const int E0 = 2;
                    static const int E1 = 3;

                    Vector2 np[4];
                    Vector2 nuv1[4];
                    Vector2 nuv2[4];
                    const float actualOffset = Math::TwoPi * offset;
                    const float actualLength = Math::TwoPi / length;
                    const float actualAmplitude = amplitude * (Vector2::Get<COMPONENT>(p[S1]) - Vector2::Get<COMPONENT>(p[S0]));

                    const float sin = Math::Sin(actualOffset) * actualAmplitude;
                    np[E0] = p[S0];
                    np[E1] = p[S1];
                    Vector2::Add<COMPONENT>(np[E0], sin * startAxisWeight);
                    Vector2::Add<COMPONENT>(np[E1], sin * endAxisWeight);
                    nuv1[E0] = uv1[S0];
                    nuv1[E1] = uv1[S1];
                    nuv2[E0] = uv2[S0];
                    nuv2[E1] = uv2[S1];

                    const float size = Math::Abs(Vector2::Get<OTHER_COMPONENT>(p[E0]) - Vector2::Get<OTHER_COMPONENT>(p[S0]));
                    const int count = Math::Max(static_cast<int>(size) / 2, 2);
                    const float floatCount = static_cast<float>(count);
                    for (int i = 1; i <= count; i++)
                    {
                        const float t = static_cast<float>(i) / floatCount;
                        const float sin = Math::Sin(actualOffset + (t * actualLength)) * actualAmplitude;

                        np[S0] = np[E0];
                        np[S1] = np[E1];
                        np[E0] = Math::Lerp(p[S0], p[E0], t);
                        np[E1] = Math::Lerp(p[S1], p[E1], t);
                        Vector2::Add<COMPONENT>(np[E0], sin * startAxisWeight);
                        Vector2::Add<COMPONENT>(np[E1], sin * endAxisWeight);

                        nuv1[S0] = nuv1[E0];
                        nuv1[S1] = nuv1[E1];
                        nuv1[E0] = Math::Lerp(uv1[S0], uv1[E0], t);
                        nuv1[E1] = Math::Lerp(uv1[S1], uv1[E1], t);

                        nuv2[S0] = nuv2[E0];
                        nuv2[S1] = nuv2[E1];
                        nuv2[E0] = Math::Lerp(uv2[S0], uv2[E0], t);
                        nuv2[E1] = Math::Lerp(uv2[S1], uv2[E1], t);

                        Base::DrawQuad(renderer, np, color, nuv1, texture1, nuv2, texture2);
                    }
                }
                break;
            case HorizontalWave:
            case HorizontalPot:
            case Top:
            case Bottom:
                {
                    static const int COMPONENT = 1;
                    static const int OTHER_COMPONENT = 0;
                    static const int S0 = 0;
                    static const int S1 = 2;
                    static const int E0 = 1;
                    static const int E1 = 3;

                    Vector2 np[4];
                    Vector2 nuv1[4];
                    Vector2 nuv2[4];
                    const float actualOffset = Math::TwoPi * offset;
                    const float actualLength = Math::TwoPi / length;
                    const float actualAmplitude = amplitude * (Vector2::Get<COMPONENT>(p[S1]) - Vector2::Get<COMPONENT>(p[S0]));

                    const float sin = Math::Sin(actualOffset) * actualAmplitude;
                    np[E0] = p[S0];
                    np[E1] = p[S1];
                    Vector2::Add<COMPONENT>(np[E0], sin * startAxisWeight);
                    Vector2::Add<COMPONENT>(np[E1], sin * endAxisWeight);
                    nuv1[E0] = uv1[S0];
                    nuv1[E1] = uv1[S1];
                    nuv2[E0] = uv2[S0];
                    nuv2[E1] = uv2[S1];

                    const float size = Math::Abs(Vector2::Get<OTHER_COMPONENT>(p[E0]) - Vector2::Get<OTHER_COMPONENT>(p[S0]));
                    const int count = Math::Max(static_cast<int>(size) / 2, 2);
                    const float floatCount = static_cast<float>(count);
                    for (int i = 1; i <= count; i++)
                    {
                        const float t = static_cast<float>(i) / floatCount;
                        const float sin = Math::Sin(actualOffset + (t * actualLength)) * actualAmplitude;

                        np[S0] = np[E0];
                        np[S1] = np[E1];
                        np[E0] = Math::Lerp(p[S0], p[E0], t);
                        np[E1] = Math::Lerp(p[S1], p[E1], t);
                        Vector2::Add<COMPONENT>(np[E0], sin * startAxisWeight);
                        Vector2::Add<COMPONENT>(np[E1], sin * endAxisWeight);

                        nuv1[S0] = nuv1[E0];
                        nuv1[S1] = nuv1[E1];
                        nuv1[E0] = Math::Lerp(uv1[S0], uv1[E0], t);
                        nuv1[E1] = Math::Lerp(uv1[S1], uv1[E1], t);

                        nuv2[S0] = nuv2[E0];
                        nuv2[S1] = nuv2[E1];
                        nuv2[E0] = Math::Lerp(uv2[S0], uv2[E0], t);
                        nuv2[E1] = Math::Lerp(uv2[S1], uv2[E1], t);

                        Base::DrawQuad(renderer, np, color, nuv1, texture1, nuv2, texture2);
                    }
                }
                break;
        }
    }

    void UISineCurveEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color color, RectF clippingRect, Texture2D* texture)
    {
        Vector2 uv[] =
        {
            Vector2(clippingRect.GetLeft(),  clippingRect.GetTop()),
            Vector2(clippingRect.GetRight(), clippingRect.GetTop()),
            Vector2(clippingRect.GetLeft(),  clippingRect.GetBottom()),
            Vector2(clippingRect.GetRight(), clippingRect.GetBottom()),
        };
        This::DrawQuad(renderer, p, color, uv, texture);
    }

    void UISineCurveEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color color, RectF clippingRect, Texture2D* texture1, Vector2* uv2, Texture2D* texture2)
    {
        Vector2 uv[] =
        {
            Vector2(clippingRect.GetLeft(),  clippingRect.GetTop()),
            Vector2(clippingRect.GetRight(), clippingRect.GetTop()),
            Vector2(clippingRect.GetLeft(),  clippingRect.GetBottom()),
            Vector2(clippingRect.GetRight(), clippingRect.GetBottom()),
        };
        This::DrawQuad(renderer, p, color, uv, texture1, uv2, texture2);
    }

    void UISineCurveEffect::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        amplitude = reader.ReadFloat();
        offset = reader.ReadFloat();
        length = reader.ReadFloat();
        SetForm(static_cast<Form>(reader.ReadByte()));
    }

    void UISineCurveEffect::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        amplitude = o->amplitude;
        offset = o->offset;
        length = o->length;
        form = o->form;
        startAxisWeight = o->startAxisWeight;
        endAxisWeight = o->endAxisWeight;
    }

    UISineCurveEffect::Form UISineCurveEffect::ConvertFromStringToForm(const char* value)
    {
             if (value == nullptr)                                       return VerticalWave;
        else if (String::EqualsCharsIgnoreCase(value, "Vertical"))       return VerticalWave;
        else if (String::EqualsCharsIgnoreCase(value, "VerticalWave"))   return VerticalWave;
        else if (String::EqualsCharsIgnoreCase(value, "VerticalPot"))    return VerticalPot;
        else if (String::EqualsCharsIgnoreCase(value, "Horizontal"))     return HorizontalWave;
        else if (String::EqualsCharsIgnoreCase(value, "HorizontalWave")) return HorizontalWave;
        else if (String::EqualsCharsIgnoreCase(value, "HorizontalPot"))  return HorizontalPot;
        else if (String::EqualsCharsIgnoreCase(value, "Left"))           return Left;
        else if (String::EqualsCharsIgnoreCase(value, "Right"))          return Right;
        else if (String::EqualsCharsIgnoreCase(value, "Top"))            return Top;
        else if (String::EqualsCharsIgnoreCase(value, "Bottom"))         return Bottom;
        else                                                             return VerticalWave;
    }
    
    const char* UISineCurveEffect::ConvertFromFormToString(Form value)
    {
        switch (value)
        {
            case VerticalWave:      return "VerticalWave";
            case VerticalPot:       return "VerticalPot";
            case Left:              return "Left";
            case Right:             return "Right";
            case HorizontalWave:    return "HorizontalWave";
            case HorizontalPot:     return "HorizontalPot";
            case Top:               return "Top";
            case Bottom:            return "Bottom";
            default:                return "VerticalWave";
        }
    }
}