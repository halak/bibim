#include <Bibim/Config.h>
#include <Bibim/UIVisual.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Math.h>
#include <Bibim/UIDomain.h>
#include <Bibim/UIEffectMap.h>
#include <Bibim/UIEventMap.h>
#include <Bibim/UITransform.h>
#include <Bibim/UIGamePadEventArgs.h>
#include <Bibim/UIKeyboardEventArgs.h>
#include <Bibim/UIMouseButtonEventArgs.h>
#include <Bibim/UIMouseEventArgs.h>
#include <Bibim/UIMouseWheelEventArgs.h>
#include <Bibim/UIPickingContext.h>
#include <Bibim/UIPanel.h>

namespace Bibim
{
    UIVisual::UIVisual()
        : UIElement(),
          xMode(AbsolutePosition),
          yMode(AbsolutePosition),
          widthMode(RelativeSize),
          heightMode(RelativeSize),
          x(0.0f),
          y(0.0f),
          width(1.0f),
          height(1.0f),
          origin(Vector2::Zero),
          anchorPoint(LeftTop),
          opacity(255),
          visibility(Visible),
          zOrder(128),
          flags(DEFAULT_FLAGS),
          eventMap(nullptr),
          effectMap(nullptr),
          parent(nullptr),
          focuser(nullptr)
    {
    }

    UIVisual::~UIVisual()
    {
        if (focuser)
        {
            UIDomain* temporaryFocuser = focuser;
            focuser = nullptr;
            temporaryFocuser->OnDestructed(this);
        }
    }

    RectF UIVisual::ComputeBounds(UIVisualVisitor& context)
    {
        const RectF bounds = context.GetCurrentBounds();
        const Vector2 contentSize = (widthMode == ContentSize || heightMode == ContentSize) ? GetContentSize() : Vector2::Zero;
        RectF result = RectF::Empty;

        float offsetX = 0.0f;
        float offsetY = 0.0f;
        switch (xMode)
        {
            case AbsolutePosition:
                offsetX = x;
                break;
            case RelativePosition:
                offsetX = x * bounds.Width;
                break;
        }

        switch (yMode)
        {
            case AbsolutePosition:
                offsetY = y;
                break;
            case RelativePosition:
                offsetY = y * bounds.Height;
                break;
        }

        switch (widthMode)
        {
            case AbsoluteSize:
                result.Width = width;
                break;
            case RelativeSize:
                result.Width = width * bounds.Width;
                break;
            case ContentSize:
                result.Width = width * contentSize.X;
                break;
            case AdjustiveSize:
                result.Width = bounds.Width + width;
                break;
        }

        switch (heightMode)
        {
            case AbsoluteSize:
                result.Height = height;
                break;
            case RelativeSize:
                result.Height = height * bounds.Height;
                break;
            case ContentSize:
                result.Height = height * contentSize.Y;
                break;
            case AdjustiveSize:
                result.Height = bounds.Height + height;
                break;
        }

        switch (anchorPoint)
        {
            case LeftTop:
                result.X = bounds.GetLeft() + offsetX;
                result.Y = bounds.GetTop()  + offsetY;
                break;
            case LeftBottom:
                result.X = bounds.GetLeft()   + offsetX;
                result.Y = bounds.GetBottom() - offsetY;
                break;
            case LeftMiddle:
                result.X = bounds.GetLeft()   + offsetX;
                result.Y = bounds.GetMiddle() + offsetY;
                break;
            case RightTop:
                result.X = bounds.GetRight() - offsetX;
                result.Y = bounds.GetTop()   + offsetY;
                break;
            case RightBottom:
                result.X = bounds.GetRight()  - offsetX;
                result.Y = bounds.GetBottom() - offsetY;
                break;
            case RightMiddle:
                result.X = bounds.GetRight()  - offsetX;
                result.Y = bounds.GetMiddle() + offsetY;
                break;
            case CenterTop:
                result.X = bounds.GetCenter() + offsetX;
                result.Y = bounds.GetTop()    + offsetY;
                break;
            case CenterBottom:
                result.X = bounds.GetCenter() + offsetX;
                result.Y = bounds.GetBottom() - offsetY;
                break;
            case Center:
                result.X = bounds.GetCenter() + offsetX;
                result.Y = bounds.GetMiddle() + offsetY;
                break;
        }

        result.X -= result.Width  * origin.X;
        result.Y -= result.Height * origin.Y;

        return result;
    }

