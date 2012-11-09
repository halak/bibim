#include <Bibim/PCH.h>
#include <Bibim/UISpark.h>
#include <Bibim/Assert.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Image.h>
#include <Bibim/Math.h>
#include <Bibim/Numerics.h>
#include <Bibim/Timeline.h>
#include <Bibim/UIDrawingContext.h>
#include <Bibim/UIPickingContext.h>
using namespace SPK;

namespace Bibim
{
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
        SPKFactory::getInstance().destroy(particleSystem);
        SetTimeline(nullptr);
    }

    void UISpark::SetTimeline(Timeline* value)
    {
        if (timeline != value)
        {
            if (timeline)
                timeline->Remove(&updater);

            timeline = value;

            if (timeline)
                timeline->Add(&updater, this);
        }
    }

    Vector2 UISpark::GetContentSize()
    {
        return contentSize;
    }

    void UISpark::OnStep(float dt, int /*timestamp*/)
    {
        if (particleSystem == nullptr)
            return;

        const bool enabledAABBComputing = (GetWidthMode()  == ContentSize) || 
                                          (GetHeightMode() == ContentSize);

        particleSystem->enableAABBComputing(enabledAABBComputing);

        const bool isAlive = particleSystem->update(dt);

        if (isAlive == false)
        {
        }

        if (enabledAABBComputing)
        {
            const Vector3D max = particleSystem->getAABBMax();
            const Vector3D min = particleSystem->getAABBMin();
            contentSize.X = max.x - min.x;
            contentSize.Y = max.y - min.y;
        }
    }

    void UISpark::OnDraw(UIDrawingContext& context)
    {
        UIVisual::OnDraw(context);

        if (particleSystem == nullptr)
            return;

        typedef std::vector<Group*> Groups;
        const Groups& groups = particleSystem->getGroups();
        for (Groups::const_iterator it = groups.begin(); it != groups.end(); it++)
        {
            const Group* g = (*it);
            const int count = g->getNbParticles();
            for (int i = 0; i < count; i++)
            {
                const Particle& p = g->getParticle(i);

                context.DrawLine(Vector2(100.0f + p.position().x, 100.0f + p.position().y), Vector2(p.position().x + 103, p.position().y + 103), Color(255, 255, 255));
            }
        }

        // context.Draw(GetSource(), GetHorizontalFlip(), GetVerticalFlip());
    }

    void UISpark::__Construct__()
    {
        particleSystem = nullptr;
        timeline = nullptr;
        contentSize = Vector2::Zero;
        updater.o = this;

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
    }

    SPK::Group* UISpark::CreateParticleGroup(lua_tinker::table t)
    {
        struct MinMax
        {
            float Min;
            float Max;
            bool IsValid;

            MinMax(lua_tinker::table& t, const char* key)
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
                        IsValid = ToMinMax(t.get<const char*>(key), Min, Max);
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
        };

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
                                Enable |= flags;
                        }
                        break;
                    case LUA_TTABLE:
                        {
                            lua_tinker::table value = t.get<lua_tinker::table>(key);
                            if (value.has(1) && value.has(2))
                            {
                                Mutable |= flags;

                                // 테이블의 첫번째, 두번째 값중 하나라도 "1~2"와 같은 범위 값이면,
                                // 전체를 random 값으로 설정합니다.
                                if ((value.type(1) == LUA_TSTRING && String::CharsFind(value.get<const char*>(1), '~') != -1) ||
                                    (value.type(2) == LUA_TSTRING && String::CharsFind(value.get<const char*>(2), '~') != -1))
                                    Random |= flags;
                            }
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
                        ToMinMax(value.get<const char*>(1), birthMin, birthMax);
                    else
                    {
                        birthMin = value.get<float>(1);
                        birthMax = birthMin;
                    }

                    if (value.type(2) == LUA_TSTRING)
                        ToMinMax(value.get<const char*>(2), deathMin, deathMax);
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
                    if (ToMinMax(t.get<const char*>(key), min, max))
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

        MinMax lifetime(t, "Lifetime");
        if (lifetime.IsValid)
	        model->setLifeTime(lifetime.Min, lifetime.Max);

        static const char*const CapacityKey = "CapacityKey";
        int capacity = Pool<Particle>::DEFAULT_CAPACITY;
        if (t.has(CapacityKey))
            capacity = t.get<int>(CapacityKey);

	    Group* group = Group::create(model, capacity);

        lua_tinker::table emitters = t.get<lua_tinker::table>("Emitters");
        const int numberOfEmitters = emitters.len();
        for (int i = 1; i <= numberOfEmitters; i++)
        {
            Emitter* emitter = nullptr;
            int initialParticles = 0;

            /*
            SphericEmitter* particleEmitter = SphericEmitter::create(Vector3D(0.0f,1.0f,0.0f),0.1f * Math::Pi,0.4f * Math::Pi);
	        particleEmitter->setZone(Ring::create(Vector3D(0.0f,0.015f,0.0f), Vector3D(0.0f, 0.0f, 1.0f), 50.0f, 100.0f));
	        particleEmitter->setFlow(250);
	        particleEmitter->setForce(0.0f,-0.5f);
            */

            if (emitter)
            {
                group->addEmitter(emitter);

                if (initialParticles > 0)
                    group->addParticles(initialParticles, emitter);
            }
        }

        lua_tinker::table modifiers = t.get<lua_tinker::table>("Modifiers");
        const int numberOfModifiers = modifiers.len();
        for (int i = 1; i <= numberOfModifiers; i++)
        {
            Modifier* modifier = nullptr;

            /*
	        Plane* groundPlane = Plane::create();
	        Obstacle* obstacle = Obstacle::create(groundPlane,INTERSECT_ZONE,0.6f,1.0f);
            */

            if (modifier)
                group->addModifier(modifier);
        }

        MinMax gravity(t, "Gravity");
        if (gravity.IsValid)
            group->setGravity(Vector3D(gravity.Min, gravity.Max, 0.0f));

        static const char*const FrictionKey = "Friction";
        if (t.has(FrictionKey))
            group->setFriction(t.get<float>(FrictionKey));

        return group;
    }

    bool UISpark::ToMinMax(const char* value, float& outMin, float& outMax)
    {
         const int index = String::CharsFind(value, '~');
         if (index != -1)
         {
             outMin = Float::Parse(&value[0], index);
             outMax = Float::Parse(&value[index + 1]);
         }
         else
         {
             outMin = Float::Parse(value);
             outMax = outMin;
         }

         return true;
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
}