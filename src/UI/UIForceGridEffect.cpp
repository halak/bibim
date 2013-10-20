#include <Bibim/Config.h>
#include <Bibim/UIForceGridEffect.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Math.h>
#include <Bibim/String.h>

namespace Bibim
{
    BBImplementsComponent(UIForceGridEffect);

    const float UIForceGridEffect::DefaultDampingValue = 0.98f;
    const float UIForceGridEffect::TargetLengthFactor = 0.95f;
    const float UIForceGridEffect::PerspectiveProjectionFactor = 2000.0f;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    UIForceGridEffect::UIForceGridEffect()
        : timeline(nullptr),
          springsTimeline(nullptr),
          pointMassTimeline(nullptr)
    {
    }

    UIForceGridEffect::UIForceGridEffect(Rect size, Vector2 spacing)
        : timeline(nullptr),
          springsTimeline(nullptr),
          pointMassTimeline(nullptr)
    {
        Initialize(size, spacing);
    }

    void UIForceGridEffect::InitializeXY(int width, int height, float spacingX, float spacingY)
    {
        Initialize(Rect(0, 0, width, height), Vector2(spacingX, spacingY));
    }

    void UIForceGridEffect::Initialize(Rect size, Vector2 spacing)
    {
        int numColumns = (int)(size.Width / spacing.X) + 1;
        int numRows = (int)(size.Height / spacing.Y) + 1;

        points.resize(numColumns);
        for (std::vector<std::vector<PointMass> >::iterator it = points.begin(); it != points.end(); it++)
            it->resize(numRows);

        // these fixed points will be used to anchor the grid to fixed positions on the screen
        std::vector<std::vector<PointMass> > fixedPoints;
        fixedPoints.resize(numColumns);
        for (std::vector<std::vector<PointMass> >::iterator it = fixedPoints.begin(); it != fixedPoints.end(); it++)
            it->resize(numRows);

        // create the point masses
        int column = 0, row = 0;
        for (float y = static_cast<float>(size.GetTop()); y <= size.GetBottom(); y += spacing.Y)
        {
            for (float x = static_cast<float>(size.GetLeft()); x <= size.GetRight(); x += spacing.X)
            {
                points[column][row] = PointMass(Vector3(x, y, 0.0f), 1.0f);
                fixedPoints[column][row] = PointMass(Vector3(x, y, 0.0f), 0.0f);
                column++;
            }
            row++;
            column = 0;
        }

        // link the point masses with springs
        for (int y = 0; y < numRows; y++)
        {
            for (int x = 0; x < numColumns; x++)
            {
                if (x == 0 || y == 0 || x == numColumns - 1 || y == numRows - 1)	// anchor the border of the grid
                    springs.push_back(Spring(fixedPoints[x][y], points[x][y], 0.1f, 0.1f));
                else if (x % 3 == 0 && y % 3 == 0)									// loosely anchor 1/9th of the point masses
                    springs.push_back(Spring(fixedPoints[x][y], points[x][y], 0.002f, 0.02f));

                const float stiffness = 0.28f;
                const float damping = 0.06f;

                if (x > 0)
                    springs.push_back(Spring(points[x - 1][y], points[x][y], stiffness, damping));
                if (y > 0)
                    springs.push_back(Spring(points[x][y - 1], points[x][y], stiffness, damping));
            }
        }

        springsTimeline = new Timeline();

        for (std::vector<Spring>::iterator it = springs.begin(); it != springs.end(); it++)
        {
            springsTimeline->Add(&(*it));
        }

        pointMassTimeline = new Timeline();

        for (std::vector<std::vector<PointMass> >::iterator it0 = points.begin(); it0 != points.end(); it0++)
        {
            for (std::vector<PointMass>::iterator it1 = it0->begin(); it1 != it0->end(); it1++)
            {
                pointMassTimeline->Add(&(*it1));
            }
        }

        updater.o = this;
        this->size = size;
        this->spacing = spacing;
    }

    UIForceGridEffect::~UIForceGridEffect()
    {
        SetTimeline(nullptr);

        if (springsTimeline)
            delete springsTimeline;

        if (pointMassTimeline)
            delete pointMassTimeline;
    }

    void UIForceGridEffect::SetTimeline(Timeline* value)
    {
        if (timeline != value)
        {
            if (timeline)
                timeline->Remove(&updater);

            timeline = value;

            if (timeline)
                timeline->Add(&updater);
        }
    }

    void UIForceGridEffect::ApplyDirectedForce2D(float forceX, float forceY, float positionX, float positionY, float radius)
    {
        ApplyDirectedForce(Vector2(forceX, forceY), Vector2(positionX, positionY), radius);
    }

