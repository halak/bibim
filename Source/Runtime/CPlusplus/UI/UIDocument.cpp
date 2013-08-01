#include <Bibim/Config.h>
#include <Bibim/UIDocument.h>
#include <Bibim/Assert.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/BitMask.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Font.h>
#include <Bibim/Glyph.h>
#include <Bibim/Image.h>
#include <Bibim/Math.h>
#include <Bibim/UIDrawingContext.h>
#include <Bibim/UIPickingContext.h>
#include <Bibim/UILabel.h>
#include <Bibim/UIImage.h>

namespace Bibim
{
    BBImplementsComponent(UIDocument);

    UIDocument::UIDocument()
        : text(String::Empty),
          stylesheetRevision(-1),
          lastBoundary(-1.0f)
    {
    }

    UIDocument::~UIDocument()
    {
    }

    void UIDocument::SetText(const String& value)
    {
        if (text != value)
        {
            text = value;
            stylesheetRevision = -1;
        }
    }

    void UIDocument::SetStyleSheet(StyleSheet* value)
    {
        if (stylesheet != value)
        {
            stylesheet = value;
            stylesheetRevision = -1;
        }
    }

    Vector2 UIDocument::GetContentSize()
    {
        if (stylesheet)
        {
            ParseAndSetup();
            return contentSize;
        }
        else
            return Vector2::Zero;
    }

    void UIDocument::OnPick(UIPickingContext& context)
    {
        if (GetPickable() && context.Contains(context.GetCurrentClippedBounds()))
            context.SetResult(this);
    }

    void UIDocument::OnDraw(UIDrawingContext& context)
    {
        if (stylesheet == nullptr || text.IsEmpty())
            return;

        ParseAndSetup();

        const float boundary = context.GetCurrentBounds().Width;
        if (boundary != lastBoundary)
        {
            PerformLayout(boundary);
            lastBoundary = boundary;
        }

        DrawChildren(context);
    }

    namespace
    {
        static int GetTerminateCharacter(int c)
        {
            switch (c)
            {
                case '[': return ']';
                case '<': return '>';
                case '(': return ')';
                default:  return '\0';
            }
        }

        static bool AdvanceToTerminate(String::UTF8CharEnumerator& en, int c)
        {
            while (en.MoveNext())
            {
                if (en.GetCurrent() == c &&
                    en.MoveNext() &&
                    en.GetCurrent() == c)
                    return true;
            }

            return false;
        }

        static int SkipWhiteSpaceAndNewLine(String::UTF8CharEnumerator& en, Font* font)
        {
            int spaces = 0;
            int newLines = 0;

            const char* s = en.GetBuffer();
            const int index = en.GetCurrentIndex();
            for (int i = index; String::IsWhiteSpace(s[i]); i++)
            {
                if (s[i] == '\n')
                    newLines++;
                else
                    spaces++;
            }

            const int total = newLines + spaces;
            for (int i = 0; i < total - 1; i++)
            {
                if (en.MoveNext() == false)
                    break;

                BBAssertDebug(String::IsWhiteSpace(en.GetCurrent()));
            }

            if (newLines > 0)
                return static_cast<int>(-(newLines * font->GetLineHeight()));
            else
                return static_cast<int>(static_cast<float>(spaces) * font->GetRegularGlyph(' ')->GetAdvance().X * font->GetSpacing());
        }
    }

