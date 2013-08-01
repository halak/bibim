#include <Bibim/Config.h>
#include <Bibim/UISpark.h>
#include <Bibim/Assert.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Image.h>
#include <Bibim/Math.h>
#include <Bibim/Numerics.h>
#include <Bibim/Timeline.h>
#include <Bibim/UIDrawingContext.h>
#include <Bibim/UIPickingContext.h>
#include <Bibim/UIWindow.h>
#pragma warning(push)
#pragma warning(disable : 4100)
#include <SPK.h>
#pragma warning(pop)
using namespace SPK;

namespace Bibim
{
    class SparkRenderer : public SPK::Renderer
    {
        public:
            virtual ~SparkRenderer() { }

            // 원래 SPK::Renderer의 순수 가상 함수는 모두 무시합니다.
            virtual void setBlending(BlendingMode /*blendMode*/) { }
            virtual void render(const Group& /*group*/) { }

            virtual void Draw(UIDrawingContext& context, const Group& group, const std::vector<ImagePtr>& imagePalette) = 0;
    };

    class DirectionalRenderer : public SparkRenderer
    {
        SPK_IMPLEMENT_REGISTERABLE(DirectionalRenderer)
        public:
            DirectionalRenderer() { }
            virtual ~DirectionalRenderer() { }

            static DirectionalRenderer* create()
            {
                DirectionalRenderer* obj = new DirectionalRenderer();
                registerObject(obj);
                return obj;
            }

            virtual void Draw(UIDrawingContext& context, const Group& group, const std::vector<ImagePtr>& imagePalette);
    };

    class RandomAngleAxisRenderer : public SparkRenderer
    {
        SPK_IMPLEMENT_REGISTERABLE(RandomAngleAxisRenderer)
        public:
            static const int NumberOfAxes = 32;

        public:
            RandomAngleAxisRenderer();
            virtual ~RandomAngleAxisRenderer() { }

            static RandomAngleAxisRenderer* create()
            {
                RandomAngleAxisRenderer* obj = new RandomAngleAxisRenderer();
                registerObject(obj);
                return obj;
            }

            virtual void Draw(UIDrawingContext& context, const Group& group, const std::vector<ImagePtr>& imagePalette);

        private:
            static Vector3 Axes[NumberOfAxes];
            static bool AxesReady;
    };

    Vector3 RandomAngleAxisRenderer::Axes[NumberOfAxes];
    bool RandomAngleAxisRenderer::AxesReady = false;

    class SingleAngleAxisRenderer : public SparkRenderer
    {
        SPK_IMPLEMENT_REGISTERABLE(SingleAngleAxisRenderer)
        public:
            SingleAngleAxisRenderer(Vector3 axis);
            virtual ~SingleAngleAxisRenderer() { }

            static SingleAngleAxisRenderer* create(Vector3 axis)
            {
                SingleAngleAxisRenderer* obj = new SingleAngleAxisRenderer(axis);
                registerObject(obj);
                return obj;
            }

            virtual void Draw(UIDrawingContext& context, const Group& group, const std::vector<ImagePtr>& imagePalette);

        private:
            Vector3 axis;
    };

    class MultipleAngleAxisRenderer : public SparkRenderer
    {
        SPK_IMPLEMENT_REGISTERABLE(MultipleAngleAxisRenderer)
        public:
            MultipleAngleAxisRenderer(std::vector<Vector3>& axes);
            virtual ~MultipleAngleAxisRenderer() { }

            static MultipleAngleAxisRenderer* create(std::vector<Vector3>& axes)
            {
                MultipleAngleAxisRenderer* obj = new MultipleAngleAxisRenderer(axes);
                registerObject(obj);
                return obj;
            }

            virtual void Draw(UIDrawingContext& context, const Group& group, const std::vector<ImagePtr>& imagePalette);

        private:
            std::vector<Vector3> axes;
    };

#   define BEGIN_DRAW_PARTICLE(group, particle) \
        const int count = (group).getNbParticles(); \
        for (int i = count - 1; i >= 0; i--) \
        { \
            const Particle& particle = (group).getParticle(i);

#   define END_DRAW_PARTICLE() }

#   define PARTICLE_POSITION(particle)  Vector2(particle.position().x, particle.position().y)
#   define PARTICLE_IMAGE(particle)     imagePalette.at(static_cast<int>(particle.getParamCurrentValue(PARAM_TEXTURE_INDEX) + 0.5f))
#   define PARTICLE_COLOR(particle)     Color(Vector4(particle.getR(), \
                                                      particle.getG(), \
                                                      particle.getB(), \
                                                      particle.getParamCurrentValue(PARAM_ALPHA)))
