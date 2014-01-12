#include <Bibim/Config.h>
#include <Bibim/UITrail.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Math.h>
#include <Bibim/UIDrawingContext.h>
#include <Bibim/Texture2D.h>

namespace Bibim
{
    BBImplementsComponent(UITrail);

    UITrail::UITrail()
        : thickness(16.0f),
          numberOfTrails(10)
    {
        SetSize(1.0f, 1.0f);
        SetSizeMode(ContentSize, ContentSize);

        Clear();
    }

    UITrail::~UITrail()
    {
    }

    void UITrail::Clear()
    {
        trails.clear();
        lines1.clear();
        lines2.clear();
        triangles.clear();
        triangleUVs.clear();
        triangleColors.clear();
        lastDirection = Vector2::Zero;
        trailLength = 0.0f;

        triangleColors.resize((numberOfTrails - 1) * 6);
        const int count = static_cast<int>(triangleColors.size());
        int i = 0;
        for (; i < count / 2; i += 6)
        {
            const float t = static_cast<float>(i) / static_cast<float>(count / 2);
            const byte opacity = static_cast<byte>(255.0f * t);

            triangleColors[i + 0] = Color(255, 255, 255, opacity);
            triangleColors[i + 1] = Color(255, 255, 255, opacity);
            triangleColors[i + 2] = Color(255, 255, 255, opacity);
            triangleColors[i + 3] = Color(255, 255, 255, opacity);
            triangleColors[i + 4] = Color(255, 255, 255, opacity);
            triangleColors[i + 5] = Color(255, 255, 255, opacity);
        }

        for (; i < count; i += 6)
        {
            triangleColors[i + 0] = Color::White;
            triangleColors[i + 1] = Color::White;
            triangleColors[i + 2] = Color::White;
            triangleColors[i + 3] = Color::White;
            triangleColors[i + 4] = Color::White;
            triangleColors[i + 5] = Color::White;
        }
    }

    void UITrail::SetThickness(float value)
    {
        thickness = Math::Max(value, 0.0f);
    }

    void UITrail::SetTrails(int value)
    {
        numberOfTrails = Math::Max(value, 3);
        Clear();
    }

    void UITrail::SetSource(Texture2D* value)
    {
        source = value;
    }

    Vector2 UITrail::GetContentSize()
    {
        return Vector2(thickness, thickness);
    }

    void UITrail::OnDraw(UIDrawingContext& context)
    {
        UIVisual::OnDraw(context);

        const Vector2 current = context.GetCurrentBounds().GetCenterPoint();

        if (trails.empty() || trails.back() != current)
        {
            trails.push_back(current);

        if (trails.size() >= 2)
        {
            const float oldTrailLength = trailLength;
            const Vector2 previous = trails[trails.size() - 2];
            Vector2 direction = current - previous;
            trailLength += direction.Normalize();

            if (lastDirection != Vector2::Zero)
            {
                float current = lastDirection.ToRadian();
                float desired = direction.ToRadian();

                float delta = Math::TwoPi * 4.0f * (1.0f/60.0f);
                if (Math::Abs(desired - current) > delta)
                {
                    float d;
                    if (Math::Abs(desired - current) < Math::Pi)
                        d = (desired - current) / Math::Abs(desired - current);
                    else
                        d = (current - desired) / Math::Abs(desired - current);

                    current += d * delta;
                }
                else
                    current = desired;

                lastDirection = Vector2::UnitX;
                lastDirection.Rotate(current);
            }
            else
                lastDirection = direction;

            const Vector2 normal = Vector2(-lastDirection.Y, lastDirection.X);
            const float halfThickness = GetThickness() * 0.5f;

            if (trails.size() == 2)
            {
                lines1.push_back(previous + normal * halfThickness);
                lines2.push_back(previous - normal * halfThickness);
            }

            lines1.push_back(current + normal * halfThickness);
            lines2.push_back(current - normal * halfThickness);

            if (lines1.size() >= 2)
            {
                triangles.push_back(lines1[lines1.size() - 2]);
                triangles.push_back(lines2[lines2.size() - 1]);
                triangles.push_back(lines1[lines1.size() - 1]);

                triangles.push_back(lines1[lines1.size() - 2]);
                triangles.push_back(lines2[lines2.size() - 2]);
                triangles.push_back(lines2[lines2.size() - 1]);

                const float ox = oldTrailLength; // old x
                const float nx = trailLength; // new x

                triangleUVs.push_back(Vector2(0.0f, ox));
                triangleUVs.push_back(Vector2(1.0f, nx));
                triangleUVs.push_back(Vector2(0.0f, nx));

                triangleUVs.push_back(Vector2(0.0f, ox));
                triangleUVs.push_back(Vector2(1.0f, ox));
                triangleUVs.push_back(Vector2(1.0f, nx));
            }
        }
        }

        while (static_cast<int>(trails.size()) > numberOfTrails)
        {
            trails.pop_front();
            lines1.pop_front();
            lines2.pop_front();

            triangles.erase(triangles.begin(), triangles.begin() + 6);
            triangleUVs.erase(triangleUVs.begin(), triangleUVs.begin() + 6);
        }

        if (triangles.size() > 0)
        {
            triangleColorsTemporary = triangleColors;
            context.FillTriangles(static_cast<int>(triangles.size()),
                                  &triangles[0],
                                  &triangleUVs[0],
                                  &triangleColorsTemporary[0],
                                  source);
        }
    }

    void UITrail::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }

    void UITrail::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        thickness = o->thickness;
        trails = o->trails;
        triangles = o->triangles;
    }
}