    UIGeometryEffect* UIVisual::GetGeometryEffect() const
    {
        if (effectMap)
            return effectMap->GetGeometryEffect();
        else
            return nullptr;
    }

    void UIVisual::SetGeometryEffect(UIGeometryEffect* value)
    {
        if (effectMap == nullptr)
            effectMap = new UIEffectMap();

        effectMap->SetGeometryEffect(value);
    }

    void UIVisual::InsertEffect(UIPixelEffect* item)
    {
        if (effectMap == nullptr)
            effectMap = new UIEffectMap();

        effectMap->Insert(item);
    }

    void UIVisual::RemoveEffect(UIPixelEffect* item)
    {
        if (effectMap)
            effectMap->Remove(item);
    }

    UIPixelEffect* UIVisual::FindEffect(const String& name)
    {
        if (effectMap)
            return effectMap->FindPixelEffect(name);
        else
            return nullptr;
    }

    void UIVisual::BringToFront()
    {
        if (parent)
            parent->BringChildToFront(this);
    }

    void UIVisual::SendToBack()
    {
        if (parent)
            parent->SendChildToBack(this);
    }

    void UIVisual::AlignTo(AnchorPoint point)
    {
        switch (point)
        {
            case LeftTop:
                origin = Vector2(0.0f, 0.0f);
                break;
            case LeftBottom:
                origin = Vector2(0.0f, 1.0f);
                break;
            case LeftMiddle:
                origin = Vector2(0.0f, 0.5f);
                break;
            case RightTop:
                origin = Vector2(1.0f, 0.0f);
                break;
            case RightBottom:
                origin = Vector2(1.0f, 1.0f);
                break;
            case RightMiddle:
                origin = Vector2(1.0f, 0.5f);
                break;
            case CenterTop:
                origin = Vector2(0.5f, 0.0f);
                break;
            case CenterBottom:
                origin = Vector2(0.5f, 1.0f);
                break;
            case Center:
                origin = Vector2(0.5f, 0.5f);
                break;
        }

        SetAnchorPoint(point);
    }

    void UIVisual::Click()
    {
        RaiseMouseClickEvent(UIMouseEventArgs(nullptr, this));
    }

    Vector2 UIVisual::GetContentSize()
    {
        return Vector2::Zero;
    }

    void UIVisual::SetOpacity(float value)
    {
        if (value <= 0.0f)
            opacity = 0;
        else if (value >= 1.0f)
            opacity = 255;
        else
            opacity = static_cast<byte>(value * 255.0f);
    }

    void UIVisual::SetZOrder(int value)
    {
        value = Math::Clamp(value, 0, 255);
        if (static_cast<int>(zOrder) != value)
        {
            const int old = static_cast<int>(zOrder);
            zOrder = static_cast<byte>(value);
            if (parent)
                parent->OnChildZOrderChanged(this, old);
        }
    }

    void UIVisual::SetEventMap(UIEventMap* value)
    {
        eventMap = value;
    }

    void UIVisual::SetEffectMap(UIEffectMap* value)
    {
        effectMap = value;
    }

    void UIVisual::SetTransform(UITransform* value)
    {
        transform = value;
    }

    void UIVisual::SetParent(UIPanel* value)
    {
        if (parent != value)
        {
            UIPanel* old = parent;

            parent = value;

            OnParentChanged(old);
        }
    }

    void UIVisual::Focus(UIDomain* value)
    {
        if (focuser != value)
        {
            if (focuser)
                focuser->OnDestructed(this);

            focuser = value;

            if (focuser)
                RaiseFocusedEvent(UIEventArgs(this));
            else
                RaiseBluredEvent(UIEventArgs(this));
        }
    }

    bool UIVisual::IsPanel() const
    {
        return false;
    }

    bool UIVisual::IsWindow() const
    {
        return false;
    }

