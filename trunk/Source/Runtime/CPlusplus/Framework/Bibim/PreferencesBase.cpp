#include <Bibim/PCH.h>
#include <Bibim/PreferencesBase.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

namespace Bibim
{
    PreferencesBase::PreferencesBase(const String& name)
        : name(name),
          isModified(false),
          isLoaded(false)
    {
        const char* buffer = name.CStr();
        const int length = name.GetLength();
        BBAssert(length >= 4);

        static const char ALLOWED_CHARS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890_-";
        static const int  ALLOWED_CHARS_COUNT = sizeof(ALLOWED_CHARS) / sizeof(ALLOWED_CHARS[0]);

        for (int i = 0; i < length; i++)
        {
            const char c = buffer[i];
            bool allowed = false;
            for (int k = 0; k < ALLOWED_CHARS_COUNT; k++)
            {
                if (c == ALLOWED_CHARS[k])
                {
                    allowed = true;
                    break;
                }
            }

            if (allowed == false)
            {
                // ������ ���� ���ڿ��� �����մϴ�.
                BBBreak();
            }
        }
    }

    PreferencesBase::~PreferencesBase()
    {
        if (IsModified())
        {
            // ����� �����Ͱ� �ִµ� ������ ���߽��ϴ�.
            BBBreak();
        }
    }

    const Any& PreferencesBase::GetValue(const String& key)
    {
        if (IsLoaded() == false)
            Update();

        Dictionary::const_iterator it = items.find(key);
        if (it != items.end())
            return (*it).second;
        else
            return Any::Void;
    }

    void PreferencesBase::SetValue(const String& key, const Any& value)
    {
        if (key.IsEmpty())
            return;

        if (IsLoaded() == false)
            Update();

        if (value.GetType() != Any::VoidType)
        {
            if (CanStore(value.GetType()))
            {
                items[key] = value;
                isModified = true;
            }
        }
        else
        {
            Dictionary::iterator it = items.find(key);
            if (it != items.end())
            {
                items.erase(it);
                isModified = true;
            }
        }
    }

    void PreferencesBase::Update()
    {
        isLoaded = true;

        rapidjson::Document document;
        const String documentString = Load();
        document.Parse<0>(documentString.CStr());
        
        if (document.HasParseError())
            return;

        BBAssert(document.IsObject());

        items.clear();

        typedef rapidjson::Document::ConstMemberIterator ConstMemberIterator;
        for (ConstMemberIterator it = document.MemberBegin(); it != document.MemberEnd(); it++)
        {
            const String key = String((*it).name.GetString(), 0, (*it).name.GetStringLength());
            Any value = Any::Void;
            switch ((*it).value.GetType())
            {
                case rapidjson::kFalseType:
                    value = Any::False;
                    break;
                case rapidjson::kTrueType:
                    value = Any::True;
                    break;
                case rapidjson::kStringType:
                    value = Any(String((*it).value.GetString(), 0, (*it).value.GetStringLength()));
                    break;
                case rapidjson::kNumberType:
                    value = Any((*it).value.GetInt());
                    break;
            }

            if (value != Any::Void)
                items[key] = value;
        }
    }

    void PreferencesBase::Commit()
    {
        if (IsModified() == false || IsLoaded() == false)
            return;

        rapidjson::Document document;
        document.SetObject();
        for (Dictionary::const_iterator it = items.begin(); it != items.end(); it++)
        {
            const char* key = (*it).first.CStr();
            const Any& value = (*it).second;
            switch (value.GetType())
            {
                case Any::BoolType:
                    document.AddMember(key, value.CastBool(), document.GetAllocator());
                    break;
                case Any::IntType:
                    document.AddMember(key, value.CastInt(), document.GetAllocator());
                    break;
                case Any::StringType:
                    document.AddMember(key, value.CastString().CStr(), document.GetAllocator());
                    break;
            }
        }

        rapidjson::StringBuffer output;
	    rapidjson::Writer<rapidjson::StringBuffer> writer(output);
        document.Accept(writer);

        if (const char* s = output.GetString())
            Save(s);

        isModified = false;
    }
}