    void UIDocument::ParseAndSetup()
    {
        if (stylesheetRevision == stylesheet->GetRevision())
            return;

        RemoveAll();
        afterSpaces.clear();
        ascenders.clear();

        if (text.IsEmpty())
            return;

        stylesheetRevision = stylesheet->GetRevision();
        lastBoundary = -1.0f; // invalid value

        std::stack<Font*> fontStack;
        if (const StyleSheet::Decoration* decoration = stylesheet->GetDecoration(String::Empty))
            fontStack.push(decoration->GetFont());
        else
            return;

        int textIndex = 0;
        String::UTF8CharEnumerator en(text);
        while (en.MoveNext())
        {
            const int current = en.GetCurrent();
            const int startIndex = en.GetCurrentIndex();
            if (current == '[' ||
                current == '(' ||
                current == '<')
            {
                if (en.MoveNext() == false)
                    break;
                if (current != en.GetCurrent())
                    continue;

                // 특수 문자들을 만나기 전 문자열을 일단 추가합니다.
                if (startIndex != textIndex)
                {
                    AddText(text.Substring(textIndex, startIndex - textIndex), fontStack.top());
                    afterSpaces.push_back(0);
                }
                
                if (AdvanceToTerminate(en, GetTerminateCharacter(current)))
                {
                    const int terminateIndex = en.GetCurrentIndex();
                    const char* name = &text.CStr()[startIndex + 2];
                    const int nameLength = terminateIndex - startIndex - 3;
                
                    switch (current)
                    {
                        case '[':
                            ProcessDecoration(name, nameLength, fontStack);
                            break;
                        case '(':
                            if (UIVisual* visual = ProcessContent(name, nameLength))
                            {
                                Add(visual);
                                afterSpaces.push_back(0);
                                ascenders.push_back(0.0f);
                            }
                            break;
                        case '<':
                            break;
                    }
                
                    textIndex = terminateIndex + 1;
                }
            }
            else if (String::IsWhiteSpace(current))
            {
                if (startIndex != textIndex)
                {
                    AddText(text.Substring(textIndex, startIndex - textIndex), fontStack.top());
                    afterSpaces.push_back(SkipWhiteSpaceAndNewLine(en, fontStack.top()));
                    textIndex = en.GetCurrentIndex() + 1;
                }
            }
        }

        AddText(text.Substring(textIndex), fontStack.top());
        afterSpaces.push_back(0);

        BBAssertDebug(GetNumberOfChildren() == static_cast<int>(afterSpaces.size()));
    }

    void UIDocument::PerformLayout(float boundary)
    {
        yPositionOfLines.clear();
        yPositionOfLines.push_back(0);
        firstChildIndexOnLine.clear();
        firstChildIndexOnLine.push_back(0);

        std::vector<UIVisual*> line;
        float maxLineHeight = 0.0f;
        float maxAscender = 0.0f;

        BBAssertDebug(GetNumberOfChildren() == static_cast<int>(afterSpaces.size()));

        Vector2 position = Vector2::Zero;
        const VisualCollection& children = GetChildren();
        const int count = static_cast<int>(children.size());
        for (int i = 0; i < count; i++)
        {
            UIVisual* current = children[i];
            int afterSpace = afterSpaces[i];
            const Vector2 contentSize = current->GetContentSize();

            if (position.X + contentSize.X >= boundary)
            {
                for (std::vector<UIVisual*>::const_iterator it = line.begin(); it != line.end(); it++)
                {
                    if ((*it)->GetClassID() == UILabel::ClassID)
                    {
                        UILabel* label = static_cast<UILabel*>(*it);
                        (*it)->SetY(position.Y + maxAscender - label->GetFont()->GetAscender());
                    }
                    else
                    {
                        (*it)->SetY(position.Y + maxLineHeight - (*it)->GetContentHeight());
                    }
                }

                position.X = 0.0f;
                position.Y += maxLineHeight;

                line.clear();
                maxLineHeight = 0.0f;
                maxAscender = 0.0f;
            }

            current->SetX(position.X);
            position.X += contentSize.X;
            if (afterSpace > 0)
                position.X += static_cast<float>(afterSpace);
            maxLineHeight = Math::Max(maxLineHeight, contentSize.Y);
            maxAscender   = Math::Max(maxAscender,   ascenders[i]);

            line.push_back(current);

            if (afterSpace < 0)
                position.X = boundary;
        }

        for (std::vector<UIVisual*>::const_iterator it = line.begin(); it != line.end(); it++)
        {
            if ((*it)->GetClassID() == UILabel::ClassID)
            {
                UILabel* label = static_cast<UILabel*>(*it);
                (*it)->SetY(position.Y + maxAscender - label->GetFont()->GetAscender());
            }
            else
            {
                (*it)->SetY(position.Y + maxLineHeight - (*it)->GetContentHeight());
            }
        }
    }

