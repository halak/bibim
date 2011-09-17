//#include <Bibim/PCH.h>
//#include <Bibim/UIMarkupTextBox.h>
//#include <Bibim/Font.h>
//#include <Bibim/UILabel.h>
//#include <Bibim/UISprite.h>
//
//namespace Bibim
//{
//    UIMarkupTextBox::UIMarkupTextBox()
//        : text(UIMarkupText::Empty),
//          font(nullptr)
//    {
//    }
//
//    UIMarkupTextBox::~UIMarkupTextBox()
//    {
//    }
//
//    void UIMarkupTextBox::SetText(const UIMarkupText& value)
//    {
//        if (text != value)
//        {
//            text = value;
//            UpdateLayout();
//        }
//    }
//
//    void UIMarkupTextBox::SetFont(Font* value)
//    {
//        if (font != value)
//        {
//            font = value;
//            UpdateLayout();
//        }
//    }
//
//    void UIMarkupTextBox::UpdateLayout()
//    {
//        RemoveAllChildren();
//
//        if (font == nullptr)
//            return;
//
//        typedef UIMarkupText::Phrase Phrase;
//        typedef UIMarkupText::TextPhrase TextPhrase;
//        typedef UIMarkupText::NewLinePhrase NewLinePhrase;
//        typedef UIMarkupText::ColorPhrase ColorPhrase;
//        typedef UIMarkupText::FontPhrase FontPhrase;
//        typedef UIMarkupText::ContentPhrase ContentPhrase;
//        typedef UIMarkupText::PhraseCollection PhraseCollection;
//
//        bool isNewLine = false;
//        FontPtr currentFont = font;
//
//        const PhraseCollection& phrases = text.GetPhrases();
//        for (PhraseCollection::const_iterator it = phrases.begin(); it != phrases.end(); it++)
//        {
//            switch ((*it)->GetType())
//            {
//                case UIMarkupText::TextPhraseType:
//                    {
//                        const TextPhrase* item = static_cast<const TextPhrase*>(*it);
//                        const String subText = text.GetOriginalText().Substring(item->GetIndex(), item->GetLength());
//
//                        UILabelPtr child = new UILabel();
//                        child->SetFrame(new ArrangedFrame(Vector2::Zero, currentFont->Measure(subText), isNewLine));
//                        child->SetFont(currentFont);
//                        child->SetText(subText);
//                        AddChild(child);
//                        isNewLine = false;
//                    }
//                    break;
//                case UIMarkupText::NewLinePhraseType:
//                    isNewLine = true;
//                    break;
//                case UIMarkupText::ColorPhraseType:
//                    {
//                        const ColorPhrase* item = static_cast<const ColorPhrase*>(*it);
//
//                        Color color;
//                        if (item->HasColor())
//                            color = item->GetColor();
//                        else
//                            color = font->GetColor();
//
//                        if (color != currentFont->GetColor())
//                        {
//                            currentFont = new Font(*currentFont);
//                            currentFont->SetColor(color);
//                        }
//                    }
//                    break;
//                case UIMarkupText::FontPhraseType:
//                    {
//                        // const FontPhrase* item = static_cast<const FontPhrase*>(*it);
//                    }
//                    break;
//                case UIMarkupText::ContentPhraseType:
//                    {
//                        // const ContentPhrase* item = static_cast<const ContentPhrase*>(*it);
//                    }
//                    break;
//            }
//        }
//    }
//}