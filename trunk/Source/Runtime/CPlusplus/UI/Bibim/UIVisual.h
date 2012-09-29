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

                void InsertEffect(UIPixelEffect* item);
                void RemoveEffect(UIPixelEffect* item);
                UIPixelEffect* FindEffect(const String& name);
                inline UIPixelEffect* FindEffectByChars(const char* name);

                void BringToFront();
                void SendToBack();

                void AlignTo(AnchorPoint point);

                void Click();

                inline void SetAbsoluteBounds(int x, int y, int width, int height);
                inline void SetAbsoluteBounds(float x, float y, float width, float height);
                inline void SetRelativeBounds(float x, float y, float width, float height);

                inline float GetX() const;
                inline void  SetX(float value);

                inline float GetY() const;
                inline void  SetY(float value);

                inline void SetXY(float x, float y);

                inline float GetWidth() const;
                inline void  SetWidth(float value);

                inline float GetHeight() const;
                inline void  SetHeight(float value);

                inline void SetSize(float width, float height);

                inline PositionMode GetXMode() const;
                inline void SetXMode(PositionMode value);

                inline PositionMode GetYMode() const;
                inline void SetYMode(PositionMode value);

                inline void SetXYMode(PositionMode xyMode);
                inline void SetXYMode(PositionMode xMode, PositionMode yMode);

                inline SizeMode GetWidthMode() const;
                inline void SetWidthMode(SizeMode value);

                inline SizeMode GetHeightMode() const;
                inline void SetHeightMode(SizeMode value);

                inline void SetSizeMode(SizeMode sizeMode);
                inline void SetSizeMode(SizeMode widthMode, SizeMode heightMode);

                inline Vector2 GetOrigin() const;
                inline void SetOrigin(Vector2 value);

                inline AnchorPoint GetAnchorPoint() const;
                inline void SetAnchorPoint(AnchorPoint value);

                inline float GetOpacity() const;
                void SetOpacity(float value);

                inline Visibility GetVisibility() const;
                inline void SetVisibility(Visibility value);

                inline int GetZOrder() const;
                void SetZOrder(int value);

                inline bool GetPickable() const;
                inline void SetPickable(bool value);

                inline UIEventMap* GetEventMap() const;
                void SetEventMap(UIEventMap* value);

                inline UIEffectMap* GetEffectMap() const;
                void SetEffectMap(UIEffectMap* value);

                inline UITransform* GetTransform() const;
                void SetTransform(UITransform* value);

                inline UIPanel* GetParent() const;

                inline bool IsVisible() const;
                virtual bool IsPanel() const;

                inline void AlignToByChars(const char* value);

                inline const char* GetXModeAsChars() const;
                inline void SetXModeByChars(const char* value);

                inline const char* GetYModeAsChars() const;
                inline void SetYModeByChars(const char* value);

                inline void SetXYModeByChars(const char* xMode, const char* yMode);

                inline const char* GetWidthModeAsChars() const;
                inline void SetWidthModeByChars(const char* value);

                inline const char* GetHeightModeAsChars() const;
                inline void SetHeightModeByChars(const char* value);

                inline void SetSizeModeByChars(const char* widthMode, const char* heightMode);

                inline float GetOriginX() const;
                inline float GetOriginY() const;
                inline void SetOriginXY(float x, float y);

                inline const char* GetAnchorPointAsChars() const;
                inline void SetAnchorPointByChars(const char* value);

                inline const char* GetVisibilityAsChars() const;
                inline void SetVisibilityByChars(const char* value);

            protected:
                virtual Vector2 GetContentSize();

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
                static PositionMode ConvertFromStringToPositionMode(const char* value);
                static const char* ConvertFromPositionModeToString(PositionMode value);
                static SizeMode ConvertFromStringToSizeMode(const char* value);
                static const char* ConvertFromSizeModeToString(SizeMode value);
                static AnchorPoint ConvertFromStringToAnchorPoint(const char* value);
                static const char* ConvertFromAnchorPointToString(AnchorPoint value);
                static Visibility ConvertFromStringToVisibility(const char* value);
                static const char* ConvertFromVisibilityToString(Visibility value);

            private:
                byte xMode;
                byte yMode;
                byte widthMode;
                byte heightMode;
                float x;
                float y;
                float width;
                float height;
                Vector2 origin;
                byte anchorPoint;
                byte opacity;
                byte visibility;
                byte zOrder;
                bool isPickable;
                UIEventMapPtr eventMap;
                UIEffectMapPtr effectMap;
                UITransformPtr transform;
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

	template<> inline void lua_tinker::push(lua_State* L, Bibim::UIVisual* value)
	{
        push(L, static_cast<lua_tinker::lua_value*>(value));
	}

	template<> inline void lua_tinker::push(lua_State* L, const Bibim::UIVisual* value)
	{
        push(L, const_cast<lua_tinker::lua_value*>(static_cast<const lua_tinker::lua_value*>(value)));
	}

#endif