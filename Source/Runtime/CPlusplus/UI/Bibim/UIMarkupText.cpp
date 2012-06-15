#include <Bibim/PCH.h>
#include <Bibim/UIMarkupText.h>
#include <Bibim/Assert.h>
#include <Bibim/Colors.h>
#include <Bibim/Math.h>
#include <algorithm>

namespace Bibim
{
    const UIMarkupText UIMarkupText::Empty = UIMarkupText();

    UIMarkupText::UIMarkupText()
    {
    }

    UIMarkupText::UIMarkupText(const String text)
        : originalText(text)
    {
        Parse();
    }

    UIMarkupText::UIMarkupText(const UIMarkupText& original)
        : originalText(original.originalText),
          displayText(original.displayText)
    {
        Copy(phrases, original.phrases);
    }

    UIMarkupText::~UIMarkupText()
    {
        PhraseCollection deletingPhrases;
        deletingPhrases.swap(phrases);
        
        for (PhraseCollection::const_iterator it = deletingPhrases.begin(); it != deletingPhrases.end(); it++)
            delete (*it);
    }

    UIMarkupText& UIMarkupText::operator = (const UIMarkupText& original)
    {
        originalText = original.originalText;
        displayText = original.displayText;
        Copy(phrases, original.phrases);
        return *this;
    }

    bool UIMarkupText::operator == (const UIMarkupText& right) const
    {
        return originalText == right.originalText;
    }

    bool UIMarkupText::operator != (const UIMarkupText& right) const
    {
        return !operator == (right);
    }

    void UIMarkupText::AddSubText(int index, int length)
    {
        if (index < 0 || length <= 0)
            return;

        phrases.push_back(new TextPhrase(originalText, index, length));
        displayText.Append(&originalText.CStr()[index], length);
    }

    template <typename T> int UIMarkupText::AddSpecialPhrase(int index, char open, char close, int subTextIndex, int subTextLength)
    {
        if (index + 1 < originalText.GetLength())
        {
            if (originalText[index + 1] == open)
            {
                // 여는 문자가 연속적으로 써져 있을 때
                // 여는 문자 하나를 추가합니다.
                AddSubText(subTextIndex, subTextLength + 1);
                index += 2;
            }
            else
            {
                // 종결자를 찾습니다.
                const int closeIndex = originalText.Find(close, index + 1);
                if (closeIndex != -1)
                {
                    // 그전까지 쌓아둔 문자열을 그대로 추가합니다.
                    AddSubText(subTextIndex, subTextLength);

                    const int contentIndex  = index + 1;
                    const int contentLength = closeIndex - index - 1;
                    if (contentLength > 0)
                        phrases.push_back(new T(originalText, contentIndex, contentLength));

                    index = closeIndex + 1;
                }
                else
                {
                    // 열렸는데 안 닫혀있을 때는 추가합니다.
                    AddSubText(subTextIndex, subTextLength + 1);
                    index++;
                }
            }
        }
        else
        {
            // 마지막 문자였을 때는 추가합니다.
            AddSubText(subTextIndex, subTextLength + 1);
            index++;
        }

        return index;
    }

    void UIMarkupText::Parse()
    {
        if (originalText.IsEmpty())
            return;

        int subTextIndex  = 0;
        int subTextLength = 0;
        for (int i = 0; i < originalText.GetLength();)
        {
            switch (originalText[i])
            {
                case '|':
                    i = AddSpecialPhrase<ColorPhrase>(i, '|', '|', subTextIndex, subTextLength);
                    subTextIndex = i;
                    subTextLength = 0;
                    break;
                case '[':
                    i = AddSpecialPhrase<ContentPhrase>(i, '[', ']', subTextIndex, subTextLength);
                    subTextIndex = i;
                    subTextLength = 0;
                    break;
                case ']':
                    if (i + 1 < originalText.GetLength())
                    {
                        if (originalText[i + 1] == ']')
                        {
                            // ']]' 일 때
                            // ==> ']'를 추가합니다.
                            AddSubText(i, 1);
                            i += 2;
                            subTextIndex = i;
                            subTextLength = 0;
                        }
                    }
                    else
                    {
                        // ']'로 끝났을 때
                        i++;
                        subTextLength++;
                    }
                    break;
                case '\r': // 개행문자 처리 (Text Phrase 나눔)
                    AddSubText(subTextIndex, subTextLength);
                    phrases.push_back(new NewLinePhrase());

                    i++;

                    // '\r' 다음에 '\n'이 이어진다면 '\n'을 무시합니다.
                    if (i < originalText.GetLength() && originalText[i] == '\n')
                        i++;

                    subTextIndex = i;
                    subTextLength = 0;

                    break;
                case '\n': // 개행문자 처리 (Text Phrase 나눔)
                    AddSubText(subTextIndex, subTextLength);
                    phrases.push_back(new NewLinePhrase());

                    i++;
                    subTextIndex = i;
                    subTextLength = 0;
                    break;
                default:
                    i++;
                    subTextLength++;
                    break;
            }
        }

        AddSubText(subTextIndex, subTextLength);
    }

