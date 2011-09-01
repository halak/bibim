#pragma once
#ifndef __BIBIM_UIFLOWPANEL_H__
#define __BIBIM_UIFLOWPANEL_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIWindow.h>
#   include <Bibim/UIFrame.h>
#   include <Bibim/UIPickingContext.h>
#   include <Bibim/UIDrawingContext.h>

    namespace Bibim
    {
        class UIFlowPanel : public UIWindow
        {
            public:
                enum Direction
                {
                    LeftToRight = 0x01,
                    RightToLeft = 0x02,
                    TopDown     = 0x04,
                    BottomUp    = 0x08,
                };

            public:
                UIFlowPanel();
                virtual ~UIFlowPanel();

                inline Direction GetDirection() const;
                void SetDirection(Direction value);

            protected:
                class ArrangedFrame : public UIFrame
                {
                    public:
                        Vector2 Offset;
                        Vector2 Size;
                        bool IsNewLine;

                    public:
                        ArrangedFrame();
                        ArrangedFrame(Vector2 offset, Vector2 size, bool isNewLine);
                        virtual ~ArrangedFrame();

                        virtual bool Setup(const RectangleF& bounds, const RectangleF& referenceBounds);
                        virtual RectangleF ComputeBounds(UIVisualVisitor& visitor, Vector2 desiredSize);
                };

        private:
                Direction direction;
        };
    }

#   include <Bibim/UIFlowPanel.inl>

#endif