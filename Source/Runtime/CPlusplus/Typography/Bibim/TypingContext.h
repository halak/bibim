﻿#pragma once
#ifndef __BIBIM_TYPINGCONTEXT_H__
#define __BIBIM_TYPINGCONTEXT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Glyph.h>
#   include <Bibim/Vector2.h>
#   include <vector>

    namespace Bibim
    {
        class TypingContext
        {
            BBThisIsNoncopyableClass(TypingContext);
            public:
                TypingContext(Font* font, const String& text, float boundary);
                TypingContext(const FontString& string, float boundary);
                ~TypingContext();

                void Reset();
                bool MoveNext();

                inline int GetCode() const;
                inline Vector2 GetPosition() const;
                inline const Glyph* GetRegularGlyph() const;
                inline const Glyph* GetStrokedGlyph() const;
                inline int GetIndex() const;
                inline int GetGlyphIndex() const;
                inline int GetLineNumber() const;

            private:
                static inline int GetLength(int code);

            private:
                const FontString* fontString;
                bool fontStringLocalAllocated;

                float boundary;

                Vector2 currentPosition;
                const Glyph* currentGlyph;
                const Glyph* currentStrokedGlyph;
                int currentIndex;
                int currentIndexFromOriginalText;
                int lineNumber;
        };
    }

#endif