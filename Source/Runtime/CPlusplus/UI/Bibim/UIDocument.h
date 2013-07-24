#pragma once
#ifndef __BIBIM_UIDOCUMENT_H__
#define __BIBIM_UIDOCUMENT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIPanel.h>
#   include <Bibim/GameAsset.h>
#   include <map>
#   include <stack>
#   include <vector>

    namespace Bibim
    {
        // 문자 중간 중간 글꼴을 바꾸거나 이미지를 삽입할 수 있는 Visual.
        // 대량의 문자열을 그리는데 최적화 되어 있습니다.
        // * 문법
        //     [[font-style-name]] ... [[/]]
        //     ((image-name))
        //     <<link>> ... <</>>
        // 닫기 명령인 [[/]], <</>>은 중첩해서 사용가능합니다.
        //     {{///}} : 3단계 닫기
        //     <<//>> : 2단게 닫기
        // TODO: 리펙토링 여지가 많이 남아있습니다.
        //     문자열을 그릴 때 clippedBounds에 따라서 가리는 문자 처음부터 스킵하기.
        //     <<link>> 구현
        class UIDocument : public UIPanel
        {
            BBComponentClass(UIDocument, UIPanel, 'U', 'D', 'O', 'C');
            public:
                BBForwardDeclareSmartPointerClass(StyleSheet);
                class StyleSheet : public GameAsset
                {
                    BBSerializableAssetClass(StyleSheet, GameAsset, 'U', 'D', 'S', 'S');
                    public:
                        class Content
                        {
                            public:
                                Content();
                                Content(Image* image, Vector2 origin);
                                inline ~Content();

                                Image* GetImage() const;
                                inline Vector2 GetOrigin() const;
                            
                            private:
                                GameAssetPtr asset;
                                Vector2 origin;
                        };

                        class Decoration
                        {
                            public:
                                Decoration();
                                explicit Decoration(Font* font);
                                inline ~Decoration();

                                inline Font* GetFont() const;

                            private:
                                FontPtr font;
                        };

                    public:
                        StyleSheet();
                        virtual ~StyleSheet();

                        void Clear();

                        inline void AddContent(const String& name, Image* image);
                        void AddContent(const String& name, Image* image, Vector2 origin);
                        void RemoveContent(const String& name);

                        void AddDecoration(const String& name, Font* font);
                        void RemoveDecoration(const String& name);

                        inline const Content* GetContent(const String& name) const;
                        inline const Decoration* GetDecoration(const String& name) const;

                        inline void AddContentXY(const String& name, Image* image, float originX, float originY);

                    private:
                        std::map<String, Content> contents;
                        std::map<String, Decoration> decorations;
                };

            public:
                UIDocument();
                virtual ~UIDocument();

                inline const String& GetText() const;
                void SetText(const String& value);

                inline StyleSheet* GetStyleSheet() const;
                void SetStyleSheet(StyleSheet* value);

                virtual Vector2 GetContentSize();

            protected:
                virtual void OnPick(UIPickingContext& context);
                virtual void OnDraw(UIDrawingContext& context);

            private:
                void ParseAndSetup();
                void PerformLayout(float boundary);
                void AddText(const String& text, Font* font);
                void ProcessDecoration(const char* name, int length, std::stack<Font*>& fontStack);
                UIVisual* ProcessContent(const char* name, int length);

            private:
                String text;
                StyleSheetPtr stylesheet;
                int stylesheetRevision;
                Vector2 contentSize;
                float lastBoundary;

                std::vector<int> afterSpaces; // Child별 다음에 나오는 공백 수 (음수면 개행 수)
                std::vector<float> ascenders; // Child별 Ascender 값
                std::vector<int> yPositionOfLines; // 행별 Y위치
                std::vector<int> firstChildIndexOnLine; // 행별 첫번째 Child의 색인
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        const String& UIDocument::GetText() const
        {
            return text;
        }

        UIDocument::StyleSheet* UIDocument::GetStyleSheet() const
        {
            return stylesheet;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        UIDocument::StyleSheet::Content::~Content()
        {
        }

        Vector2 UIDocument::StyleSheet::Content::GetOrigin() const
        {
            return origin;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        UIDocument::StyleSheet::Decoration::~Decoration()
        {
        }

        Font* UIDocument::StyleSheet::Decoration::GetFont() const
        {
            return font;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void UIDocument::StyleSheet::AddContent(const String& name, Image* image)
        {
            AddContent(name, image, Vector2(0.5f, 0.5f));
        }

        void UIDocument::StyleSheet::AddContentXY(const String& name, Image* image, float originX, float originY)
        {
            AddContent(name, image, Vector2(originX, originY));
        }

        const UIDocument::StyleSheet::Content* UIDocument::StyleSheet::GetContent(const String& name) const
        {
            std::map<String, Content>::const_iterator it = contents.find(name);
            if (it != contents.end())
                return &(*it).second;
            else
                return nullptr;
        }

        const UIDocument::StyleSheet::Decoration* UIDocument::StyleSheet::GetDecoration(const String& name) const
        {
            std::map<String, Decoration>::const_iterator it = decorations.find(name);
            if (it != decorations.end())
                return &(*it).second;
            else
                return nullptr;
        }
    }

#endif