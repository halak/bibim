#include <Bibim/Config.h>
#include <Bibim/Spark.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/ImageSet.h>

namespace Bibim
{
    Spark::Spark()
    {
        // for cloning and deserialization
    }

    Spark::Spark(const String& descriptor)
        : descriptor(descriptor)
    {
    }

    Spark::~Spark()
    {
    }

    void Spark::SetDescriptor(const String& value)
    {
        descriptor = value;
    }

    void Spark::SetImages(ImageSet* value)
    {
        images = value;
    }

    GameAsset* Spark::Create(StreamReader& reader, GameAsset* /*existingInstance*/)
    {
        return new Spark(reader.ReadString());
    }
}