    void UIVisual::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        xMode = reader.ReadByte();
        yMode = reader.ReadByte();
        widthMode = reader.ReadByte();
        heightMode = reader.ReadByte();
        x = reader.ReadFloat();
        y = reader.ReadFloat();
        width = reader.ReadFloat();
        height = reader.ReadFloat();
        origin = reader.ReadVector2();
        anchorPoint = reader.ReadByte();
        opacity = reader.ReadByte();
        visibility = reader.ReadByte();
        zOrder = reader.ReadByte();
        SetPickable(reader.ReadBool());
        SetFocusable(reader.ReadBool());
        eventMap = static_cast<UIEventMap*>(reader.ReadComponent());
        effectMap = static_cast<UIEffectMap*>(reader.ReadComponent());
        transform = static_cast<UITransform*>(reader.ReadComponent());
    }

    void UIVisual::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        xMode = o->xMode;
        yMode = o->yMode;
        widthMode = o->widthMode;
        heightMode = o->heightMode;
        x = o->x;
        y = o->y;
        width = o->width;
        height = o->height;
        origin = o->origin;
        anchorPoint = o->anchorPoint;
        opacity = o->opacity;
        visibility = o->visibility;
        zOrder = o->zOrder;
        flags = o->flags;
        eventMap = context.Clone(o->eventMap);
        effectMap = context.Clone(o->effectMap);
        transform = context.Clone(o->transform);
    }

    void UIVisual::OnDraw(UIDrawingContext& /*context*/)
    {
    }

    void UIVisual::OnPick(UIPickingContext& context)
    {
        if (GetPickable() && context.Contains(context.GetCurrentClippedBounds()))
            context.SetResult(this);
    }

    void UIVisual::OnFocused()
    {
    }

    void UIVisual::OnBlured()
    {
    }

    void UIVisual::OnParentChanged(UIPanel* /*old*/)
    {
    }

    bool UIVisual::OnKeyDown(const UIKeyboardEventArgs& /*args*/)
    {
        return false;
    }

    bool UIVisual::OnKeyUp(const UIKeyboardEventArgs& /*args*/)
    {
        return false;
    }

    bool UIVisual::OnKeyPressing(const UIKeyboardEventArgs& /*args*/)
    {
        return false;
    }

    void UIVisual::OnMouseEnter(const UIMouseEventArgs& /*args*/)
    {
    }

    void UIVisual::OnMouseLeave(const UIMouseEventArgs& /*args*/)
    {
    }

    bool UIVisual::OnMouseMove(const UIMouseEventArgs& /*args*/)
    {
        return false;
    }

    bool UIVisual::OnMouseClick(const UIMouseEventArgs& /*args*/)
    {
        return false;
    }

    bool UIVisual::OnMouseButtonDown(const UIMouseButtonEventArgs& /*args*/)
    {
        return false;
    }

    bool UIVisual::OnMouseButtonUp(const UIMouseButtonEventArgs& /*args*/)
    {
        return false;
    }

    bool UIVisual::OnMouseButtonPressing(const UIMouseButtonEventArgs& /*args*/)
    {
        return false;
    }

    bool UIVisual::OnMouseWheel(const UIMouseWheelEventArgs& /*args*/)
    {
        return false;
    }

    bool UIVisual::OnGamePadButtonDown(const UIGamePadEventArgs& /*args*/)
    {
        return false;
    }

    bool UIVisual::OnGamePadButtonUp(const UIGamePadEventArgs& /*args*/)
    {
        return false;
    }

    bool UIVisual::OnGamePadButtonPressing(const UIGamePadEventArgs& /*args*/)
    {
        return false;
    }

    bool UIVisual::OnGamePadTrigger(const UIGamePadEventArgs& /*args*/)
    {
        return false;
    }

    bool UIVisual::OnGamePadThumbstick(const UIGamePadEventArgs& /*args*/)
    {
        return false;
    }

