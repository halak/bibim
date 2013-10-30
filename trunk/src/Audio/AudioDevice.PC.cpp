#include <Bibim/Config.h>
#if (defined(BIBIM_PLATFORM_PC))

#include <Bibim/AudioDevice.PC.h>
#include <Bibim/Assert.h>
#include <Bibim/MPQ.h>
#include <Bibim/MPQStream.h>
#include <irrklang.h>
using namespace irrklang;

namespace Bibim
{
    class IrrFileReader : public IFileReader
    {
        public:
            IrrFileReader(Stream* stream, const String& fileName)
                : stream(stream),
                  fileName(fileName)
            {
            }

            virtual ~IrrFileReader()
            {
            }

            virtual ik_s32 read(void* buffer, ik_u32 sizeToRead)
            {
                return stream->Read(buffer, sizeToRead);
            }

            virtual bool seek(ik_s32 finalPos, bool relativeMovement)
            {
                if (relativeMovement)
                {
                    const int oldPosition = stream->GetPosition();
                    return stream->Seek(finalPos, Stream::FromCurrent) >= oldPosition;
                }
                else
                    return stream->Seek(finalPos, Stream::FromBegin) == finalPos;
            }

            virtual ik_s32 getSize()
            {
                return stream->GetLength();
            }

            virtual ik_s32 getPos()
            {
                return stream->GetPosition();
            }

            virtual const ik_c8* getFileName()
            {
                return fileName.CStr();
            }

        private:
            StreamPtr stream;
            String fileName;
    };

    class IrrFileFactory : public IFileFactory
    {
        public:
            IrrFileFactory(MPQ* mpq)
                : mpq(mpq)
            {
            }

            virtual ~IrrFileFactory()
            {
            }

            virtual IFileReader* createFileReader(const ik_c8* filename)
            {
                if (mpq->Has(filename))
                    return new IrrFileReader(new MPQStream(mpq, filename), filename);
                else
                    return nullptr;
            }

        private:
            MPQPtr mpq;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    AudioDevice::AudioDevice()
    {
        engine = createIrrKlangDevice(ESOD_AUTO_DETECT, ESEO_MULTI_THREADED | ESEO_PRINT_DEBUG_INFO_TO_DEBUGGER);
    }

    AudioDevice::~AudioDevice()
    {
        engine->drop();
        engine = nullptr;
    }

    void AudioDevice::AddArchive(MPQ* mpq)
    {
        if (mpq == nullptr || engine == nullptr)
            return;

        IrrFileFactory* factory = new IrrFileFactory(mpq);
        engine->addFileFactory(factory);
        factory->drop();
    }

    float AudioDevice::GetDurationByChars(const char* uri) const
    {
        if (uri == nullptr)
            return 0.0f;

        if (ISoundSource* source = engine->getSoundSource(uri))
            return static_cast<float>(source->getPlayLength()) * 0.001f;
        else
            return 0.0f;
    }
}

#endif