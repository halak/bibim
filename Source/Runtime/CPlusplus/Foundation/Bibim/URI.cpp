#include <Bibim/PCH.h>
#include <Bibim/URI.h>

namespace Bibim
{
    const URI URI::Empty;

    URI::URI()
        : source(Anywhere),
          id(0),
          address(String::Empty)
    {
    }

    URI::URI(const char* address)
        : source(Anywhere),
          id(0),
          address(String::Empty)
    {
        if (address)
            Construct(address);
    }

    URI::URI(const String& address)
        : source(Anywhere),
          id(0),
          address(String::Empty)
    {
        Construct(address);
    }

    URI::URI(Source source, uint32 id)
        : source(source),
          id(id),
          address(String::Empty)
    {
    }

    URI::URI(Source source, const String& address)
        : source(source),
          id(0),
          address(address)
    {
    }

    URI::URI(const URI& original)
        : source(original.source),
          id(original.id),
          address(original.address)
    {
    }

    URI::~URI()
    {
    }

    void URI::Construct(const String& address)
    {
        static const String file = "file://";
        static const String http = "http://";

        if (address.StartsWithIgnoreCase(file)) 
        {
            this->source = FileSystem;
            this->address = address.Substring(file.GetLength());
        }
        else if (address.StartsWithIgnoreCase(http)) 
        {
            this->source = Internet;
            this->address = address.Substring(http.GetLength());
        }
        else
        {
            this->source = Anywhere;
            this->address = address;
        }
    }

    URI& URI::operator = (const URI& right)
    {
        source = right.source;
        id = right.id;
        address = right.address;
        return *this;
    }

    URI URI::FromFileSystem(const String& address)
    {
        return URI(FileSystem, address);
    }

    URI URI::FromEmbeddedResource(uint32 id)
    {
        return URI(EmbeddedResource, id);
    }

    URI URI::FromInternet(const String& address)
    {
        return URI(Internet, address);
    }
}