    void UIDocument::AddText(const String& text, Font* font)
    {
        UILabel* label = new UILabel();
        label->SetXYMode(UIVisual::AbsolutePosition);
        label->SetSize(1.0f, 1.0f);
        label->SetSizeMode(UIVisual::ContentSize);
        label->SetPickable(false);
        label->SetText(text);
        label->SetFont(font);
        Add(label);
        ascenders.push_back(font->GetAscender());
    }

    void UIDocument::ProcessDecoration(const char* name, int length, std::stack<Font*>& fontStack)
    {
        // '/'가 포함되어 있으면 무조건 닫는 구문이라고 가정합니다.
        int closeCount = 0;
        for (int i = 0; i < length; i++)
        {
            if (name[i] == '/')
                closeCount++;
        }

        if (closeCount > 0)
        {
            closeCount = Math::Min(closeCount, fontStack.size() - 1);
            for (int i = 0; i < closeCount; i++)
                fontStack.pop();
        }
        else
        {
            if (const StyleSheet::Decoration* decoration = stylesheet->GetDecoration(String(name, 0, length)))
                fontStack.push(decoration->GetFont());
            else
                fontStack.push(fontStack.top());
        }
    }

    UIVisual* UIDocument::ProcessContent(const char* name, int length)
    {
        String trimmedName = String(name, 0, length);
        trimmedName.Trim();

        if (const StyleSheet::Content* content = stylesheet->GetContent(trimmedName))
        {
            if (Image* source = content->GetImage())
            {
                UIImage* image = new UIImage();
                image->SetXYMode(UIVisual::AbsolutePosition);
                image->SetSize(1.0f, 1.0f);
                image->SetSizeMode(UIVisual::ContentSize);
                image->SetPickable(false);
                image->SetSource(source);
                return image;
            }
        }

        return nullptr;
    }