    //void UIForceGridEffect::ApplyDirectedForce3D(float forceX, float forceY, float forceZ, float positionX, float positionY, float positionZ, float radius)
    //{
    //    ApplyDirectedForce(Vector3(forceX, forceY, forceZ), Vector3(positionX, positionY, positionZ), radius);
    //}

    void UIForceGridEffect::ApplyImplosiveForce2D(float force, float positionX, float positionY, float radius)
    {
        ApplyImplosiveForce(force, Vector2(positionX, positionY), radius);
    }

    void UIForceGridEffect::ApplyImplosiveForce3D(float force, float positionX, float positionY, float positionZ, float radius)
    {
        ApplyImplosiveForce(force, Vector3(positionX, positionY, positionZ), radius);
    }

    void UIForceGridEffect::ApplyExplosiveForce2D(float force, float positionX, float positionY, float radius)
    {
        ApplyExplosiveForce(force, Vector2(positionX, positionY), radius);
    }

    void UIForceGridEffect::ApplyExplosiveForce3D(float force, float positionX, float positionY, float positionZ, float radius)
    {
        ApplyExplosiveForce(force, Vector3(positionX, positionY, positionZ), radius);
    }

    void UIForceGridEffect::ApplyDirectedForce(Vector2 force, Vector2 position, float radius)
    {
        ApplyDirectedForce(Vector3(force, 0), Vector3(position, 0), radius);
    }

    void UIForceGridEffect::ApplyDirectedForce(Vector3 force, Vector3 position, float radius)
    {
        for (std::vector<std::vector<PointMass> >::iterator it0 = points.begin(); it0 != points.end(); it0++)
        {
            for (std::vector<PointMass>::iterator it1 = it0->begin(); it1 != it0->end(); it1++)
            {
                if(Vector3::GetDistanceSquared(position, it1->position) < radius * radius)
                    it1->ApplyForce(10.0f * force / (10.0f * Vector3::GetDistance(position, it1->position)));
            }
        }
    }

    void UIForceGridEffect::ApplyImplosiveForce(float force, Vector2 position, float radius)
    {
        ApplyImplosiveForce(force, Vector3(position, 0), radius);
    }

    void UIForceGridEffect::ApplyImplosiveForce(float force, Vector3 position, float radius)
    {
        for (std::vector<std::vector<PointMass> >::iterator it0 = points.begin(); it0 != points.end(); it0++)
        {
            for (std::vector<PointMass>::iterator it1 = it0->begin(); it1 != it0->end(); it1++)
            {
                float dist2 = Vector3::GetDistanceSquared(position, it1->position);

                if (dist2 < radius * radius)
                {
                    it1->ApplyForce(10.0f * force * (it1->position - position) / (100.0f + dist2));
                    it1->IncreaseDamping(0.6f);
                }
            }
        }
    }

    void UIForceGridEffect::ApplyExplosiveForce(float force, Vector2 position, float radius)
    {
        ApplyExplosiveForce(force, Vector3(position, 0), radius);
    }

    void UIForceGridEffect::ApplyExplosiveForce(float force, Vector3 position, float radius)
    {
        for (std::vector<std::vector<PointMass> >::iterator it0 = points.begin(); it0 != points.end(); it0++)
        {
            for (std::vector<PointMass>::iterator it1 = it0->begin(); it1 != it0->end(); it1++)
            {
                float dist2 = Vector3::GetDistanceSquared(position, it1->position);

                if (dist2 < radius * radius)
                {
                    it1->ApplyForce(100.0f * force * (it1->position - position) / (10000.0f + dist2));
                    it1->IncreaseDamping(0.6f);
                }
            }
        }
    }

    Vector2 UIForceGridEffect::TranslateCoordinate(Vector3 pos, Point2 screenSize, Vector2* p)
    {
        static const int S0 = 0;
        static const int S1 = 1;
        static const int E0 = 2;
        static const int E1 = 3;

        Vector2 pV = PerspectiveVector(pos, screenSize);
        float xRate = (pV.X - size.GetLeft()) / size.Width;
        float yRate = (pV.Y - size.GetTop()) / size.Height;
        Vector2 topPoint = Math::Lerp(p[S0], p[E0], xRate);
        Vector2 bottomPoint = Math::Lerp(p[S1], p[E1], xRate);
        return Math::Lerp(topPoint, bottomPoint, yRate);
    }

