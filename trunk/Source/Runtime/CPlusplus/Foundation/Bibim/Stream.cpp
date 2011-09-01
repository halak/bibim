#include <Bibim/PCH.h>
#include <Bibim/Stream.h>
#include <vector>

namespace Bibim
{
    Stream::Stream()
    {
    }

    Stream::~Stream()
    {
    }

    String Stream::ReadText()
    {
        String result;
        std::vector<char> buffer;

        buffer.resize(4096);

        for (;;)
        {
            const int size = Read(&buffer[0], static_cast<int>(buffer.size()));
            if (size > 0)
            {
                buffer[size] = '\0';
                result += &buffer[0];
            }
            else
                break;
        }

        return result;
    }
}