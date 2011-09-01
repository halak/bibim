#pragma once
#ifndef __BIBIM_UIMARKUPTEXT_H__
#define __BIBIM_UIMARKUPTEXT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Color.h>
#   include <Bibim/SequenceDictionary.h>
#   include <Bibim/String.h>
#   include <vector>

    namespace Bibim
    {
        // Bibim용 Markup 규칙에 의거하여 문자열을 분석하고 결과를 보관하는 class.
        // 
        // * |color|
        //   이후 문자의 색을 지정한 색(color)으로 바꿔서 출력하게 합니다.
        //   Color::CanParse에서 true를 반환받는 문자열을 넣을 수 있습니다.
        //   존재하지 않는 색이라면 전역 기본 색으로 바꿉니다.
        // * [type:name]
        // * [type:name?key1=value1&key2=value2]
        //   현재 Cursor 위치에 특정 Content를 삽입합니다.
        //   예를들어 "halak.png"란 그림을 삽입하고 싶으면,
        //   [image:halak.png]의 형태로 작성하면 됩니다.
        //   이름 다음에 '?'를 입력 후 세부 속성을 설정할 수 있습니다.
        //   세부 속성은 'key=value'의 형태로 입력할 수 있으며,
        //   복수의 속성은 '&'로 구분합니다.
        //   [image:halak.png?scale=2,2&horizontalFlip=yes]
        // * 줄 넘김은 '\r', '\n', '\r\n' 모두 허용합니다.
        class UIMarkupText
        {
            public:
                enum PhraseType
                {
                    TextPhraseType,
                    NewLinePhraseType,
                    ColorPhraseType,
                    FontPhraseType,
                    ContentPhraseType,
                };

                // Markup 문자열을 이루는 요소입니다.
                // Markup 문자열은 여러개의 Phrase로 구성됩니다.
                class Phrase
                {
                    public:
                        // Phrase의 Type을 가져옵니다.
                        // 모든 파생 class는 단일상속 하고있기 때문에,
                        // Type 확인 후 static_cast로 변환하여 사용하면 됩니다. 
                        inline PhraseType GetType() const;

                        // 원본 문자열에서 Phrase가 차지하는 영역을 가져옵니다.
                        inline int GetIndex() const;
                        inline int GetLength() const;

                    protected:
                        Phrase(PhraseType type);
                        Phrase(PhraseType type, int index, int length);
                        Phrase(const Phrase& original);
                        virtual ~Phrase();

                        virtual Phrase* Clone() const = 0;

                    private:
                        PhraseType type;
                        int index;
                        int length;

                    private:
                        Phrase& operator = (const Phrase&);

                        friend class UIMarkupText;
                };

                // 단순 문자열을 가리키는 Phrase.
                class TextPhrase : public Phrase
                {
                    private:
                        TextPhrase(const String& originalText, int index, int length);
                        TextPhrase(const TextPhrase& original);
                        virtual ~TextPhrase();

                        virtual TextPhrase* Clone() const;

                        friend class UIMarkupText;
                };

                // 새 Line의 시작을 가리키는 Phrase.
                // 별다른 Field가 없기 때문에 static_cast할 필요가 없습니다.
                class NewLinePhrase : public Phrase
                {
                    private:
                        inline NewLinePhrase();
                        inline NewLinePhrase(const NewLinePhrase& original);
                        virtual ~NewLinePhrase();

                        virtual NewLinePhrase* Clone() const;

                        friend class UIMarkupText;
                };

                // 문자 색 변화를 가리키는 Phrase.
                class ColorPhrase : public Phrase
                {
                    public:
                        // 바꿀 색을 가져옵니다.
                        inline Color GetColor() const;
                        // 색이 지정되어 있는지 확인합니다.
                        // 이 Method의 결과가 false면 기본색으로 전환됩니다.
                        inline bool  HasColor() const;

                    private:
                        ColorPhrase(const String& originalText, int index, int length);
                        ColorPhrase(const ColorPhrase& original);
                        virtual ~ColorPhrase();

                        virtual ColorPhrase* Clone() const;

                    private:
                        Color color;
                        bool hasColor;

                        friend class UIMarkupText;
                };

                // 글꼴 변화를 가리키는 Phrase.
                class FontPhrase : public Phrase
                {
                    private:
                        FontPhrase(const String& originalText, int index, int length);
                        FontPhrase(const FontPhrase& original);
                        virtual ~FontPhrase();

                        virtual FontPhrase* Clone() const;

                    private:
                        friend class UIMarkupText;
                };

                class ContentPhrase : public Phrase
                {
                    public:
                        inline const String& GetContentType() const;
                        inline const String& GetContentName() const;
                        inline const SequenceDictionary& GetAttributes() const;

                    private:
                        ContentPhrase(const String& originalText, int index, int length);
                        ContentPhrase(const ContentPhrase& original);
                        virtual ~ContentPhrase();

                        virtual ContentPhrase* Clone() const;

                        void ParseAttributes(const String& originalText, int index, int length);

                    private:
                        String contentType;
                        String contentName;
                        SequenceDictionary attributes;
                        
                        friend class UIMarkupText;
                };

            public:
                typedef std::vector<Phrase*> PhraseCollection;

            public:
                UIMarkupText();
                UIMarkupText(const String original);
                UIMarkupText(const UIMarkupText& original);
                ~UIMarkupText();

                inline const String& GetOriginalText() const;
                inline const String& GetDisplayText() const;
                inline const PhraseCollection& GetPhrases() const;

                UIMarkupText& operator = (const UIMarkupText& original);
                bool operator == (const UIMarkupText& right) const;
                bool operator != (const UIMarkupText& right) const;

            public:
                static const UIMarkupText Empty;

            private:
                void AddSubText(int index, int length);
                template <typename T> int AddSpecialPhrase(int index, char open, char close, int subTextIndex, int subTextLength);

                void Parse();

                static void Copy(PhraseCollection& outTarget, const PhraseCollection& original);

            private:
                String originalText;
                String displayText;
                PhraseCollection phrases;
        };
    }

#   include <Bibim/UIMarkupText.inl>

#endif