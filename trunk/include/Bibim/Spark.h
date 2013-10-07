#pragma once
#ifndef __BIBIM_SPARK_H__
#define __BIBIM_SPARK_H__

#include <Bibim/FWD.h>
#include <Bibim/GameAsset.h>
#include <Bibim/String.h>
#include <vector>

namespace Bibim
{
    class Spark : public GameAsset
    {
        BBSerializableAssetClass(Spark, GameAsset, 'A', 'S', 'P', 'K');
        public:
            Spark();
            Spark(const String& descriptor);
            virtual ~Spark();

            inline const String& GetDescriptor() const;
            void SetDescriptor(const String& value);

            inline ImageSet* GetImages() const;
            void SetImages(ImageSet* value);

        private:
            String descriptor;
            ImageSetPtr images;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const String& Spark::GetDescriptor() const
    {
        return descriptor;
    }

    ImageSet* Spark::GetImages() const
    {
        return images;
    }
}

#endif