    void UIMarkupText::Copy(PhraseCollection& outTarget, const PhraseCollection& original)
    {
        BBAssert(outTarget.size() == 0);

        outTarget.reserve(original.size());
        for (PhraseCollection::const_iterator it = original.begin(); it != original.end(); it++)
            outTarget.push_back((*it)->Clone());
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIMarkupText::Phrase::Phrase(PhraseType type)
        : type(type),
          index(-1),
          length(-1)
    {
    }

    UIMarkupText::Phrase::Phrase(PhraseType type, int index, int length)
        : type(type),
          index(index),
          length(length)
    {
    }

    UIMarkupText::Phrase::Phrase(const Phrase& original)
        : type(original.type),
          index(original.index),
          length(original.length)
    {
    }

    UIMarkupText::Phrase::~Phrase()
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIMarkupText::TextPhrase::TextPhrase(const String& /*originalText*/, int index, int length)
        : Phrase(TextPhraseType, index, length)
    {
    }

    UIMarkupText::TextPhrase::TextPhrase(const TextPhrase& original)
        : Phrase(original)
    {
    }

    UIMarkupText::TextPhrase::~TextPhrase()
    {
    }

    UIMarkupText::TextPhrase* UIMarkupText::TextPhrase::Clone() const
    {
        return new TextPhrase(*this);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIMarkupText::NewLinePhrase::NewLinePhrase()
        : Phrase(NewLinePhraseType)
    {
    }

    UIMarkupText::NewLinePhrase::NewLinePhrase(const NewLinePhrase& original)
        : Phrase(original)
    {
    }

    UIMarkupText::NewLinePhrase::~NewLinePhrase()
    {
    }

    UIMarkupText::NewLinePhrase* UIMarkupText::NewLinePhrase::Clone() const
    {
        return new NewLinePhrase(*this);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIMarkupText::ColorPhrase::ColorPhrase(const String& originalText, int index, int length)
        : Phrase(ColorPhraseType, index, length),
          color(Colors::Black),
          hasColor(false)
    {
        if (const Color* namedColor = Colors::Find(originalText.Substring(index, length)))
        {
            color = (*namedColor);
            hasColor = true;
        }
        else
            hasColor = false;
    }

    UIMarkupText::ColorPhrase::ColorPhrase(const ColorPhrase& original)
        : Phrase(original),
          color(original.color),
          hasColor(original.hasColor)
    {
    }

    UIMarkupText::ColorPhrase::~ColorPhrase()
    {
    }

    UIMarkupText::ColorPhrase* UIMarkupText::ColorPhrase::Clone() const
    {
        return new ColorPhrase(*this);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIMarkupText::FontPhrase::FontPhrase(const String& /*originalText*/, int index, int length)
        : Phrase(FontPhraseType, index, length)
    {
    }
    
    UIMarkupText::FontPhrase::FontPhrase(const FontPhrase& original)
        : Phrase(original)
    {
    }

    UIMarkupText::FontPhrase::~FontPhrase()
    {
    }

    UIMarkupText::FontPhrase* UIMarkupText::FontPhrase::Clone() const
    {
        return new FontPhrase(*this);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIMarkupText::ContentPhrase::ContentPhrase(const String& originalText, int index, int length)
        : Phrase(ContentPhraseType, index, length)
    {
        int colonIndex    = originalText.Find(':', index);
        int questionIndex = originalText.Find('?', index);
        if (colonIndex != -1)
        {
            contentType = originalText.Substring(index, Math::Min(colonIndex - index, length));
            contentType.Trim();
        }

        if (questionIndex != -1)
        {
            contentName = originalText.Substring(colonIndex + 1, Math::Min(questionIndex - colonIndex - 1, length));

            const int offset = questionIndex + 1;
            ParseAttributes(originalText, offset, index + length - offset);
        }
        else
        {
            const int offset = colonIndex + 1;
            contentName = originalText.Substring(offset, index + length - offset);
        }
    }

    UIMarkupText::ContentPhrase::ContentPhrase(const ContentPhrase& original)
        : Phrase(original),
          contentType(original.contentType),
          contentName(original.contentName),
          attributes(original.attributes)
    {
    }

    UIMarkupText::ContentPhrase::~ContentPhrase()
    {
    }

    UIMarkupText::ContentPhrase* UIMarkupText::ContentPhrase::Clone() const
    {
        return new ContentPhrase(*this);
    }

    void UIMarkupText::ContentPhrase::ParseAttributes(const String& originalText, int index, int length)
    {
        const int end = index + length;
        for (int i = index; i < end;)
        {
            const int equalSignIndex = originalText.Find('=', i);
            if (equalSignIndex == -1)
                break;

            int ampersandIndex = originalText.Find('&', i);
            if (ampersandIndex == -1)
                ampersandIndex = end;

            if (equalSignIndex < ampersandIndex)
            {
                String key = originalText.Substring(i, equalSignIndex - i);
                attributes.Add(key, originalText.Substring(equalSignIndex + 1, ampersandIndex - equalSignIndex - 1));
            }

            i = ampersandIndex + 1;
        }

        attributes.Optimize();
    }
}