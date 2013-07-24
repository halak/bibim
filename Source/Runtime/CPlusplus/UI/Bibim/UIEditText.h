#pragma once
#ifndef __BIBIM_UIEDITEXT_H__
#define __BIBIM_UIEDITEXT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UILabel.h>
#   include <Bibim/IME.h>

    namespace Bibim
    {
        class UIEditText : public UILabel, public IME::Callback
        {
            BBComponentClass(UIEditText, UILabel, 'U', 'E', 'D', 'T');
            public:
                UIEditText();
                virtual ~UIEditText();

                inline IME* GetIME() const;
                void SetIME(IME* value);

                inline IME::TextFormat GetFormat() const;
                void SetFormat(IME::TextFormat value);

                inline const String& GetPlaceholder() const;
                inline void SetPlaceholder(const String& value);

                inline int GetMaxLength() const;
                void SetMaxLength(int value);

                inline bool GetFrozen() const;
                inline void SetFrozen(bool value);

                inline const String& GetEditorTitle() const;
                inline void SetEditorTitle(const String& value);

                inline const String& GetEditorDescription() const;
                inline void SetEditorDescription(const String& value);

            public:
                static IME::TextFormat ConvertFromStringToFormat(const char* value);
                static const char* ConvertFromFormatToString(IME::TextFormat value);

            protected:
                virtual void OnDraw(UIDrawingContext& context);

                virtual bool OnMouseClick(const UIMouseEventArgs& args);

            private:
                virtual void OnTextEdited(const String& text);
                virtual void OnTextEditCancelled();

            private:
                IME* ime;
                IME::TextFormat format;
                String placeholder;
                int maxLength;
                bool frozen;
                String editorTitle;
                String editorDescription;
        };
    }

    BBBindLua(Bibim::UIEditText);
    BBBindLuaEnum(Bibim::IME::TextFormat,
                  Bibim::UIEditText::ConvertFromStringToFormat,
                  Bibim::UIEditText::ConvertFromFormatToString);

#endif