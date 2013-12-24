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
            const Vector2 normal = Vector2(-direction.Y, direction.X);
            
            Vector2 oldDirection = direction;
            if (trails.size() >= 3)
            {
                oldDirection = previous - trails[trails.size() - 3];
                oldDirection.Normalize();
            }

            const float halfThickness = GetThickness() * 0.5f;

            if (trails.size() == 2)
            {
                lines1.push_back(previous + normal * halfThickness);
                lines2.push_back(previous - normal * halfThickness);
            }

            const float dot = normal.Dot(oldDirection);
            if (Math::Equals(dot, 0.0f) == false)
            {
                const Vector2 oldNormal = Vector2(-oldDirection.Y, oldDirection.X);

                Vector2 halfNormal = Math::Lerp(oldNormal, normal, 0.5f);
                halfNormal.Normalize();

                if (dot < 0.0f)
                {
                    lines1[lines1.size() - 1] = previous + halfNormal * halfThickness;
                    lines2[lines2.size() - 1] = previous - halfNormal * halfThickness;
                }
                else if (dot > 0.0f)
                {
                    lines1[lines1.size() - 1] = previous + halfNormal * halfThickness;
                    lines2[lines2.size() - 1] = previous - halfNormal * halfThickness;
                }

                triangles[triangles.size() - 1] = lines2[lines2.size() - 1];
                triangles[triangles.size() - 4] = lines1[lines1.size() - 1];
                triangles[triangles.size() - 5] = lines2[lines2.size() - 1];
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

        while (trails.size() > numberOfTrails)
        {
            trails.pop_front();
            lines1.pop_front();
            lines2.pop_front();

            triangles.erase(triangles.begin(), triangles.begin() + 6);
            triangleUVs.erase(triangleUVs.begin(), triangleUVs.begin() + 6);
        }

        if (triangles.size() > 0)
        {
            context.FillTriangles(static_cast<int>(triangles.size()),
                                  &triangles[0],
                                  &triangleUVs[0],
                                  &triangleColors[0],
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