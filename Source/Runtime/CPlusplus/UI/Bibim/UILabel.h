#pragma once
#ifndef __BIBIM_UILABEL_H__
#define __BIBIM_UILABEL_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIVisual.h>
#   include <Bibim/FontString.h>

    namespace Bibim
    {
        class UILabel : public UIVisual
        {
            BBUIElementClass('U', 'L', 'B', 'L');
            public:
                UILabel();
                virtual ~UILabel();

                inline const String& GetText() const;
                void SetText(const String& value);

                inline Font* GetFont() const;
                void SetFont(Font* value);

                inline bool GetAutoResize() const;
                void SetAutoResize(bool value);

            protected:
                virtual void OnDraw(UIDrawingContext& context);

            private:
                String text;
                FontPtr font;
                FontString fontString;
                bool fontStringChanged;
                bool autoResize;
        };
    }

#   include <Bibim/UILabel.inl>

#endif