#   define RaiseRoutedEvent(onCallbackMethod, raiseEventMethod, eventID, args) \
                bool handled = onCallbackMethod(args); \
                if (eventMap) \
                    handled = eventMap->RaiseEvent(eventID, args) || handled; \
                \
                if (handled == false) \
                { \
                    if (UIVisual* parent = GetParent()) \
                        parent->raiseEventMethod(args); \
                }

    void UIVisual::RaiseKeyDownEvent(const UIKeyboardEventArgs& args)
    {
        RaiseRoutedEvent(OnKeyDown, RaiseKeyDownEvent, UIEventID::KeyDown, args);
    }

    void UIVisual::RaiseKeyUpEvent(const UIKeyboardEventArgs& args)
    {
        RaiseRoutedEvent(OnKeyUp, RaiseKeyUpEvent, UIEventID::KeyUp, args);
    }

    void UIVisual::RaiseKeyPressingEvent(const UIKeyboardEventArgs& args)
    {
        RaiseRoutedEvent(OnKeyPressing, RaiseKeyPressingEvent, UIEventID::KeyPressing, args);
    }

    void UIVisual::RaiseMouseEnterEvent(const UIMouseEventArgs& args)
    {
        OnMouseEnter(args);
        if (eventMap)
            eventMap->RaiseEvent(UIEventID::MouseEnter, args);
    }

    void UIVisual::RaiseMouseLeaveEvent(const UIMouseEventArgs& args)
    {
        OnMouseLeave(args);
        if (eventMap)
            eventMap->RaiseEvent(UIEventID::MouseLeave, args);
    }

    void UIVisual::RaiseMouseMoveEvent(const UIMouseEventArgs& args)
    {
        RaiseRoutedEvent(OnMouseMove, RaiseMouseMoveEvent, UIEventID::MouseMove, args);
    }

    void UIVisual::RaiseMouseClickEvent(const UIMouseEventArgs& args)
    {
        RaiseRoutedEvent(OnMouseClick, RaiseMouseClickEvent, UIEventID::MouseClick, args);
    }

    void UIVisual::RaiseMouseButtonDownEvent(const UIMouseButtonEventArgs& args)
    {
        RaiseRoutedEvent(OnMouseButtonDown, RaiseMouseButtonDownEvent, UIEventID::MouseButtonDown, args);
    }

    void UIVisual::RaiseMouseButtonUpEvent(const UIMouseButtonEventArgs& args)
    {
        RaiseRoutedEvent(OnMouseButtonUp, RaiseMouseButtonUpEvent, UIEventID::MouseButtonUp, args);
    }

    void UIVisual::RaiseMouseButtonPressingEvent(const UIMouseButtonEventArgs& args)
    {
        RaiseRoutedEvent(OnMouseButtonPressing, RaiseMouseButtonPressingEvent, UIEventID::MouseButtonPressing, args);
    }

    void UIVisual::RaiseMouseWheelEvent(const UIMouseWheelEventArgs& args)
    {
        RaiseRoutedEvent(OnMouseWheel, RaiseMouseWheelEvent, UIEventID::MouseWheel, args);
    }

    void UIVisual::RaiseGamePadButtonDownEvent(const UIGamePadEventArgs& args)
    {
        RaiseRoutedEvent(OnGamePadButtonDown, RaiseGamePadButtonDownEvent, UIEventID::GamePadButtonDown, args);
    }

    void UIVisual::RaiseGamePadButtonUpEvent(const UIGamePadEventArgs& args)
    {
        RaiseRoutedEvent(OnGamePadButtonUp, RaiseGamePadButtonUpEvent, UIEventID::GamePadButtonUp, args);
    }

    void UIVisual::RaiseGamePadButtonPressingEvent(const UIGamePadEventArgs& args)
    {
        RaiseRoutedEvent(OnGamePadButtonPressing, RaiseGamePadButtonPressingEvent, UIEventID::GamePadButtonPressing, args);
    }

    void UIVisual::RaiseGamePadTriggerEvent(const UIGamePadEventArgs& args)
    {
        RaiseRoutedEvent(OnGamePadTrigger, RaiseGamePadTriggerEvent, UIEventID::GamePadTrigger, args);
    }

    void UIVisual::RaiseGamePadThumbstickEvent(const UIGamePadEventArgs& args)
    {
        RaiseRoutedEvent(OnGamePadThumbstick, RaiseGamePadThumbstickEvent, UIEventID::GamePadThumbstick, args);
    }

    void UIVisual::RaiseFocusedEvent(const UIEventArgs& args)
    {
        OnFocused();
        if (eventMap)
            eventMap->RaiseEvent(UIEventID::Focused, args);
    }

    void UIVisual::RaiseBluredEvent(const UIEventArgs& args)
    {
        OnBlured();
        if (eventMap)
            eventMap->RaiseEvent(UIEventID::Blured, args);
    }

