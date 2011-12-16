#pragma once
#ifndef __BIBIM_UIVISUAL_H__
#define __BIBIM_UIVISUAL_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIElement.h>
#   include <Bibim/Vector2.h>

    namespace Bibim
    {
        class UIVisual : public UIElement
        {
            BBAbstractComponentClass(UIVisual, UIElement);
            public:
                enum PositionMode
                {
                    AbsolutePosition,
                    RelativePosition,
                    UndefinedPosition,
                };

                enum SizeMode
                {
                    AbsoluteSize,
                    RelativeSize,
                    ContentSize,
                };

                enum AnchorPoint
                {
                    LeftTop,
                    LeftBottom,
                    LeftMiddle,
                    RightTop,
                    RightBottom,
                    RightMiddle,
                    CenterTop,
                    CenterBottom,
                    Center,
                };

                enum Visibility
                {
                    Visible,
                    Invisible,
                    Collasped,
                };


            public:
                UIVisual();
                virtual ~UIVisual();

                RectF ComputeBounds(UIVisualVisitor& context);

                inline void Show();
                inline void Hide();

                void BringToFront();
                void SendToBack();

                inline void SetAbsoluteBounds(int x, int y, int width, int height);
                inline void SetAbsoluteBounds(float x, float y, float width, float height);
                inline void SetRelativeBounds(float x, float y, float width, float height);

                inline float GetX() const;
                inline void  SetX(float value);

                inline float GetY() const;
                inline void  SetY(float value);

                inline float GetWidth() const;
                inline void  SetWidth(float value);

                inline float GetHeight() const;
                inline void  SetHeight(float value);

                inline PositionMode GetXMode() const;
                inline void SetXMode(PositionMode value);

                inline PositionMode GetYMode() const;
                inline void SetYMode(PositionMode value);

                inline SizeMode GetWidthMode() const;
                inline void SetWidthMode(SizeMode value);

                inline SizeMode GetHeightMode() const;
                inline void SetHeightMode(SizeMode value);

                inline AnchorPoint GetAlignment() const;
                inline void SetAlignment(AnchorPoint value);

                inline float GetOpacity() const;
                void SetOpacity(float value);

                inline Visibility GetVisibility() const;
                inline void SetVisibility(Visibility value);

                inline int GetZOrder() const;
                void SetZOrder(int value);

                inline UIEventMap* GetEventMap() const;
                void SetEventMap(UIEventMap* value);

                inline UIEffectMap* GetEffectMap() const;
                void SetEffectMap(UIEffectMap* value);

                inline UIPanel* GetParent() const;

                inline bool IsVisible() const;
                virtual bool IsPanel() const;

            protected:
                virtual void OnDraw(UIDrawingContext& context);
                virtual void OnPick(UIPickingContext& context);

                virtual void OnParentChanged(UIPanel* old);

                virtual bool OnKeyDown(const UIKeyboardEventArgs& args);
                virtual bool OnKeyUp(const UIKeyboardEventArgs& args);
                virtual bool OnKeyPressing(const UIKeyboardEventArgs& args);
                virtual void OnMouseEnter(const UIMouseEventArgs& args);
                virtual void OnMouseLeave(const UIMouseEventArgs& args);
                virtual bool OnMouseMove(const UIMouseEventArgs& args);
                virtual bool OnMouseClick(const UIMouseEventArgs& args);
                virtual bool OnMouseButtonDown(const UIMouseButtonEventArgs& args);
                virtual bool OnMouseButtonUp(const UIMouseButtonEventArgs& args);
                virtual bool OnMouseButtonPressing(const UIMouseButtonEventArgs& args);
                virtual bool OnMouseWheel(const UIMouseWheelEventArgs& args);
                virtual bool OnGamePadButtonDown(const UIGamePadEventArgs& args);
                virtual bool OnGamePadButtonUp(const UIGamePadEventArgs& args);
                virtual bool OnGamePadButtonPressing(const UIGamePadEventArgs& args);
                virtual bool OnGamePadTrigger(const UIGamePadEventArgs& args);
                virtual bool OnGamePadThumbstick(const UIGamePadEventArgs& args);

            private:
                inline void SetBounds(float x, float y, float width, float height);

                void SetParent(UIPanel* value);

                void RaiseKeyDownEvent(const UIKeyboardEventArgs& args);
                void RaiseKeyUpEvent(const UIKeyboardEventArgs& args);
                void RaiseKeyPressingEvent(const UIKeyboardEventArgs& args);
                void RaiseMouseEnterEvent(const UIMouseEventArgs& args);
                void RaiseMouseLeaveEvent(const UIMouseEventArgs& args);
                void RaiseMouseMoveEvent(const UIMouseEventArgs& args);
                void RaiseMouseClickEvent(const UIMouseEventArgs& args);
                void RaiseMouseButtonDownEvent(const UIMouseButtonEventArgs& args);
                void RaiseMouseButtonUpEvent(const UIMouseButtonEventArgs& args);
                void RaiseMouseButtonPressingEvent(const UIMouseButtonEventArgs& args);
                void RaiseMouseWheelEvent(const UIMouseWheelEventArgs& args);
                void RaiseGamePadButtonDownEvent(const UIGamePadEventArgs& args);
                void RaiseGamePadButtonUpEvent(const UIGamePadEventArgs& args);
                void RaiseGamePadButtonPressingEvent(const UIGamePadEventArgs& args);
                void RaiseGamePadTriggerEvent(const UIGamePadEventArgs& args);
                void RaiseGamePadThumbstickEvent(const UIGamePadEventArgs& args);

            private:
                byte xMode;
                byte yMode;
                byte widthMode;
                byte heightMode;
                float x;
                float y;
                float width;
                float height;
                byte alignment;
                byte opacity;
                byte visibility;
                byte zOrder;
                UIEventMapPtr eventMap;
                UIEffectMapPtr effectMap;
                UIPanel* parent;

                friend class UIDrawingContext;
                friend class UIPickingContext;
                friend class UIKeyboardEventDispatcher;
                friend class UIMouseEventDispatcher;
                friend class UIGamdPadEventDispatcher;
                friend class UITouchEventDispatcher;
                friend class UIPanel;
        };
    }

#   include <Bibim/UIVisual.inl>

#endif