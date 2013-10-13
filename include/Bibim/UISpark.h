#pragma once
#ifndef __BIBIM_UISPARK_H__
#define __BIBIM_UISPARK_H__

#include <Bibim/FWD.h>
#include <Bibim/UIVisual.h>
#include <Bibim/IUpdateable.h>
#include <Bibim/SparkParticleEngine.h>
#include <Bibim/Timeline.h>
#include <vector>

namespace SPK { class System; class Group; class Emitter; class Modifier; class Zone; class Particle; };

namespace Bibim
{
    class UISpark : public UIVisual
    {
        BBComponentClass(UISpark, UIVisual, 'U', 'I', 'S', 'K');
        public:
            UISpark();
            UISpark(lua_tinker::table t);
            virtual ~UISpark();

            void Load(lua_tinker::table t);

            inline Spark* GetSource() const;
            void SetSource(Spark* value);

            inline Timeline* GetTimeline() const;
            void SetTimeline(Timeline* value);

            inline bool GetAutoRemove() const;
            void SetAutoRemove(bool value);

            virtual Vector2 GetContentSize();

        protected:
                    void OnStep(float dt, int timestamp);
            virtual void OnDraw(UIDrawingContext& context);

        private:
            void __Construct__();
            void __Construct__(lua_tinker::table t);

            SPK::Group*    CreateParticleGroup(lua_tinker::table t);
            SPK::Emitter*  CreateParticleEmitter(lua_tinker::table t, SPK::Group* group, int& outInitialParticles);
            static SPK::Modifier* CreateParticleModifier(lua_tinker::table t);
            static SPK::Zone*     CreateParticleZone(lua_tinker::table t);

            static bool UpdateMotionRandomness(SPK::Particle& particle, float dt);

            struct Burst
            {
                float Time;
                int Count;
                SPK::Group* Group;
                SPK::Emitter* Emitter;
            };

            struct MinMax
            {
                float Min;
                float Max;
                bool IsValid;

                MinMax(const char* value);
                MinMax(lua_tinker::table& t, int key);
                MinMax(lua_tinker::table& t, const char* key);

                static bool TryParse(const char* value, float& outMin, float& outMax);
            };

            class Updater : public IUpdateable
            {
                public:
                    Updater();
                    virtual ~Updater();

                    virtual void Update(float dt, int timestamp);

                public:
                    UISpark* o;
            };

        private:
            SparkPtr source;
            SPK::System* particleSystem;
            std::vector<ImagePtr> imagePalette;
            std::vector<Burst> burstTable;
            int lastBurstIndex;
            float burstTime;
            Timeline* timeline;
            Vector2 contentSize;
            Updater updater;
            bool isUpdateable;
            bool autoRemove;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    Spark* UISpark::GetSource() const
    {
        return source;
    }

    Timeline* UISpark::GetTimeline() const
    {
        return timeline;
    }

    bool UISpark::GetAutoRemove() const
    {
        return autoRemove;
    }
}

#endif