    void UIDocument::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        // NOT IMPLEMENTED
        // stylesheet = static_cast<StyleSheet*>(reader.ReadAsset());
        text = reader.ReadString();
        stylesheetRevision = -1;
    }

    void UIDocument::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        text = o->text;
        stylesheet = o->stylesheet;
        contentSize = o->contentSize;
        stylesheetRevision = -1;
    }

    /*
    void UIDocument::UpdateLayout()
    {
        RemoveAllChildren();

        if (font == nullptr)
            return;

        typedef UIMarkupText::Phrase Phrase;
        typedef UIMarkupText::TextPhrase TextPhrase;
        typedef UIMarkupText::NewLinePhrase NewLinePhrase;
        typedef UIMarkupText::ColorPhrase ColorPhrase;
        typedef UIMarkupText::FontPhrase FontPhrase;
        typedef UIMarkupText::ContentPhrase ContentPhrase;
        typedef UIMarkupText::PhraseCollection PhraseCollection;

        bool isNewLine = false;
        FontPtr currentFont = font;

        const PhraseCollection& phrases = text.GetPhrases();
        for (PhraseCollection::const_iterator it = phrases.begin(); it != phrases.end(); it++)
        {
            switch ((*it)->GetType())
            {
                case UIMarkupText::TextPhraseType:
                    {
                        const TextPhrase* item = static_cast<const TextPhrase*>(*it);
                        const String subText = text.GetOriginalText().Substring(item->GetIndex(), item->GetLength());

                        UILabelPtr child = new UILabel();
                        child->SetFrame(new ArrangedFrame(Vector2::Zero, currentFont->Measure(subText), isNewLine));
                        child->SetFont(currentFont);
                        child->SetText(subText);
                        AddChild(child);
                        isNewLine = false;
                    }
                    break;
                case UIMarkupText::NewLinePhraseType:
                    isNewLine = true;
                    break;
                case UIMarkupText::ColorPhraseType:
                    {
                        const ColorPhrase* item = static_cast<const ColorPhrase*>(*it);

                        Color color;
                        if (item->HasColor())
                            color = item->GetColor();
                        else
                            color = font->GetColor();

                        if (color != currentFont->GetColor())
                        {
                            currentFont = new Font(*currentFont);
                            currentFont->SetColor(color);
                        }
                    }
                    break;
                case UIMarkupText::FontPhraseType:
                    {
                        // const FontPhrase* item = static_cast<const FontPhrase*>(*it);
                    }
                    break;
                case UIMarkupText::ContentPhraseType:
                    {
                        // const ContentPhrase* item = static_cast<const ContentPhrase*>(*it);
                    }
                    break;
            }
        }
    }
    */

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIDocument::StyleSheet::Content::Content()
    {
    }

    UIDocument::StyleSheet::Content::Content(Image* image, Vector2 origin)
        : asset(image),
          origin(origin)
    {
    }

    Image* UIDocument::StyleSheet::Content::GetImage() const
    {
        if (asset && asset->GetClassID() == Image::ClassID)
            return static_cast<Image*>(asset.GetPointee());
        else
            return nullptr;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIDocument::StyleSheet::Decoration::Decoration()
    {
    }

    UIDocument::StyleSheet::Decoration::Decoration(Font* font)
        : font(font)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIDocument::StyleSheet::StyleSheet()
    {
    }

    UIDocument::StyleSheet::~StyleSheet()
    {
        Clear();
    }

    void UIDocument::StyleSheet::Clear()
    {
        contents.clear();
        decorations.clear();
        IncreaseRevision();
    }

    void UIDocument::StyleSheet::AddContent(const String& name, Image* image, Vector2 origin)
    {
        if (image == nullptr || name.IsEmpty())
            return;

        contents[name] = Content(image, origin);
        IncreaseRevision();
    }

    void UIDocument::StyleSheet::RemoveContent(const String& name)
    {
        std::map<String, Content>::iterator it = contents.find(name);
        if (it != contents.end())
        {
            contents.erase(it);
            IncreaseRevision();
        }
    }

    void UIDocument::StyleSheet::AddDecoration(const String& name, Font* font)
    {
        if (font == nullptr)
            return;

        decorations[name] = Decoration(font);
        IncreaseRevision();
    }

    void UIDocument::StyleSheet::RemoveDecoration(const String& name)
    {
        std::map<String, Decoration>::iterator it = decorations.find(name);
        if (it != decorations.end())
        {
            decorations.erase(it);
            IncreaseRevision();
        }
    }

    GameAsset* UIDocument::StyleSheet::Create(StreamReader& reader, GameAsset* existingInstance)
    {
        StyleSheet* result = nullptr;
        
        if (existingInstance)
        {
            result = static_cast<StyleSheet*>(existingInstance);
            result->Clear();
        }
        else
            result = new StyleSheet();

        result->SetStatus(GameAsset::LoadingStatus);
        // NOT IMPLEMENTED
        BBBreak();
        /*
        result->cache.Reset();
        result->library = static_cast<FontLibrary*>(reader.ReadModule(FontLibrary::ClassID));
        result->parameters.FaceURI = reader.ReadString();
        result->parameters.FontSize = reader.ReadFloat();
        result->parameters.StrokeSize = reader.ReadFloat();
        result->parameters.Weights = reader.ReadFloat();
        result->parameters.Shear = reader.ReadFloat();
        result->parameters.ShadowSize = reader.ReadInt();
        result->parameters.ShadowSpread = reader.ReadFloat();
        result->parameters.ShadowThickness = reader.ReadFloat();
        result->shadowOffset = reader.ReadVector2();
        result->parameters.Scale = reader.ReadFloat();
        result->parameters.Hinting = reader.ReadBool();
        result->parameters.IgnoreBitmap = reader.ReadBool();
        result->spacing = reader.ReadFloat();
        result->color = reader.ReadColor();
        result->strokeColor = reader.ReadColor();
        result->shadowColor = reader.ReadColor();
        result->IncreaseRevision();
        */
        result->SetStatus(GameAsset::CompletedStatus);

        return result;
    }
}