#   undef RaiseRoutedEvent

    UIVisual::PositionMode UIVisual::ConvertFromStringToPositionMode(const char* value)
    {
             if (value == nullptr)                             return UndefinedPosition;
        else if (String::EqualsCharsIgnoreCase(value, "ABS"))  return AbsolutePosition;
        else if (String::EqualsCharsIgnoreCase(value, "REL"))  return RelativePosition;
        else                                                   return UndefinedPosition;
    }

    const char* UIVisual::ConvertFromPositionModeToString(PositionMode value)
    {
        switch (value)
        {
            case AbsolutePosition:  return "ABS";
            case RelativePosition:  return "REL";
            default:                return "UNDEFINED";
        }
    }

    UIVisual::SizeMode UIVisual::ConvertFromStringToSizeMode(const char* value)
    {
             if (value == nullptr)                            return ContentSize;
        else if (String::EqualsCharsIgnoreCase(value, "ABS")) return AbsoluteSize;
        else if (String::EqualsCharsIgnoreCase(value, "REL")) return RelativeSize;
        else if (String::EqualsCharsIgnoreCase(value, "ADJ")) return AdjustiveSize;
        else                                                  return ContentSize;
    }

    const char* UIVisual::ConvertFromSizeModeToString(SizeMode value)
    {
        switch (value)
        {
            case AbsoluteSize:  return "ABS";
            case RelativeSize:  return "REL";
            case AdjustiveSize: return "ADJ";
            default:            return "CONTENT";
        }
    }

    UIVisual::AnchorPoint UIVisual::ConvertFromStringToAnchorPoint(const char* value)
    {
             if (value == nullptr)                                      return LeftTop;
        else if (String::EqualsCharsIgnoreCase(value, "LeftTop"))       return LeftTop;
        else if (String::EqualsCharsIgnoreCase(value, "LeftBottom"))    return LeftBottom;
        else if (String::EqualsCharsIgnoreCase(value, "LeftMiddle"))    return LeftMiddle;
        else if (String::EqualsCharsIgnoreCase(value, "RightTop"))      return RightTop;
        else if (String::EqualsCharsIgnoreCase(value, "RightBottom"))   return RightBottom;
        else if (String::EqualsCharsIgnoreCase(value, "RightMiddle"))   return RightMiddle;
        else if (String::EqualsCharsIgnoreCase(value, "CenterTop"))     return CenterTop;
        else if (String::EqualsCharsIgnoreCase(value, "CenterBottom"))  return CenterBottom;
        else if (String::EqualsCharsIgnoreCase(value, "Center"))        return Center;
        else                                                            return LeftTop;
    }

    const char* UIVisual::ConvertFromAnchorPointToString(AnchorPoint value)
    {
        switch (value)
        {
            case LeftTop:       return "LeftTop";
            case LeftBottom:    return "LeftBottom";
            case LeftMiddle:    return "LeftMiddle";
            case RightTop:      return "RightTop";
            case RightBottom:   return "RightBottom";
            case RightMiddle:   return "RightMiddle";
            case CenterTop:     return "CenterTop";
            case CenterBottom:  return "CenterBottom";
            case Center:        return "Center";
            default:            return "LeftTop";
        }
    }

    UIVisual::Visibility UIVisual::ConvertFromStringToVisibility(const char* value)
    {
             if (value == nullptr)                                  return Visible;
        else if (String::EqualsCharsIgnoreCase(value, "Visible"))   return Visible;
        else if (String::EqualsCharsIgnoreCase(value, "Invisible")) return Invisible;
        else if (String::EqualsCharsIgnoreCase(value, "Collapsed")) return Collasped;
        else                                                        return Visible;
    }

    const char* UIVisual::ConvertFromVisibilityToString(Visibility value)
    {
        switch (value)
        {
            case Visible:   return "Visible";
            case Invisible: return "Invisible";
            case Collasped: return "Collapsed";
            default:        return "Visible";
        }
    }
}