#include <Bibim/PCH.h>
#include <Bibim/UISpark.h>
#include <Bibim/Assert.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Image.h>
#include <Bibim/Math.h>
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

	    // Model
	    Model* particleModel = Model::create(FLAG_RED | FLAG_GREEN | FLAG_BLUE | FLAG_ALPHA);
	    particleModel->setParam(PARAM_ALPHA,0.8f); // constant alpha
	    particleModel->setLifeTime(8.0f,8.0f);

	    // Emitter
        SphericEmitter* particleEmitter = SphericEmitter::create(Vector3D(0.0f,1.0f,0.0f),0.1f * Math::Pi,0.4f * Math::Pi);
	    particleEmitter->setZone(Ring::create(Vector3D(0.0f,0.015f,0.0f), Vector3D(0.0f, 0.0f, 1.0f), 50.0f, 100.0f));
	    particleEmitter->setFlow(250);
	    particleEmitter->setForce(0.0f,-0.5f);

	    // Obstacle
	    Plane* groundPlane = Plane::create();
	    Obstacle* obstacle = Obstacle::create(groundPlane,INTERSECT_ZONE,0.6f,1.0f);

	    // Group
	    Group* particleGroup = Group::create(particleModel,2100);
	    particleGroup->addEmitter(particleEmitter);
	    particleGroup->addModifier(obstacle);
	    // particleGroup->setRenderer(particleRenderer);
	    particleGroup->setGravity(Vector3D(0.0f, 1000.8f, 0.0f));
    	
	    particleSystem = System::create();
	    particleSystem->addGroup(particleGroup);
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