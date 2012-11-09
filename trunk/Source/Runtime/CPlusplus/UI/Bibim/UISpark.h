#pragma once
#ifndef __BIBIM_UISPARK_H__
#define __BIBIM_UISPARK_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIVisual.h>
#   include <Bibim/IUpdateable.h>
#   include <Bibim/SparkParticleEngine.h>
#   include <Bibim/Timeline.h>
#   include <vector>

    namespace Bibim
    {
        class UISpark : public UIVisual
        {
            BBComponentClass(UISpark, UIVisual, 'U', 'I', 'S', 'K');
            public:
                UISpark();
                UISpark(lua_tinker::table t);
                virtual ~UISpark();

                inline Timeline* GetTimeline() const;
                void SetTimeline(Timeline* value);

            protected:
                virtual Vector2 GetContentSize();

                        void OnStep(float dt, int timestamp);
                virtual void OnDraw(UIDrawingContext& context);

            private:
                void __Construct__();
                void __Construct__(lua_tinker::table t);
                SPK::Group* CreateParticleGroup(lua_tinker::table t);

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
                SPK::System* particleSystem;
                std::vector<ImagePtr> sources;
                Timeline* timeline;
                Vector2 contentSize;
                Updater updater;
        };
    }

#   include <Bibim/UISpark.inl>

#endif