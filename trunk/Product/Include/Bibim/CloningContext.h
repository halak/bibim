#pragma once
#ifndef __BIBIM_CLONINGCONTEXT_H__
#define __BIBIM_CLONINGCONTEXT_H__

#   include <Bibim/FWD.h>
#   include <map>

    namespace Bibim
    {
        class CloningContext
        {
            public:
                CloningContext();
                ~CloningContext();

                void Store(const GameComponent* original, GameComponent* clone);

                GameComponent* CloneComponent(const GameComponent* item);
                template <typename T> T* Clone(const T* item);
                template <typename T> T* Clone(const SharedPointer<T>& item);

            private:
                typedef std::map<const GameComponent*, GameComponent*> ComponentMap;
            
            private:
                ComponentMap originalCloneMap;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        template <typename T> T* CloningContext::Clone(const T* item)
        {
            return static_cast<T*>(CloneComponent(static_cast<const GameComponent*>(item)));
        }

        template <typename T> T* CloningContext::Clone(const SharedPointer<T>& item)
        {
            return static_cast<T*>(CloneComponent(static_cast<const GameComponent*>(item.GetPointee())));
        }
    }

#endif