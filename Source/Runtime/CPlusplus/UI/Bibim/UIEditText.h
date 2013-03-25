#pragma once
#ifndef __BIBIM_UIEDITEXT_H__
#define __BIBIM_UIEDITEXT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UILabel.h>

    namespace Bibim
    {
        class UIEditText : public UILabel
        {
            BBComponentClass(UIEditText, UILabel, 'U', 'E', 'D', 'T');
            public:
                enum Format
                {
                    Default,
                    Number,
                    Alphabet,
                    AlphabetNumber,
                };

            public:
                UIEditText();
                virtual ~UIEditText();

                inline Format GetFormat() const;
                void SetFormat(Format value);

                inline bool GetFrozen() const;
                inline void SetFrozen(bool value);

            protected:
                virtual bool OnMouseClick(const UIMouseEventArgs& args);

            private:
                Format format;
                bool frozen;
        };
    }

#   include <Bibim/UIEditText.inl>

#endif