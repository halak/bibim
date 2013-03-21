#include <Bibim/PCH.h>
#include <Bibim/Preferences.Windows.h>
#include <Bibim/Environment.h>
#include <Bibim/FileStream.h>
#include <vector>

namespace Bibim
{
    Preferences::Preferences(const String& name)
        : Base(name)
    {
    }

    Preferences::~Preferences()
    {
    }

    String Preferences::Load()
    {
        const String path = Environment::GetAppDataPath(GetName(), "preferences");
        FileStreamPtr stream = new FileStream(path, FileStream::ReadOnly);
        if (stream->CanRead() == false)
            return String::Empty;

        std::vector<char> buffer;
        buffer.resize(stream->GetLength());
        stream->Read(&buffer[0], buffer.size());
        stream->Close();

        return String(&buffer[0], 0, buffer.size());
    }

    void Preferences::Save(const String& document)
    {
        const String path = Environment::GetAppDataPath(GetName(), "preferences");
        FileStreamPtr stream = new FileStream(path, FileStream::WriteOnly);
        if (stream->CanWrite() == false)
            return;

        stream->Write(document.CStr(), document.GetLength());
        stream->Close();
    }
}