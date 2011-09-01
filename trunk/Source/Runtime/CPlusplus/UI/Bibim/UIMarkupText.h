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
        // Bibim�� Markup ��Ģ�� �ǰ��Ͽ� ���ڿ��� �м��ϰ� ����� �����ϴ� class.
        // 
        // * |color|
        //   ���� ������ ���� ������ ��(color)���� �ٲ㼭 ����ϰ� �մϴ�.
        //   Color::CanParse���� true�� ��ȯ�޴� ���ڿ��� ���� �� �ֽ��ϴ�.
        //   �������� �ʴ� ���̶�� ���� �⺻ ������ �ٲߴϴ�.
        // * [type:name]
        // * [type:name?key1=value1&key2=value2]
        //   ���� Cursor ��ġ�� Ư�� Content�� �����մϴ�.
        //   ������� "halak.png"�� �׸��� �����ϰ� ������,
        //   [image:halak.png]�� ���·� �ۼ��ϸ� �˴ϴ�.
        //   �̸� ������ '?'�� �Է� �� ���� �Ӽ��� ������ �� �ֽ��ϴ�.
        //   ���� �Ӽ��� 'key=value'�� ���·� �Է��� �� ������,
        //   ������ �Ӽ��� '&'�� �����մϴ�.
        //   [image:halak.png?scale=2,2&horizontalFlip=yes]
        // * �� �ѱ��� '\r', '\n', '\r\n' ��� ����մϴ�.
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

                // Markup ���ڿ��� �̷�� ����Դϴ�.
                // Markup ���ڿ��� �������� Phrase�� �����˴ϴ�.
                class Phrase
                {
                    public:
                        // Phrase�� Type�� �����ɴϴ�.
                        // ��� �Ļ� class�� ���ϻ�� �ϰ��ֱ� ������,
                        // Type Ȯ�� �� static_cast�� ��ȯ�Ͽ� ����ϸ� �˴ϴ�. 
                        inline PhraseType GetType() const;

                        // ���� ���ڿ����� Phrase�� �����ϴ� ������ �����ɴϴ�.
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

                // �ܼ� ���ڿ��� ����Ű�� Phrase.
                class TextPhrase : public Phrase
                {
                    private:
                        TextPhrase(const String& originalText, int index, int length);
                        TextPhrase(const TextPhrase& original);
                        virtual ~TextPhrase();

                        virtual TextPhrase* Clone() const;

                        friend class UIMarkupText;
                };

                // �� Line�� ������ ����Ű�� Phrase.
                // ���ٸ� Field�� ���� ������ static_cast�� �ʿ䰡 �����ϴ�.
                class NewLinePhrase : public Phrase
                {
                    private:
                        inline NewLinePhrase();
                        inline NewLinePhrase(const NewLinePhrase& original);
                        virtual ~NewLinePhrase();

                        virtual NewLinePhrase* Clone() const;

                        friend class UIMarkupText;
                };

                // ���� �� ��ȭ�� ����Ű�� Phrase.
                class ColorPhrase : public Phrase
                {
                    public:
                        // �ٲ� ���� �����ɴϴ�.
                        inline Color GetColor() const;
                        // ���� �����Ǿ� �ִ��� Ȯ���մϴ�.
                        // �� Method�� ����� false�� �⺻������ ��ȯ�˴ϴ�.
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

                // �۲� ��ȭ�� ����Ű�� Phrase.
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