    void UIForceGridEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color color)
    {
        static const int S0 = 0;
        static const int S1 = 1;
        static const int E0 = 2;
        static const int E1 = 3;

        if(points.size() == 0)
        {
            Base::DrawQuad(renderer, p, color);
            return;
        }

        int colCount = points.size();
        int rowCount = points[0].size();

        Point2 screenSize = renderer->GetGraphicsDevice()->GetScreenSize();

        Vector2 np[4];

        for (int y = 1; y < rowCount; y++)
        {
            np[E0] = TranslateCoordinate(points[0][y - 1].position, screenSize, p);
            np[E1] = TranslateCoordinate(points[0][y].position, screenSize, p);

            for (int x = 1; x < colCount; x++)
            {
                np[S0] = np[E0];
                np[S1] = np[E1];
                np[E0] = TranslateCoordinate(points[x][y - 1].position, screenSize, p);
                np[E1] = TranslateCoordinate(points[x][y].position, screenSize, p);

                Base::DrawQuad(renderer, np, color);
            }
        }
    }

    void UIForceGridEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color color, Vector2* uv,  Texture2D* texture)
    {
        static const int S0 = 0;
        static const int S1 = 1;
        static const int E0 = 2;
        static const int E1 = 3;

        if(points.size() == 0)
        {
            Base::DrawQuad(renderer, p, color, uv, texture);
            return;
        }

        int colCount = points.size();
        int rowCount = points[0].size();

        Point2 screenSize = renderer->GetGraphicsDevice()->GetScreenSize();

        Vector2 np[4];
        Vector2 nuv[4];

        Vector2 basePointUV[4];

        basePointUV[S1] = uv[S0];
        basePointUV[E1] = uv[E0];

        for (int y = 1; y < rowCount; y++)
        {
            basePointUV[S0] = basePointUV[S1];
            basePointUV[E0] = basePointUV[E1];
            basePointUV[S1] = Math::Lerp(uv[S0], uv[S1], static_cast<float>(y) / static_cast<float>(rowCount));
            basePointUV[E1] = Math::Lerp(uv[E0], uv[E1], static_cast<float>(y) / static_cast<float>(rowCount));

            np[E0] = TranslateCoordinate(points[0][y - 1].position, screenSize, p);
            np[E1] = TranslateCoordinate(points[0][y].position, screenSize, p);
            nuv[E0] = basePointUV[S0];
            nuv[E1] = basePointUV[S1];

            for (int x = 1; x < colCount; x++)
            {
                np[S0] = np[E0];
                np[S1] = np[E1];
                np[E0] = TranslateCoordinate(points[x][y - 1].position, screenSize, p);
                np[E1] = TranslateCoordinate(points[x][y].position, screenSize, p);

                nuv[S0] = nuv[E0];
                nuv[S1] = nuv[E1];
                nuv[E0] = Math::Lerp(basePointUV[S0], basePointUV[E0], static_cast<float>(x) / static_cast<float>(colCount));
                nuv[E1] = Math::Lerp(basePointUV[S1], basePointUV[E1], static_cast<float>(x) / static_cast<float>(colCount));

                Base::DrawQuad(renderer, np, color, nuv, texture);
            }
        }
    }

    void UIForceGridEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color color, Vector2* uv1, Texture2D* texture1, Vector2* uv2, Texture2D* texture2)
    {
        static const int S0 = 0;
        static const int S1 = 1;
        static const int E0 = 2;
        static const int E1 = 3;

        if(points.size() == 0)
        {
            Base::DrawQuad(renderer, p, color, uv1, texture1, uv2, texture2);
            return;
        }

        int colCount = points.size();
        int rowCount = points[0].size();

        Point2 screenSize = renderer->GetGraphicsDevice()->GetScreenSize();

        Vector2 np[4];
        Vector2 nuv1[4];
        Vector2 nuv2[4];

        Vector2 basePointUV1[4];
        Vector2 basePointUV2[4];

        basePointUV1[S1] = uv1[S0];
        basePointUV1[E1] = uv1[E0];
        basePointUV2[S1] = uv2[S0];
        basePointUV2[E1] = uv2[E0];

        for (int y = 1; y < rowCount; y++)
        {
            basePointUV1[S0] = basePointUV1[S1];
            basePointUV1[E0] = basePointUV1[E1];
            basePointUV1[S1] = Math::Lerp(uv1[S0], uv1[S1], static_cast<float>(y) / static_cast<float>(rowCount));
            basePointUV1[E1] = Math::Lerp(uv1[E0], uv1[E1], static_cast<float>(y) / static_cast<float>(rowCount));

            basePointUV2[S0] = basePointUV2[S1];
            basePointUV2[E0] = basePointUV2[E1];
            basePointUV2[S1] = Math::Lerp(uv2[S0], uv2[S1], static_cast<float>(y) / static_cast<float>(rowCount));
            basePointUV2[E1] = Math::Lerp(uv2[E0], uv2[E1], static_cast<float>(y) / static_cast<float>(rowCount));

            np[E0] = TranslateCoordinate(points[0][y - 1].position, screenSize, p);
            np[E1] = TranslateCoordinate(points[0][y].position, screenSize, p);
            nuv1[E0] = basePointUV1[S0];
            nuv1[E1] = basePointUV1[S1];
            nuv2[E0] = basePointUV2[S0];
            nuv2[E1] = basePointUV2[S1];

            for (int x = 1; x < colCount; x++)
            {
                np[S0] = np[E0];
                np[S1] = np[E1];
                np[E0] = TranslateCoordinate(points[x][y - 1].position, screenSize, p);
                np[E1] = TranslateCoordinate(points[x][y].position, screenSize, p);

                nuv1[S0] = nuv1[E0];
                nuv1[S1] = nuv1[E1];
                nuv1[E0] = Math::Lerp(basePointUV1[S0], basePointUV1[E0], static_cast<float>(x) / static_cast<float>(colCount));
                nuv1[E1] = Math::Lerp(basePointUV1[S1], basePointUV1[E1], static_cast<float>(x) / static_cast<float>(colCount));

                nuv2[S0] = nuv2[E0];
                nuv2[S1] = nuv2[E1];
                nuv2[E0] = Math::Lerp(basePointUV2[S0], basePointUV2[E0], static_cast<float>(x) / static_cast<float>(colCount));
                nuv2[E1] = Math::Lerp(basePointUV2[S1], basePointUV2[E1], static_cast<float>(x) / static_cast<float>(colCount));

                Base::DrawQuad(renderer, np, color, nuv1, texture1, nuv2, texture2);
            }
        }
    }

    void UIForceGridEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color color, RectF clippingRect, Texture2D* texture)
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

    void UIForceGridEffect::DrawQuad(UIRenderer* renderer, Vector2* p, Color color, RectF clippingRect, Texture2D* texture1, Vector2* uv2, Texture2D* texture2)
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

    void UIForceGridEffect::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        Initialize(reader.ReadRect(), reader.ReadVector2());
    }

    void UIForceGridEffect::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        Initialize(o->size, o->spacing);
    }
    
    void UIForceGridEffect::OnStep(float dt, int timestamp)
    {
        springsTimeline->Update(dt, timestamp);
        pointMassTimeline->Update(dt, timestamp);
    }

    Vector2 UIForceGridEffect::PerspectiveVector(Vector3 v, Point2 screenSize)
    {
        // do a perspective projection
        float factor = (v.Z + PerspectiveProjectionFactor) / PerspectiveProjectionFactor;
        return (Vector2(v.X, v.Y) - Vector2(screenSize.X, screenSize.Y) / 2.0f) * factor + Vector2(screenSize.X, screenSize.Y) / 2.0f;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIForceGridEffect::PointMass::PointMass()
        : position(Vector3()),
          velocity(Vector3()),
          inverseMass(0.0f),
          acceleration(Vector3()),
          damping(DefaultDampingValue)
    {
    }

    UIForceGridEffect::PointMass::PointMass(Vector3 position, float invMass)
        : position(position),
          velocity(Vector3()),
          inverseMass(invMass),
          acceleration(Vector3()),
          damping(DefaultDampingValue)
    {
    }

    UIForceGridEffect::PointMass::~PointMass()
    {
    }

    void UIForceGridEffect::PointMass::Update(float dt, int /*timestamp*/)
    {
        velocity += acceleration;
        //position += velocity * dt;
        position += velocity;
        acceleration = Vector3::Zero;

        if (velocity.GetLengthSquared() < 0.001f * 0.001f)
            velocity = Vector3::Zero;

        velocity *= damping;
        damping = DefaultDampingValue;
    }

    void UIForceGridEffect::PointMass::ApplyForce(Vector3 force)
    {
        acceleration += force * inverseMass;
    }

    void UIForceGridEffect::PointMass::IncreaseDamping(float factor)
    {
        damping *= factor;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIForceGridEffect::Spring::Spring(PointMass end1, PointMass end2, float stiffness, float damping)
        : end1(end1),
          end2(end2),
          stiffness(stiffness),
          damping(damping)
    {
        targetLength = Vector3::GetDistance(end1.position, end2.position) * TargetLengthFactor;
    }

    UIForceGridEffect::Spring::~Spring()
    {
    }

    void UIForceGridEffect::Spring::Update(float dt, int /*timestamp*/)
    {
        Vector3 x = end1.position - end2.position;

        float length = x.GetLength();
        // these springs can only pull, not push
        if (length <= targetLength)
            return;

        x = (x / length) * (length - targetLength);
        Vector3 dv = end2.velocity - end1.velocity;
        Vector3 force = stiffness * x - dv * damping;

        end1.ApplyForce(-force);
        end2.ApplyForce(force);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIForceGridEffect::Updater::Updater()
        : o(nullptr)
    {
    }

    UIForceGridEffect::Updater::~Updater()
    {
    }

    void UIForceGridEffect::Updater::Update(float dt, int timestamp)
    {
        o->OnStep(dt, timestamp);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
}