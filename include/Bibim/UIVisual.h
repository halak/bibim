#pragma once
#ifndef __BIBIM_UIVISUAL_H__
#define __BIBIM_UIVISUAL_H__

#include <Bibim/FWD.h>
#include <Bibim/UIElement.h>
#include <Bibim/Vector2.h>

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
                AdjustiveSize,
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

            class DestructionListener
            {
                public:
                    virtual ~DestructionListener() { }

                    virtual void OnVisualDestruected(UIVisual* visual) = 0;
            };

        public:
            UIVisual();
            virtual ~UIVisual();

            RectF ComputeBounds(UIVisualVisitor& context);

            inline void Show();
            inline void Hide();

            UIGeometryEffect* GetGeometryEffect() const;
            void SetGeometryEffect(UIGeometryEffect* value);

            void InsertEffect(UIPixelEffect* item);
            void RemoveEffect(UIPixelEffect* item);
            UIPixelEffect* FindEffect(const String& name);

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

            inline Vector2 GetXY() const;
            inline void SetXY(float x, float y);

            inline float GetWidth() const;
            inline void  SetWidth(float value);

            inline float GetHeight() const;
            inline void  SetHeight(float value);

            inline Vector2 GetSize() const;
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

            virtual Vector2 GetContentSize();
            inline float GetContentWidth();
            inline float GetContentHeight();

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

            inline bool GetFocusable() const;
            inline void SetFocusable(bool value);

            inline bool GetDraggable() const;
            inline void SetDraggable(bool value);

            inline UIEventMap* GetEventMap() const;
            void SetEventMap(UIEventMap* value);

            inline UIEffectMap* GetEffectMap() const;
            void SetEffectMap(UIEffectMap* value);

            inline UITransform* GetTransform() const;
            void SetTransform(UITransform* value);

            inline UIPanel* GetParent() const;

            inline bool IsVisible() const;
            inline bool IsFocused() const;
            virtual bool IsPanel() const;
            virtual bool IsWindow() const;

            inline void SetXYModeByChars(const char* xMode, const char* yMode);
            inline void SetSizeModeByChars(const char* widthMode, const char* heightMode);

            inline void SetOriginXY(float x, float y);

        public:
            static PositionMode ConvertFromStringToPositionMode(const char* value);
            static const char* ConvertFromPositionModeToString(PositionMode value);
            static SizeMode ConvertFromStringToSizeMode(const char* value);
            static const char* ConvertFromSizeModeToString(SizeMode value);
            static AnchorPoint ConvertFromStringToAnchorPoint(const char* value);
            static const char* ConvertFromAnchorPointToString(AnchorPoint value);
            static Visibility ConvertFromStringToVisibility(const char* value);
            static const char* ConvertFromVisibilityToString(Visibility value);

        protected:
            virtual void OnDraw(UIDrawingContext& context);
            virtual void OnPick(UIPickingContext& context);

            virtual void OnFocused();
            virtual void OnBlured();
            virtual void OnDragBegan();
            virtual void OnDragEnded();
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

            void Focus(UIDomain* value);
            void Drag(UIDomain* value);
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
            void RaiseFocusedEvent(const UIEventArgs& args);
            void RaiseBluredEvent(const UIEventArgs& args);

        private:
            static const byte PICKALBE_BITFIELD  = (1<<0);
            static const byte FOCUSABLE_BITFIELD = (1<<1);
            static const byte DRAGGABLE_BITFIELD = (1<<2);
            static const byte DEFAULT_FLAGS = PICKALBE_BITFIELD;

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
            byte flags;
            UIEventMapPtr eventMap;
            UIEffectMapPtr effectMap;
            UITransformPtr transform;
            UIPanel* parent;
            UIDomain* focuser;

            friend class UIDrawingContext;
            friend class UIPickingContext;
            friend class UIKeyboardEventDispatcher;
            friend class UIMouseEventDispatcher;
            friend class UIGamdPadEventDispatcher;
            friend class UITouchEventDispatcher;
            friend class UIPanel;
            friend class UIDomain;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    void UIVisual::Show()
    {
        SetVisibility(Visible);
    }

    void UIVisual::Hide()
    {
        SetVisibility(Collasped);
    }

    void UIVisual::SetBounds(float x, float y, float width, float height)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }

    void UIVisual::SetAbsoluteBounds(int x, int y, int width, int height)
    {
        SetAbsoluteBounds(static_cast<float>(x),
                          static_cast<float>(y),
                          static_cast<float>(width),
                          static_cast<float>(height));
    }

    void UIVisual::SetAbsoluteBounds(float x, float y, float width, float height)
    {
        SetBounds(x, y, width, height);
        xMode = AbsolutePosition;
        yMode = AbsolutePosition;
        widthMode  = AbsoluteSize;
        heightMode = AbsoluteSize;
    }

    void UIVisual::SetRelativeBounds(float x, float y, float width, float height)
    {
        SetBounds(x, y, width, height);
        xMode = RelativePosition;
        yMode = RelativePosition;
        widthMode  = RelativeSize;
        heightMode = RelativeSize;
    }

    float UIVisual::GetX() const
    {
        return x;
    }

    void UIVisual::SetX(float value)
    {
        x = value;
    }

    float UIVisual::GetY() const
    {
        return y;
    }

    void UIVisual::SetY(float value)
    {
        y = value;
    }

    Vector2 UIVisual::GetXY() const
    {
        return Vector2(x, y);
    }

    void UIVisual::SetXY(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    float UIVisual::GetWidth() const
    {
        return width;
    }

    void UIVisual::SetWidth(float value)
    {
        width = value;
    }

    float UIVisual::GetHeight() const
    {
        return height;
    }

    void UIVisual::SetHeight(float value)
    {
        height = value;
    }

    Vector2 UIVisual::GetSize() const
    {
        return Vector2(width, height);
    }

    void UIVisual::SetSize(float width, float height)
    {
        SetWidth(width);
        SetHeight(height);
    }

    UIVisual::PositionMode UIVisual::GetXMode() const
    {
        return static_cast<PositionMode>(xMode);
    }

    void UIVisual::SetXMode(PositionMode value)
    {
        xMode = static_cast<byte>(value);
    }

    UIVisual::PositionMode UIVisual::GetYMode() const
    {
        return static_cast<PositionMode>(yMode);
    }

    void UIVisual::SetYMode(PositionMode value)
    {
        yMode = static_cast<byte>(value);
    }

    void UIVisual::SetXYMode(PositionMode xyMode)
    {
        this->xMode = static_cast<byte>(xyMode);
        this->yMode = this->xMode;
    }

    void UIVisual::SetXYMode(PositionMode xMode, PositionMode yMode)
    {
        this->xMode = static_cast<byte>(xMode);
        this->yMode = static_cast<byte>(yMode);
    }

    UIVisual::SizeMode UIVisual::GetWidthMode() const
    {
        return static_cast<SizeMode>(widthMode);
    }

    void UIVisual::SetWidthMode(SizeMode value)
    {
        widthMode = static_cast<byte>(value);
    }

    UIVisual::SizeMode UIVisual::GetHeightMode() const
    {
        return static_cast<SizeMode>(heightMode);
    }

    void UIVisual::SetHeightMode(SizeMode value)
    {
        heightMode = static_cast<byte>(value);
    }

    void UIVisual::SetSizeMode(SizeMode sizeMode)
    {
        this->widthMode = static_cast<byte>(sizeMode);
        this->heightMode = this->widthMode;
    }

    void UIVisual::SetSizeMode(SizeMode widthMode, SizeMode heightMode)
    {
        this->widthMode = static_cast<byte>(widthMode);
        this->heightMode = static_cast<byte>(heightMode);
    }

    float UIVisual::GetContentWidth()
    {
        return GetContentSize().X;
    }

    float UIVisual::GetContentHeight()
    {
        return GetContentSize().Y;
    }

    Vector2 UIVisual::GetOrigin() const
    {
        return origin;
    }

    void UIVisual::SetOrigin(Vector2 value)
    {
        origin = value;
    }

    UIVisual::AnchorPoint UIVisual::GetAnchorPoint() const
    {
        return static_cast<AnchorPoint>(anchorPoint);
    }

    void UIVisual::SetAnchorPoint(AnchorPoint value)
    {
        anchorPoint = static_cast<byte>(value);
    }

    float UIVisual::GetOpacity() const
    {
        return static_cast<float>(opacity) / 255.0f;
    }

    UIVisual::Visibility UIVisual::GetVisibility() const
    {
        return static_cast<Visibility>(visibility);
    }

    void UIVisual::SetVisibility(Visibility value)
    {
        visibility = static_cast<byte>(value);
    }

    int UIVisual::GetZOrder() const
    {
        return static_cast<int>(zOrder);
    }

    bool UIVisual::GetPickable() const
    {
        return (flags & PICKALBE_BITFIELD) != 0x00;
    }

    void UIVisual::SetPickable(bool value)
    {
        if (value)
            flags |= PICKALBE_BITFIELD;
        else
            flags &= ~PICKALBE_BITFIELD;
    }

    bool UIVisual::GetFocusable() const
    {
        return (flags & FOCUSABLE_BITFIELD) != 0x00;
    }

    void UIVisual::SetFocusable(bool value)
    {
        if (value)
            flags |= FOCUSABLE_BITFIELD;
        else
            flags &= ~FOCUSABLE_BITFIELD;
    }

    bool UIVisual::GetDraggable() const
    {
        return (flags & DRAGGABLE_BITFIELD) != 0x00;
    }

    void UIVisual::SetDraggable(bool value)
    {
        if (value)
            flags |= DRAGGABLE_BITFIELD;
        else
            flags &= ~DRAGGABLE_BITFIELD;
    }

    UIEventMap* UIVisual::GetEventMap() const
    {
        return eventMap;
    }

    UIEffectMap* UIVisual::GetEffectMap() const
    {
        return effectMap;
    }

    UITransform* UIVisual::GetTransform() const
    {
        return transform;
    }

    UIPanel* UIVisual::GetParent() const
    {
        return parent;
    }
    
    bool UIVisual::IsVisible() const
    {
        return GetVisibility() == Visible && GetOpacity() > 0.0f;
    }

    bool UIVisual::IsFocused() const
    {
        return focuser != nullptr;
    }

    void UIVisual::SetXYModeByChars(const char* xMode, const char* yMode)
    {
        if (yMode)
        {
            SetXMode(ConvertFromStringToPositionMode(xMode));
            SetYMode(ConvertFromStringToPositionMode(yMode));
        }
        else
        {
            const PositionMode mode = ConvertFromStringToPositionMode(xMode);
            SetXMode(mode);
            SetYMode(mode);
        }
    }

    void UIVisual::SetSizeModeByChars(const char* widthMode, const char* heightMode)
    {
        if (heightMode)
        {
            SetWidthMode(ConvertFromStringToSizeMode(widthMode));
            SetHeightMode(ConvertFromStringToSizeMode(heightMode));
        }
        else
        {
            const SizeMode mode = ConvertFromStringToSizeMode(widthMode);
            SetWidthMode(mode);
            SetHeightMode(mode);
        }
    }
    
    void UIVisual::SetOriginXY(float x, float y)
    {
        SetOrigin(Vector2(x, y));
    }
}

BBBindLua(Bibim::UIVisual);
BBBindLuaEnum(Bibim::UIVisual::PositionMode,
              Bibim::UIVisual::ConvertFromStringToPositionMode,
              Bibim::UIVisual::ConvertFromPositionModeToString);
BBBindLuaEnum(Bibim::UIVisual::SizeMode,
              Bibim::UIVisual::ConvertFromStringToSizeMode,
              Bibim::UIVisual::ConvertFromSizeModeToString);
BBBindLuaEnum(Bibim::UIVisual::AnchorPoint,
              Bibim::UIVisual::ConvertFromStringToAnchorPoint,
              Bibim::UIVisual::ConvertFromAnchorPointToString);
BBBindLuaEnum(Bibim::UIVisual::Visibility,
              Bibim::UIVisual::ConvertFromStringToVisibility,
              Bibim::UIVisual::ConvertFromVisibilityToString);

#endif