#   define PARTICLE_ANGLE(particle)     particle.getParamCurrentValue(PARAM_ANGLE)
#   define PARTICLE_SIZE(particle)      particle.getParamCurrentValue(PARAM_SIZE)

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    BBImplementsComponent(UISpark);

    UISpark::UISpark()
    {
        __Construct__();
    }

    UISpark::UISpark(lua_tinker::table t)
    {
        __Construct__(t);
    }

    UISpark::~UISpark()
    {
        SetTimeline(nullptr);
        SPKFactory::getInstance().destroy(particleSystem);
    }

    void UISpark::SetTimeline(Timeline* value)
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

    void UISpark::SetAutoRemove(bool value)
    {
        autoRemove = value;
    }

    Vector2 UISpark::GetContentSize()
    {
        return contentSize;
    }

    void UISpark::OnStep(float dt, int /*timestamp*/)
    {
        if (particleSystem == nullptr || isUpdateable == false)
            return;

        const bool enabledAABBComputing = (GetWidthMode()  == ContentSize) || 
                                          (GetHeightMode() == ContentSize);

        particleSystem->enableAABBComputing(enabledAABBComputing);

        const bool isAlive = particleSystem->update(dt);

        if (enabledAABBComputing)
        {
            const Vector3D max = particleSystem->getAABBMax();
            const Vector3D min = particleSystem->getAABBMin();
            contentSize.X = max.x - min.x;
            contentSize.Y = max.y - min.y;
        }

        if (isAlive == false && autoRemove)
        {
            UIPanel* parent = GetParent();
            if (parent && parent->IsWindow())
                static_cast<UIWindow*>(parent)->RemoveChild(this);
        }
    }

    void UISpark::OnDraw(UIDrawingContext& context)
    {
        UIVisual::OnDraw(context);

        if (particleSystem == nullptr)
            return;

        const RectF bounds = context.GetCurrentBounds();
        particleSystem->setTransformPosition(Vector3D(bounds.GetCenter(), bounds.GetMiddle()));
        particleSystem->updateTransform();
        isUpdateable = true;

        typedef std::vector<Group*> Groups;
        const Groups& groups = particleSystem->getGroups();
        for (Groups::const_iterator it = groups.begin(); it != groups.end(); it++)
        {
            const Group& g = *(*it);
            if (g.getRenderer() == nullptr)
            {
                BEGIN_DRAW_PARTICLE(g, p);
                {
                    context.DrawUnclipped(PARTICLE_POSITION(p),
                                          PARTICLE_ANGLE(p),
                                          PARTICLE_SIZE(p),
                                          PARTICLE_IMAGE(p),
                                          PARTICLE_COLOR(p));
                }
                END_DRAW_PARTICLE();
            }
            else
                static_cast<SparkRenderer*>(g.getRenderer())->Draw(context, g, imagePalette);
        }
    }

    void UISpark::__Construct__()
    {
        particleSystem = nullptr;
        timeline = nullptr;
        contentSize = Vector2::Zero;
        updater.o = this;
        isUpdateable = false;
        autoRemove = false;

        SetSize(1.0f, 1.0f);
        SetSizeMode(ContentSize, ContentSize);
    }

    void UISpark::__Construct__(lua_tinker::table t)
    {
        __Construct__();

        particleSystem = System::create();

        const int count = t.len();
        if (count > 0)
        {
            for (int i = 1; i <= count; i++)
            {
                if (Group* group = CreateParticleGroup(t.get<lua_tinker::table>(i)))
                    particleSystem->addGroup(group);
            }
        }
        else
        {
            if (Group* group = CreateParticleGroup(t))
                particleSystem->addGroup(group);
        }

        if (t.type("Images") == LUA_TTABLE)
        {
            lua_tinker::table images = t.get<lua_tinker::table>("Images");
            const int numberOfImages = images.len();
            for (int i = 1; i <= numberOfImages; i++)
                imagePalette.push_back(images.get<Image*>(i));
        }
    }

    Group* UISpark::CreateParticleGroup(lua_tinker::table t)
    {
        struct ModelFlags
        {
            int Enable;
            int Mutable;
            int Random;
            int Interpolated;

            ModelFlags()
                : Enable(FLAG_NONE),
                  Mutable(FLAG_NONE),
                  Random(FLAG_NONE),
                  Interpolated(FLAG_NONE)
            {
            }

            void Set(lua_tinker::table& t, const char* key, ModelParamFlag flags)
            {
                switch (t.type(key))
                {
                    case LUA_TNUMBER:
                        Enable |= flags;
                        break;
                    case LUA_TSTRING:
                        {
                            const char* value = t.get<const char*>(key);
                            if (String::CharsFind(value, '~') != -1)
                                Random |= flags;
                            else
                            {
                                static const String Direction = "Direction";
                                if (Direction.EqualsIgnoreCase(value) == false)
                                    Enable |= flags;
                            }
                        }
                        break;
                    case LUA_TTABLE:
                        {
                            lua_tinker::table value = t.get<lua_tinker::table>(key);
                            if (value.len() == 2)
                            {
                                Mutable |= flags;

                                // 테이블의 첫번째, 두번째 값중 하나라도 "1~2"와 같은 범위 값이면,
                                // 전체를 random 값으로 설정합니다.
                                if ((value.type(1) == LUA_TSTRING && String::CharsFind(value.get<const char*>(1), '~') != -1) ||
                                    (value.type(2) == LUA_TSTRING && String::CharsFind(value.get<const char*>(2), '~') != -1))
                                    Random |= flags;
                            }
                            else
                                Interpolated |= flags;
                        }
                        break;
                }
            }
        };

        struct SetModelParams
        {
            static void Do(Model* model, lua_tinker::table& t, const char* key, ModelParam param)
            {
                if (model->isInterpolated(param))
                {
                    lua_tinker::table value = t.get<lua_tinker::table>(key);

                    const char* xAxis = value.get<const char*>("XAxis");
                    InterpolationType interpolationType = INTERPOLATOR_LIFETIME;
                    ModelParam interpolationParam = PARAM_SIZE;
                    if (xAxis)
                    {
                        static const String Lifetime = "Lifetime";
                        static const String Age = "Age";
                        static const String SpeedSq = "SpeedSq";

                        const int xAxisLength = String::CharsLength(xAxis);
                        if (Lifetime.EqualsIgnoreCase(xAxis, xAxisLength))
                            interpolationType = INTERPOLATOR_LIFETIME;
                        else if (Age.EqualsIgnoreCase(xAxis, xAxisLength))
                            interpolationType = INTERPOLATOR_AGE;
                        else if (SpeedSq.EqualsIgnoreCase(xAxis, xAxisLength))
                            interpolationType = INTERPOLATOR_VELOCITY;
                        else
                        {
                            static const String Size = "Size";
                            static const String Mass = "Mass";
                            static const String Angle = "Angle";
                            static const String Opacity = "Opacity";
                            static const String Red = "Red";
                            static const String Green = "Green";
                            static const String Blue = "Blue";
                            static const String Image = "Image";

                            interpolationType = INTERPOLATOR_PARAM;
                            if (Size.EqualsIgnoreCase(xAxis, xAxisLength))
                                interpolationParam = PARAM_SIZE;
                            else if (Mass.EqualsIgnoreCase(xAxis, xAxisLength))
                                interpolationParam = PARAM_MASS;
                            else if (Angle.EqualsIgnoreCase(xAxis, xAxisLength))
                                interpolationParam = PARAM_ANGLE;
                            else if (Opacity.EqualsIgnoreCase(xAxis, xAxisLength))
                                interpolationParam = PARAM_ALPHA;
                            else if (Red.EqualsIgnoreCase(xAxis, xAxisLength))
                                interpolationParam = PARAM_RED;
                            else if (Green.EqualsIgnoreCase(xAxis, xAxisLength))
                                interpolationParam = PARAM_GREEN;
                            else if (Blue.EqualsIgnoreCase(xAxis, xAxisLength))
                                interpolationParam = PARAM_BLUE;
                            else if (Image.EqualsIgnoreCase(xAxis, xAxisLength))
                                interpolationParam = PARAM_TEXTURE_INDEX;
                        }
                    }

                    Interpolator* interpolator = model->getInterpolator(param);
                    interpolator->setType(interpolationType, interpolationParam);

                    if (value.has("Offset"))
                        interpolator->setScaleXVariation(value.get<float>("Offset"));

                    if (value.has("Scale"))
                        interpolator->setOffsetXVariation(value.get<float>("Scale"));

                    if (value.type("SineCurve") == LUA_TTABLE)
                    {
                        lua_tinker::table sineCurve = value.get<lua_tinker::table>("SineCurve");
                        MinMax amplitude = MinMax(sineCurve, 2);
                        if (amplitude.IsValid)
                        {
                            interpolator->generateSinCurve(sineCurve.get<float>(1),
                                                           amplitude.Min, amplitude.Max,
                                                           sineCurve.get<float>(3),
                                                           sineCurve.get<float>(4),
                                                           sineCurve.get<float>(5),
                                                           Math::Max(sineCurve.get<int>(6), 1),
                                                           Math::Max(sineCurve.get<int>(7), 4));
                        }
                    }
                    else if (value.type("PolyCurve") == LUA_TTABLE)
                    {
                        lua_tinker::table polyCurve = value.get<lua_tinker::table>("PolyCurve");
                        MinMax xRange = MinMax(polyCurve, 5);
                        if (xRange.IsValid)
                        {
                            interpolator->generatePolyCurve(polyCurve.get<float>(1),
                                                            polyCurve.get<float>(2),
                                                            polyCurve.get<float>(3),
                                                            polyCurve.get<float>(4),
                                                            xRange.Min, xRange.Max,
                                                            Math::Max(polyCurve.get<int>(6), 4));
                        }
                    }
                    else
                    {
                        lua_tinker::table::enumerator en = value.enumerate();
                        while (en.next())
                        {
                            if (en.key_type() != LUA_TNUMBER)
                                continue;

                            if (en.value_type() == LUA_TNUMBER)
                                interpolator->addEntry(en.key<float>(), en.value<float>());
                            else if (en.value_type() == LUA_TSTRING)
                            {
                                float min = 0.0f;
                                float max = 0.0f;
                                if (MinMax::TryParse(en.value<const char*>(), min, max))
                                    interpolator->addEntry(en.key<float>(), min, max);
                            }
                        }
                    }

                    return;
                }

                const bool isMutable = model->isMutable(param) != 0;
                const bool isRandom  = model->isRandom(param) != 0;
                if (isMutable && isRandom)
                {
                    lua_tinker::table value = t.get<lua_tinker::table>(key);
                    float birthMin = 0.0f;
                    float birthMax = 0.0f;
                    float deathMin = 0.0f;
                    float deathMax = 0.0f;

                    if (value.type(1) == LUA_TSTRING)
                        MinMax::TryParse(value.get<const char*>(1), birthMin, birthMax);
                    else
                    {
                        birthMin = value.get<float>(1);
                        birthMax = birthMin;
                    }

                    if (value.type(2) == LUA_TSTRING)
                        MinMax::TryParse(value.get<const char*>(2), deathMin, deathMax);
                    else
                    {
                        deathMin = value.get<float>(2);
                        deathMax = deathMin;
                    }

                    model->setParam(param, birthMin, birthMax, deathMin, deathMax);
                    return;
                }
                else if (isMutable)
                {
                    lua_tinker::table value = t.get<lua_tinker::table>(key);
                    const float birth = value.get<float>(1);
                    const float death = value.get<float>(2);
                    model->setParam(param, birth, death);
                    return;
                }
                else if (isRandom)
                {
                    float min, max;
                    if (MinMax::TryParse(t.get<const char*>(key), min, max))
                        model->setParam(param, min, max);
                    return;
                }

                if (model->isEnabled(param))
                {
                    switch (t.type(key))
                    {
                        case LUA_TNUMBER:
                        case LUA_TSTRING:
                            model->setParam(param, t.get<float>(key));
                            break;
                    }

                    return;
                }
            }
        };

        ModelFlags modelFlags;
        modelFlags.Set(t, "Red", FLAG_RED);
        modelFlags.Set(t, "Green", FLAG_GREEN);
        modelFlags.Set(t, "Blue", FLAG_BLUE);
        modelFlags.Set(t, "Opacity", FLAG_ALPHA);
        modelFlags.Set(t, "Size", FLAG_SIZE);
        modelFlags.Set(t, "Mass", FLAG_MASS);
        modelFlags.Set(t, "Angle", FLAG_ANGLE);
        modelFlags.Set(t, "AngularSpeed", FLAG_ROTATION_SPEED);
        modelFlags.Set(t, "Image", FLAG_TEXTURE_INDEX);

        int angleAxisCount = 0;
        bool isRandomAngleAxis = false;
        switch (t.type("AngleAxis"))
        {
            case LUA_TSTRING:
                if (const char* anleAxis = t.get<const char*>("AngleAxis"))
                {
                    static const String Random = "Random";
                    if (Random.EqualsIgnoreCase(anleAxis))
                    {
                        angleAxisCount = RandomAngleAxisRenderer::NumberOfAxes;
                        isRandomAngleAxis = true;
                        modelFlags.Enable |= FLAG_CUSTOM_0;
                        modelFlags.Random |= FLAG_CUSTOM_0;
                    }
                }
                break;
            case LUA_TTABLE:
                {
                    lua_tinker::table angleAxis = t.get<lua_tinker::table>("AngleAxis");
                    if (angleAxis.type(1) == LUA_TNUMBER)
                        angleAxisCount = 1;
                    else
                    {
                        angleAxisCount = angleAxis.len();
                        modelFlags.Enable |= FLAG_CUSTOM_0;
                        modelFlags.Random |= FLAG_CUSTOM_0;
                    }

                    isRandomAngleAxis = false;
                }
                break;
        }

        Model* model = Model::create(modelFlags.Enable | modelFlags.Mutable | modelFlags.Random | modelFlags.Interpolated,
                                     modelFlags.Mutable,
                                     modelFlags.Random,
                                     modelFlags.Interpolated);
        SetModelParams::Do(model, t, "Red", PARAM_RED);
        SetModelParams::Do(model, t, "Green", PARAM_GREEN);
        SetModelParams::Do(model, t, "Blue", PARAM_BLUE);
        SetModelParams::Do(model, t, "Opacity", PARAM_ALPHA);
        SetModelParams::Do(model, t, "Size", PARAM_SIZE);
        SetModelParams::Do(model, t, "Mass", PARAM_MASS);
        SetModelParams::Do(model, t, "Angle", PARAM_ANGLE);
        SetModelParams::Do(model, t, "AngularSpeed", PARAM_ROTATION_SPEED);
        SetModelParams::Do(model, t, "Image", PARAM_TEXTURE_INDEX);

        if (angleAxisCount > 1)
            model->setParam(PARAM_CUSTOM_0, 0, static_cast<float>(angleAxisCount) - 0.01f);

        MinMax lifetime(t, "Lifetime");
        if (lifetime.IsValid)
            model->setLifeTime(lifetime.Min, lifetime.Max);

        int capacity = Pool<Particle>::DEFAULT_CAPACITY;
        if (t.has("Capacity"))
            capacity = t.get<int>("Capacity");

        Group* group = Group::create(model, capacity);

        if (t.type("Emitters") == LUA_TTABLE)
        {
            lua_tinker::table emitters = t.get<lua_tinker::table>("Emitters");
            const int numberOfEmitters = emitters.len();
            for (int i = 1; i <= numberOfEmitters; i++)
            {
                int initialParticles = 0;
                if (Emitter* emitter = CreateParticleEmitter(emitters.get<lua_tinker::table>(i), initialParticles))
                {
                    group->addEmitter(emitter);

                    if (initialParticles > 0)
                        group->addParticles(initialParticles, emitter);
                }
            }
        }

        bool rotatorModifierAdded = false;
        if (t.type("Modifiers") == LUA_TTABLE)
        {
            static const std::string RotatorName = "Rotator";
            lua_tinker::table modifiers = t.get<lua_tinker::table>("Modifiers");
            const int numberOfModifiers = modifiers.len();
            for (int i = 1; i <= numberOfModifiers; i++)
            {
                if (Modifier* modifier = CreateParticleModifier(modifiers.get<lua_tinker::table>(i)))
                {
                    group->addModifier(modifier);

                    if (modifier->getClassName() == RotatorName)
                        rotatorModifierAdded = true;
                }
            }
        }

        if (rotatorModifierAdded == false && model->isEnabled(PARAM_ROTATION_SPEED))
            group->addModifier(Rotator::create());

        MinMax gravity(t, "Gravity");
        if (gravity.IsValid)
            group->setGravity(Vector3D(gravity.Min, gravity.Max, 0.0f));

        if (t.has("Friction"))
            group->setFriction(t.get<float>("Friction"));

        if (angleAxisCount == 0)
        {
            if (const char* angle = t.get<const char*>("Angle"))
            {
                static const String Direction = "Direction";
                if (Direction.EqualsIgnoreCase(angle))
                    group->setRenderer(DirectionalRenderer::create());
            }
        }
        else if (angleAxisCount > 0)
        {
            if (isRandomAngleAxis)
                group->setRenderer(RandomAngleAxisRenderer::create());
            else
            {
                BBAssertDebug(t.type("AngleAxis") == LUA_TTABLE);

                lua_tinker::table angleAxis = t.get<lua_tinker::table>("AngleAxis");
                if (angleAxisCount == 1)
                {
                    Vector3 axis = Vector3(angleAxis.get<float>(1),
                                           angleAxis.get<float>(2),
                                           angleAxis.get<float>(3));
                    if (axis != Vector3::Zero)
                    {
                        axis.Normalize();
                        group->setRenderer(SingleAngleAxisRenderer::create(axis));
                    }
                }
                else
                {
                    const int count = angleAxis.len();
                    std::vector<Vector3> axes;
                    axes.reserve(count);
                    for (int i = 1; i <= count; i++)
                    {
                        if (angleAxis.type(i) != LUA_TTABLE)
                            continue;

                        lua_tinker::table item = angleAxis.get<lua_tinker::table>(i);
                        Vector3 axis = Vector3(item.get<float>(1),
                                               item.get<float>(2),
                                               item.get<float>(3));
                        if (axis != Vector3::Zero)
                        {
                            axis.Normalize();
                            axes.push_back(axis);
                        }
                    }

                    group->setRenderer(MultipleAngleAxisRenderer::create(axes));
                }
            }
        }

        return group;
    }

    Emitter* UISpark::CreateParticleEmitter(lua_tinker::table t, int& outInitialParticles)
    {
        Emitter* emitter = nullptr;

        switch (t.type("Direction"))
        {
            case LUA_TSTRING:
                {
                    static const String Normal = "NORMAL";
                    static const String InvertedNormal = "INVNORMAL";
                    static const String No = "NO";
                    static const String Random = "RANDOM";
                    const char* direction = t.get<const char*>("Direction");
                    if (Normal.EqualsIgnoreCase(direction) ||
                        InvertedNormal.EqualsIgnoreCase(direction))
                    {
                        const bool invertedNormal = InvertedNormal.EqualsIgnoreCase(direction);

                        if (t.type("NormalZone") == LUA_TTABLE)
                        {
                            Zone* normalZone = CreateParticleZone(t.get<lua_tinker::table>("NormalZone"));
                            emitter = NormalEmitter::create(normalZone, invertedNormal);
                        }
                        else
                            emitter = NormalEmitter::create(nullptr, invertedNormal);
                    }
                    else if (No.EqualsIgnoreCase(direction))
                        emitter = StaticEmitter::create();
                    else if (Random.EqualsIgnoreCase(direction))
                        emitter = RandomEmitter::create();
                }
                break;
            case LUA_TTABLE:
                {
                    lua_tinker::table dir = t.get<lua_tinker::table>("Direction");
                    
                    const Vector3D direction = Vector3D(dir.get<float>(1),
                                                        dir.get<float>(2));

                    MinMax angles(t, "Angles");
                    if (angles.IsValid)
                        emitter = SphericEmitter::create(direction, angles.Min, angles.Max);
                    else
                        emitter = StraightEmitter::create(direction);
                }
                break;
        }

        if (emitter == nullptr)
            emitter = RandomEmitter::create();

        if (t.has("Tank"))
            emitter->setTank(Math::Max(t.get<int>("Tank"), 1));
        else
            emitter->setTank(-1);

        if (t.has("Flow"))
            emitter->setFlow(Math::Max(t.get<float>("Flow"), 0.0f));

        if (t.type("Zone") == LUA_TTABLE)
            emitter->setZone(CreateParticleZone(t.get<lua_tinker::table>("Zone")));

        MinMax force(t, "Force");
        if (force.IsValid)
            emitter->setForce(force.Min, force.Max);

        outInitialParticles = t.get<int>("InitialParticles");

        return emitter;
    }

    Modifier* UISpark::CreateParticleModifier(lua_tinker::table t)
    {
        Modifier* modifier = nullptr;

        if (t.type("Force") == LUA_TTABLE)
        {
            lua_tinker::table force = t.get<lua_tinker::table>("Force");

            const float x = force.get<float>(1);
            const float y = force.get<float>(2);

            if (const char* factor = force.get<const char*>("Factor"))
            {
                static const String Size = "Size**";
                static const String Mass = "Mass**";
                static const String Angle = "Angle**";
                static const String Image = "Image**";

                ModelParam forceFactorParam = PARAM_SIZE;
                if (Size.StartsWith(factor))
                    forceFactorParam = PARAM_SIZE;
                else if (Mass.StartsWith(factor))
                    forceFactorParam = PARAM_MASS;
                else if (Angle.StartsWith(factor))
                    forceFactorParam = PARAM_ANGLE;
                else if (Image.StartsWith(factor))
                    forceFactorParam = PARAM_TEXTURE_INDEX;
                else
                    modifier = LinearForce::create(nullptr, INSIDE_ZONE, Vector3D(x, y));

                if (modifier == nullptr)
                {
                    ForceFactor forceFactor = FACTOR_NONE;
                    const int factorLength = String::CharsLength(factor);
                    BBAssertDebug(factorLength >= 2);
                    if (factor[factorLength - 1] == '*' &&
                        factor[factorLength - 2] == '*')
                        forceFactor = FACTOR_LINEAR;
                    else
                        forceFactor = FACTOR_SQUARE;

                    modifier = LinearForce::create(nullptr, INSIDE_ZONE, Vector3D(x, y), forceFactor, forceFactorParam);
                }
            }
            else
                modifier = LinearForce::create(nullptr, INSIDE_ZONE, Vector3D(x, y));
        }
        else if (t.type("Eye") == LUA_TTABLE)
        {
            lua_tinker::table eye = t.get<lua_tinker::table>("Eye");
            const float x = eye.get<float>(1);
            const float y = eye.get<float>(2);
            const float radius = eye.get<float>("Radius");
            const float attraction = t.get<float>("Attraction");
            const float rotation = t.get<float>("Rotation");

            if (Vortex* vortex = Vortex::create(Vector3D(x, y), Vector3D(0.0f, 0.0f, 1.0f), rotation, attraction))
            {
                if (radius > 0.001f)
                {
                    vortex->setEyeRadius(radius);
                    vortex->enableParticleKilling(true);
                }
                else
                    vortex->enableParticleKilling(false);

                modifier = vortex;
            }
        }
        else if (t.has("Mass"))
        {
            const float mass = t.get<float>("Mass");
            const float distance = t.get<float>("Distance");
            modifier = PointMass::create(nullptr, INSIDE_ZONE, mass, distance);
        }

        if (modifier)
        {
            modifier->setLocalToSystem(true);

            if (const char* trigger = t.get<const char*>("Trigger"))
            {
                const int availableTriggers = modifier->getAvailableTriggers();

                static const String Always = "Always";
                static const String Inside = "Inside";
                static const String Outside = "Outside";
                static const String Intersect = "Intersect";
                static const String Enter = "Enter";
                static const String Exit = "Exit";

                const int triggerLength = String::CharsLength(trigger);
                if ((availableTriggers & ALWAYS) && Always.EqualsIgnoreCase(trigger, triggerLength))
                    modifier->setTrigger(ALWAYS);
                else if ((availableTriggers & INSIDE_ZONE) && Inside.EqualsIgnoreCase(trigger, triggerLength))
                    modifier->setTrigger(INSIDE_ZONE);
                else if ((availableTriggers & OUTSIDE_ZONE) && Outside.EqualsIgnoreCase(trigger, triggerLength))
                    modifier->setTrigger(OUTSIDE_ZONE);
                else if ((availableTriggers & INTERSECT_ZONE) && Intersect.EqualsIgnoreCase(trigger, triggerLength))
                    modifier->setTrigger(INTERSECT_ZONE);
                else if ((availableTriggers & ENTER_ZONE) && Enter.EqualsIgnoreCase(trigger, triggerLength))
                    modifier->setTrigger(ENTER_ZONE);
                else if ((availableTriggers & EXIT_ZONE) && Exit.EqualsIgnoreCase(trigger, triggerLength))
                    modifier->setTrigger(EXIT_ZONE);
            }

            if (modifier->getTrigger() != ALWAYS)
            {
                if (t.type("Zone") == LUA_TTABLE)
                    modifier->setZone(CreateParticleZone(t.get<lua_tinker::table>("Zone")));
            }
        }

        return modifier;
    }

    Zone* UISpark::CreateParticleZone(lua_tinker::table t)
    {
        const int length = t.len();

        if (length == 2 &&
            t.type(1) == LUA_TTABLE &&
            t.type(2) == LUA_TTABLE)
        {
            lua_tinker::table first  = t.get<lua_tinker::table>(1);
            lua_tinker::table second = t.get<lua_tinker::table>(2);

            return Line::create(Vector3D(first.get<float>(1),
                                         first.get<float>(2)),
                                Vector3D(second.get<float>(1),
                                         second.get<float>(2)));
        }

        Vector3D position;
        if (length == 1)
        {
            position.x = t.get<float>(1);
            position.y = position.x;
        }
        else if (length == 2)
        {
            position.x = t.get<float>(1);
            position.y = t.get<float>(2);
        }
        else if (length == 4)
        {
            const float x = t.get<float>(1);
            const float y = t.get<float>(2);
            const float halfWidth  = t.get<float>(3) * 0.5f;
            const float halfHeight = t.get<float>(4) * 0.5f;
            return AABox::create(Vector3D(x + halfWidth, y + halfHeight),
                                 Vector3D(halfWidth, halfHeight, 0.0f));
        }

        if (t.has("Radius"))
        {
            MinMax radius(t, "Radius");
            if (radius.IsValid && radius.Min > 0.0f && radius.Max > 0.0f)
            {
                if (radius.Min != radius.Max)
                    return Ring::create(position, Vector3D(0.0f, 0.0f, 1.0f), radius.Min, radius.Max);
                else
                    return Sphere::create(position, radius.Min);
            }
        }

        return Point::create(position);
    }

    void UISpark::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
    }

    void UISpark::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        particleSystem = static_cast<System*>(SPKFactory::getInstance().copy(o->particleSystem));
        SetTimeline(o->timeline);
        contentSize = o->contentSize;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    
    UISpark::MinMax::MinMax(const char* value)
        : Min(0.0f),
          Max(0.0f)
    {
        IsValid = TryParse(value, Min, Max);
    }

    UISpark::MinMax::MinMax(lua_tinker::table& t, int key)
        : Min(0.0f),
          Max(0.0f),
          IsValid(false)
    {
        switch (t.type(key))
        {
            case LUA_TNUMBER:
                Min = t.get<float>(key);
                Max = Min;
                IsValid = true;
                break;
            case LUA_TSTRING:
                IsValid = TryParse(t.get<const char*>(key), Min, Max);
                break;
            case LUA_TTABLE:
                {
                    lua_tinker::table value = t.get<lua_tinker::table>(key);
                    Min = value.get<float>(1);
                    Max = value.get<float>(2);
                    IsValid = true;
                }
                break;
            default:
                IsValid = false;
                break;
        }
    }

    UISpark::MinMax::MinMax(lua_tinker::table& t, const char* key)
        : Min(0.0f),
          Max(0.0f),
          IsValid(false)
    {
        switch (t.type(key))
        {
            case LUA_TNUMBER:
                Min = t.get<float>(key);
                Max = Min;
                IsValid = true;
                break;
            case LUA_TSTRING:
                IsValid = TryParse(t.get<const char*>(key), Min, Max);
                break;
            case LUA_TTABLE:
                {
                    lua_tinker::table value = t.get<lua_tinker::table>(key);
                    Min = value.get<float>(1);
                    Max = value.get<float>(2);
                    IsValid = true;
                }
                break;
            default:
                IsValid = false;
                break;
        }
    }

    bool UISpark::MinMax::TryParse(const char* value, float& outMin, float& outMax)
    {
        if (value == nullptr || value[0] == '\0')
            return false;

         const int index = String::CharsFind(value, '~');
         if (index != -1)
         {
             const float first  = Float::Parse(&value[0], index);
             const float second = Float::Parse(&value[index + 1]);
             if (first <= second)
             {
                 outMin = first;
                 outMax = second;
             }
             else
             {
                 outMin = second;
                 outMax = first;
             }
         }
         else
         {
             outMin = Float::Parse(value);
             outMax = outMin;
         }

         return true;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UISpark::Updater::Updater()
        : o(nullptr)
    {
    }

    UISpark::Updater::~Updater()
    {
    }

    void UISpark::Updater::Update(float dt, int timestamp)
    {
        o->OnStep(dt, timestamp);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    void DirectionalRenderer::Draw(UIDrawingContext& context, const Group& group, const std::vector<ImagePtr>& imagePalette)
    {
        BEGIN_DRAW_PARTICLE(group, p);
        {
            context.DrawUnclipped(PARTICLE_POSITION(p),
                                  Math::Atan2(p.velocity().y, p.velocity().x),
                                  PARTICLE_SIZE(p),
                                  PARTICLE_IMAGE(p),
                                  PARTICLE_COLOR(p));
        }
        END_DRAW_PARTICLE();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    RandomAngleAxisRenderer::RandomAngleAxisRenderer()
    {
        if (AxesReady == false)
        {
            AxesReady = true;

            for (int i = 0; i < NumberOfAxes; i++)
            {
                Axes[i] = Vector3(Math::Random(-100, 100),
                                  Math::Random(-100, 100),
                                  Math::Random(-100, 100));
                if (Axes[i] != Vector3::Zero)
                    Axes[i].Normalize();
                else
                    Axes[i] = Vector3::UnitZ;
            }
        }
    }

    void RandomAngleAxisRenderer::Draw(UIDrawingContext& context, const Group& group, const std::vector<ImagePtr>& imagePalette)
    {
        BEGIN_DRAW_PARTICLE(group, p);
        {
            context.DrawUnclipped(PARTICLE_POSITION(p),
                                  PARTICLE_ANGLE(p),
                                  Axes[static_cast<int>(p.getParamCurrentValue(PARAM_CUSTOM_0))],
                                  PARTICLE_SIZE(p),
                                  PARTICLE_IMAGE(p),
                                  PARTICLE_COLOR(p));
        }
        END_DRAW_PARTICLE();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    SingleAngleAxisRenderer::SingleAngleAxisRenderer(Vector3 axis)
        : axis(axis)
    {
    }

    void SingleAngleAxisRenderer::Draw(UIDrawingContext& context, const Group& group, const std::vector<ImagePtr>& imagePalette)
    {
        BEGIN_DRAW_PARTICLE(group, p);
        {
            context.DrawUnclipped(PARTICLE_POSITION(p),
                                  PARTICLE_ANGLE(p),
                                  axis,
                                  PARTICLE_SIZE(p),
                                  PARTICLE_IMAGE(p),
                                  PARTICLE_COLOR(p));
        }
        END_DRAW_PARTICLE();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    MultipleAngleAxisRenderer::MultipleAngleAxisRenderer(std::vector<Vector3>& axes)
    {
        this->axes.swap(axes);
    }

    void MultipleAngleAxisRenderer::Draw(UIDrawingContext& context, const Group& group, const std::vector<ImagePtr>& imagePalette)
    {
        BEGIN_DRAW_PARTICLE(group, p);
        {
            context.DrawUnclipped(PARTICLE_POSITION(p),
                                  PARTICLE_ANGLE(p),
                                  axes[static_cast<int>(p.getParamCurrentValue(PARAM_CUSTOM_0))],
                                  PARTICLE_SIZE(p),
                                  PARTICLE_IMAGE(p),
                                  PARTICLE_COLOR(p));
        }
        END_DRAW_PARTICLE();
    }
}