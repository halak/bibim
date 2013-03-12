#include <Bibim/Lua.h>
#include <Bibim/All.h>

namespace Bibim
{
    static void* alloc(void* ud, void* ptr, size_t osize, size_t nsize);
    static int   panic(lua_State* L);

    Lua::Lua()
        : state(nullptr),
          lastCallbackIndex(0)
    {
        state = lua_newstate(alloc, this);
        if (state)
            lua_atpanic(state, &panic);

        LoadLibraries();
        LoadClasses();
    }

    Lua::~Lua()
    {
        if (state)
        {
            lua_State* s = state;
            state = nullptr;
            lua_close(s);
        }
    }

    void Lua::GC()
    {
        lua_gc(state, LUA_GCCOLLECT, 0);
    }

    void Lua::DoFile(const String& path)
    {
        FileStreamPtr file = new FileStream(path, FileStream::ReadOnly);
        const int length = file->GetLength();
        std::vector<char> text;
        text.resize(length + 1, '\0');
        file->Read(&text[0], length);
        file->Close();

        lua_tinker::dostring(state, &text[0], path.CStr());
    }

    void Lua::LoadLibraries()
    {
        lua_pushcfunction(state, &luaopen_base);
        lua_pushstring(state, "");
        lua_call(state, 1, 0);

        lua_pushcfunction(state, &luaopen_table);
        lua_pushstring(state, LUA_TABLIBNAME);
        lua_call(state, 1, 0);

        lua_pushcfunction(state, &luaopen_string);
        lua_pushstring(state, LUA_STRLIBNAME);
        lua_call(state, 1, 0);

        lua_pushcfunction(state, &luaopen_math);
        lua_pushstring(state, LUA_MATHLIBNAME);
        lua_call(state, 1, 0);

        lua_pushcfunction(state, &luaopen_debug);
        lua_pushstring(state, LUA_DBLIBNAME);
        lua_call(state, 1, 0);

        lua_tinker::def(state, "_ALERT", static_cast<void (*)(const char*)>(&Bibim::Log::Warning));

        lua_newtable(state);
        lua_setglobal(state, "_CALLBACKS");
    }

    void Lua::LoadClasses()
    {
        lua_State* L = state;
        lua_tinker::class_add<Object>(L, "Object");
        lua_tinker::class_add<SharedObject>(L, "SharedObject");
            lua_tinker::class_inh<SharedObject, Object>(L);
        lua_tinker::class_add<GameAsset>(L, "GameAsset");
            lua_tinker::class_inh<GameAsset, SharedObject>(L);
        lua_tinker::class_add<Texture2D>(L, "Texture2D");
            lua_tinker::class_inh<Texture2D, GameAsset>(L);
            lua_tinker::class_def<Texture2D>(L, "GetWidth", &Texture2D::GetWidth);
            lua_tinker::class_def<Texture2D>(L, "GetHeight", &Texture2D::GetHeight);
            lua_tinker::class_def<Texture2D>(L, "GetSurfaceWidth", &Texture2D::GetSurfaceWidth);
            lua_tinker::class_def<Texture2D>(L, "GetSurfaceHeight", &Texture2D::GetSurfaceHeight);
        lua_tinker::class_add<SourceTexture2D>(L, "SourceTexture2D");
            lua_tinker::class_inh<SourceTexture2D, Texture2D>(L);
        lua_tinker::class_add<Image>(L, "Image");
            lua_tinker::class_inh<Image, GameAsset>(L);
            lua_tinker::class_def<Image>(L, "GetWidth", &Image::GetWidth);
            lua_tinker::class_def<Image>(L, "GetHeight", &Image::GetHeight);
        lua_tinker::class_add<ImageSet>(L, "ImageSet");
            lua_tinker::class_inh<ImageSet, GameAsset>(L);
            lua_tinker::class_def<ImageSet>(L, "Find", &ImageSet::Find);
        lua_tinker::class_add<Sprite>(L, "Sprite");
            lua_tinker::class_inh<Sprite, GameAsset>(L);
        lua_tinker::class_add<SpriteSet>(L, "SpriteSet");
            lua_tinker::class_inh<SpriteSet, GameAsset>(L);
            lua_tinker::class_def<SpriteSet>(L, "Find", &SpriteSet::Find);
        lua_tinker::class_add<Font>(L, "Font");
            lua_tinker::class_inh<Font, GameAsset>(L);
            lua_tinker::class_def<Font>(L, "GetFaceURI", &Font::GetFaceURI);
            lua_tinker::class_def<Font>(L, "SetFaceURI", &Font::SetFaceURI);
            lua_tinker::class_def<Font>(L, "GetSize", &Font::GetSize);
            lua_tinker::class_def<Font>(L, "SetSize", &Font::SetSize);
            lua_tinker::class_def<Font>(L, "GetStrokeSize", &Font::GetStrokeSize);
            lua_tinker::class_def<Font>(L, "SetStrokeSize", &Font::SetStrokeSize);
            lua_tinker::class_def<Font>(L, "GetWeights", &Font::GetWeights);
            lua_tinker::class_def<Font>(L, "SetWeights", &Font::SetWeights);
            lua_tinker::class_def<Font>(L, "GetBold", &Font::GetBold);
            lua_tinker::class_def<Font>(L, "SetBold", &Font::SetBold);
            lua_tinker::class_def<Font>(L, "GetShear", &Font::GetShear);
            lua_tinker::class_def<Font>(L, "SetShear", &Font::SetShear);
            lua_tinker::class_def<Font>(L, "GetItalic", &Font::GetItalic);
            lua_tinker::class_def<Font>(L, "SetItalic", &Font::SetItalic);
            lua_tinker::class_def<Font>(L, "GetGlowSize", &Font::GetGlowSize);
            lua_tinker::class_def<Font>(L, "SetGlowSize", &Font::SetGlowSize);
            lua_tinker::class_def<Font>(L, "GetGlowSpread", &Font::GetGlowSpread);
            lua_tinker::class_def<Font>(L, "SetGlowSpread", &Font::SetGlowSpread);
            lua_tinker::class_def<Font>(L, "GetGlowThickness", &Font::GetGlowThickness);
            lua_tinker::class_def<Font>(L, "SetGlowThickness", &Font::SetGlowThickness);
            lua_tinker::class_def<Font>(L, "GetScale", &Font::GetScale);
            lua_tinker::class_def<Font>(L, "SetScale", &Font::SetScale);
            lua_tinker::class_def<Font>(L, "GetHinting", &Font::GetHinting);
            lua_tinker::class_def<Font>(L, "SetHinting", &Font::SetHinting);
            lua_tinker::class_def<Font>(L, "GetIgnoreBitmap", &Font::GetIgnoreBitmap);
            lua_tinker::class_def<Font>(L, "SetIgnoreBitmap", &Font::SetIgnoreBitmap);
            lua_tinker::class_def<Font>(L, "GetColor", &Font::GetColor);
            lua_tinker::class_def<Font>(L, "SetColor", &Font::SetColorRGB);
            lua_tinker::class_def<Font>(L, "GetStrokeColor", &Font::GetStrokeColor);
            lua_tinker::class_def<Font>(L, "SetStrokeColor", &Font::SetStrokeColorRGB);
            lua_tinker::class_def<Font>(L, "GetGlowColor", &Font::GetGlowColor);
            lua_tinker::class_def<Font>(L, "SetGlowColor", &Font::SetGlowColorRGB);
            lua_tinker::class_def<Font>(L, "GetSpacing", &Font::GetSpacing);
            lua_tinker::class_def<Font>(L, "SetSpacing", &Font::SetSpacing);
            lua_tinker::class_def<Font>(L, "GetAscender", &Font::GetAscender);
            lua_tinker::class_def<Font>(L, "GetDescender", &Font::GetDescender);
            lua_tinker::class_def<Font>(L, "GetLineHeight", &Font::GetLineHeight);
        lua_tinker::class_add<UILayout>(L, "UILayout");
            lua_tinker::class_inh<UILayout, GameAsset>(L);
            lua_tinker::class_def<UILayout>(L, "GetRoot", &UILayout::GetRoot);

        lua_tinker::class_add<GameComponent>(L, "GameComponent");
            lua_tinker::class_inh<GameComponent, SharedObject>(L);
            lua_tinker::class_def<GameComponent>(L, "Clone", static_cast<GameComponent* (GameComponent::*)() const>(&GameComponent::Clone));

        lua_tinker::class_add<EvalBase>(L, "EvalBase");
            lua_tinker::class_inh<EvalBase, GameComponent>(L);
            lua_tinker::class_def<EvalBase>(L, "Start", &EvalBase::Start);
            lua_tinker::class_def<EvalBase>(L, "Stop", &EvalBase::Stop);
            lua_tinker::class_def<EvalBase>(L, "Reset", &EvalBase::Reset);

        lua_tinker::class_add<EvalFloat>(L, "EvalFloat");
            lua_tinker::class_inh<EvalFloat, EvalBase>(L);

        lua_tinker::class_add<EvalFloatConstant>(L, "EvalFloatConstant");
            lua_tinker::class_inh<EvalFloatConstant, EvalFloat>(L);
            lua_tinker::class_con<EvalFloatConstant>(L, lua_tinker::constructor<EvalFloatConstant, float>);
            lua_tinker::class_def<EvalFloatConstant>(L, "GetValue", &EvalFloatConstant::GetValue);
            lua_tinker::class_def<EvalFloatConstant>(L, "SetValue", &EvalFloatConstant::SetValue);

        lua_tinker::class_add<EvalFloatMultiplication>(L, "EvalFloatMultiplication");
            lua_tinker::class_inh<EvalFloatMultiplication, EvalFloat>(L);
            lua_tinker::class_con<EvalFloatMultiplication>(L, lua_tinker::constructor<EvalFloatMultiplication, EvalFloat*, EvalFloat*>);
            lua_tinker::class_def<EvalFloatMultiplication>(L, "GetLeft", &EvalFloatMultiplication::GetLeft);
            lua_tinker::class_def<EvalFloatMultiplication>(L, "SetLeft", &EvalFloatMultiplication::SetLeft);
            lua_tinker::class_def<EvalFloatMultiplication>(L, "GetRight", &EvalFloatMultiplication::GetRight);
            lua_tinker::class_def<EvalFloatMultiplication>(L, "SetRight", &EvalFloatMultiplication::SetRight);

        lua_tinker::class_add<UIElement>(L, "UIElement");
            lua_tinker::class_inh<UIElement, GameComponent>(L);
            lua_tinker::class_def<UIElement>(L, "GetID", &UIElement::GetID);
            lua_tinker::class_def<UIElement>(L, "SetID", &UIElement::SetID);
            lua_tinker::class_def<UIElement>(L, "GetName", &UIElement::GetName);
            lua_tinker::class_def<UIElement>(L, "SetName", &UIElement::SetName);
        lua_tinker::class_add<UIVisual>(L, "UIVisual");
            lua_tinker::class_inh<UIVisual, UIElement>(L);
            lua_tinker::class_def<UIVisual>(L, "Show", &UIVisual::Show);
            lua_tinker::class_def<UIVisual>(L, "Hide", &UIVisual::Hide);
            lua_tinker::class_def<UIVisual>(L, "GetGeometryEffect", &UIVisual::GetGeometryEffect);
            lua_tinker::class_def<UIVisual>(L, "SetGeometryEffect", &UIVisual::SetGeometryEffect);
            lua_tinker::class_def<UIVisual>(L, "InsertEffect", &UIVisual::InsertEffect);
            lua_tinker::class_def<UIVisual>(L, "RemoveEffect", &UIVisual::RemoveEffect);
            lua_tinker::class_def<UIVisual>(L, "FindEffect", &UIVisual::FindEffect);
            lua_tinker::class_def<UIVisual>(L, "BringToFront", &UIVisual::BringToFront);
            lua_tinker::class_def<UIVisual>(L, "SendToBack", &UIVisual::SendToBack);
            lua_tinker::class_def<UIVisual>(L, "AlignTo", &UIVisual::AlignTo);
            lua_tinker::class_def<UIVisual>(L, "Click", &UIVisual::Click);
            lua_tinker::class_def<UIVisual>(L, "SetAbsBounds", static_cast<void (UIVisual::*)(float, float, float, float)>(&UIVisual::SetAbsoluteBounds));
            lua_tinker::class_def<UIVisual>(L, "SetRelBounds", &UIVisual::SetRelativeBounds);
            lua_tinker::class_def<UIVisual>(L, "GetX", &UIVisual::GetX);
            lua_tinker::class_def<UIVisual>(L, "SetX", &UIVisual::SetX);
            lua_tinker::class_def<UIVisual>(L, "GetY", &UIVisual::GetY);
            lua_tinker::class_def<UIVisual>(L, "SetY", &UIVisual::SetY);
            lua_tinker::class_def<UIVisual>(L, "GetXY", &UIVisual::GetXY);
            lua_tinker::class_def<UIVisual>(L, "SetXY", &UIVisual::SetXY);
            lua_tinker::class_def<UIVisual>(L, "GetWidth", &UIVisual::GetWidth);
            lua_tinker::class_def<UIVisual>(L, "SetWidth", &UIVisual::SetWidth);
            lua_tinker::class_def<UIVisual>(L, "GetHeight", &UIVisual::GetHeight);
            lua_tinker::class_def<UIVisual>(L, "SetHeight", &UIVisual::SetHeight);
            lua_tinker::class_def<UIVisual>(L, "GetSize", &UIVisual::GetSize);
            lua_tinker::class_def<UIVisual>(L, "SetSize", &UIVisual::SetSize);
            lua_tinker::class_def<UIVisual>(L, "GetXMode", &UIVisual::GetXMode);
            lua_tinker::class_def<UIVisual>(L, "SetXMode", &UIVisual::SetXMode);
            lua_tinker::class_def<UIVisual>(L, "GetYMode", &UIVisual::GetYMode);
            lua_tinker::class_def<UIVisual>(L, "SetYMode", &UIVisual::SetYMode);
            lua_tinker::class_def<UIVisual>(L, "SetXYMode", &UIVisual::SetXYModeByChars);
            lua_tinker::class_def<UIVisual>(L, "GetWidthMode", &UIVisual::GetWidthMode);
            lua_tinker::class_def<UIVisual>(L, "SetWidthMode", &UIVisual::SetWidthMode);
            lua_tinker::class_def<UIVisual>(L, "GetHeightMode", &UIVisual::GetHeightMode);
            lua_tinker::class_def<UIVisual>(L, "SetHeightMode", &UIVisual::SetHeightMode);
            lua_tinker::class_def<UIVisual>(L, "SetSizeMode", &UIVisual::SetSizeModeByChars);
            lua_tinker::class_def<UIVisual>(L, "GetOrigin", &UIVisual::GetOrigin);
            lua_tinker::class_def<UIVisual>(L, "SetOrigin", &UIVisual::SetOriginXY);
            lua_tinker::class_def<UIVisual>(L, "GetAnchorPoint", &UIVisual::GetAnchorPoint);
            lua_tinker::class_def<UIVisual>(L, "SetAnchorPoint", &UIVisual::SetAnchorPoint);
            lua_tinker::class_def<UIVisual>(L, "GetOpacity", &UIVisual::GetOpacity);
            lua_tinker::class_def<UIVisual>(L, "SetOpacity", &UIVisual::SetOpacity);
            lua_tinker::class_def<UIVisual>(L, "GetVisibility", &UIVisual::GetVisibility);
            lua_tinker::class_def<UIVisual>(L, "SetVisibility", &UIVisual::SetVisibility);
            lua_tinker::class_def<UIVisual>(L, "GetZOrder", &UIVisual::GetZOrder);
            lua_tinker::class_def<UIVisual>(L, "SetZOrder", &UIVisual::SetZOrder);
            lua_tinker::class_def<UIVisual>(L, "GetPickable", &UIVisual::GetPickable);
            lua_tinker::class_def<UIVisual>(L, "SetPickable", &UIVisual::SetPickable);
            lua_tinker::class_def<UIVisual>(L, "GetFocusable", &UIVisual::GetFocusable);
            lua_tinker::class_def<UIVisual>(L, "SetFocusable", &UIVisual::SetFocusable);
            lua_tinker::class_def<UIVisual>(L, "GetEventMap", &UIVisual::GetEventMap);
            lua_tinker::class_def<UIVisual>(L, "GetTransform", &UIVisual::GetTransform);
            lua_tinker::class_def<UIVisual>(L, "SetTransform", &UIVisual::SetTransform);
            lua_tinker::class_def<UIVisual>(L, "GetParent", &UIVisual::GetParent);
            lua_tinker::class_def<UIVisual>(L, "IsVisible", &UIVisual::IsVisible);
            lua_tinker::class_def<UIVisual>(L, "IsPanel", &UIVisual::IsPanel);
            lua_tinker::class_def<UIVisual>(L, "IsWindow", &UIVisual::IsWindow);
        lua_tinker::class_add<UIImage>(L, "UIImage");
            lua_tinker::class_inh<UIImage, UIVisual>(L);
            lua_tinker::class_con<UIImage>(L, lua_tinker::constructor<UIImage>);
            lua_tinker::class_def<UIImage>(L, "GetSource", &UIImage::GetSource);
            lua_tinker::class_def<UIImage>(L, "SetSource", &UIImage::SetSource);
            lua_tinker::class_def<UIImage>(L, "GetTexture", &UIImage::GetTexture);
            lua_tinker::class_def<UIImage>(L, "SetTexture", &UIImage::SetTexture);
            lua_tinker::class_def<UIImage>(L, "GetAutoResize", &UIImage::GetAutoResize);
            lua_tinker::class_def<UIImage>(L, "SetAutoResize", &UIImage::SetAutoResize);
            lua_tinker::class_def<UIImage>(L, "GetHorizontalFlip", &UIImage::GetHorizontalFlip);
            lua_tinker::class_def<UIImage>(L, "SetHorizontalFlip", &UIImage::SetHorizontalFlip);
            lua_tinker::class_def<UIImage>(L, "GetVerticalFlip", &UIImage::GetVerticalFlip);
            lua_tinker::class_def<UIImage>(L, "SetVerticalFlip", &UIImage::SetVerticalFlip);
        lua_tinker::class_add<UILabel>(L, "UILabel");
            lua_tinker::class_inh<UILabel, UIVisual>(L);
            lua_tinker::class_con<UILabel>(L, lua_tinker::constructor<UILabel>);
            lua_tinker::class_def<UILabel>(L, "GetText", &UILabel::GetText);
            lua_tinker::class_def<UILabel>(L, "SetText", &UILabel::SetText);
            lua_tinker::class_def<UILabel>(L, "GetFont", &UILabel::GetFont);
            lua_tinker::class_def<UILabel>(L, "SetFont", &UILabel::SetFont);
            lua_tinker::class_def<UILabel>(L, "GetAutoResize", &UILabel::GetAutoResize);
            lua_tinker::class_def<UILabel>(L, "SetAutoResize", &UILabel::SetAutoResize);
        lua_tinker::class_add<UIRect>(L, "UIRect");
            lua_tinker::class_inh<UIRect, UIVisual>(L);
            lua_tinker::class_con<UIRect>(L, lua_tinker::constructor<UIRect>);
            lua_tinker::class_def<UIRect>(L, "GetFillColorR", &UIRect::GetFillColorR);
            lua_tinker::class_def<UIRect>(L, "GetFillColorG", &UIRect::GetFillColorG);
            lua_tinker::class_def<UIRect>(L, "GetFillColorB", &UIRect::GetFillColorB);
            lua_tinker::class_def<UIRect>(L, "SetFillColor", &UIRect::SetFillColorRGB);
        lua_tinker::class_add<UISprite>(L, "UISprite");
            lua_tinker::class_inh<UISprite, UIVisual>(L);
            lua_tinker::class_con<UISprite>(L, lua_tinker::constructor<UISprite>);
            lua_tinker::class_def<UISprite>(L, "GetSource", &UISprite::GetSource);
            lua_tinker::class_def<UISprite>(L, "SetSource", &UISprite::SetSource);
            lua_tinker::class_def<UISprite>(L, "GetSpeed", &UISprite::GetSpeed);
            lua_tinker::class_def<UISprite>(L, "SetSpeed", &UISprite::SetSpeed);
            lua_tinker::class_def<UISprite>(L, "GetTime", &UISprite::GetTime);
            lua_tinker::class_def<UISprite>(L, "SetTime", &UISprite::SetTime);
            lua_tinker::class_def<UISprite>(L, "GetFrameIndex", &UISprite::GetFrameIndex);
            lua_tinker::class_def<UISprite>(L, "SetFrameIndex", &UISprite::SetFrameIndex);
            lua_tinker::class_def<UISprite>(L, "GetHorizontalFlip", &UISprite::GetHorizontalFlip);
            lua_tinker::class_def<UISprite>(L, "SetHorizontalFlip", &UISprite::SetHorizontalFlip);
            lua_tinker::class_def<UISprite>(L, "GetVerticalFlip", &UISprite::GetVerticalFlip);
            lua_tinker::class_def<UISprite>(L, "SetVerticalFlip", &UISprite::SetVerticalFlip);
            lua_tinker::class_def<UISprite>(L, "GetTimeline", &UISprite::GetTimeline);
            lua_tinker::class_def<UISprite>(L, "SetTimeline", &UISprite::SetTimeline);
        lua_tinker::class_add<UIPanel>(L, "UIPanel");
            lua_tinker::class_inh<UIPanel, UIVisual>(L);
            lua_tinker::class_def<UIPanel>(L, "ShowChildren", &UIPanel::ShowChildren);
            lua_tinker::class_def<UIPanel>(L, "HideChildren", &UIPanel::HideChildren);
            lua_tinker::class_def<UIPanel>(L, "FindChild", static_cast<UIVisual* (UIPanel::*)(const char*, bool) const>(&UIPanel::FindChildByChars));
            lua_tinker::class_def<UIPanel>(L, "GetChildIndex", &UIPanel::GetChildIndex);
            lua_tinker::class_def<UIPanel>(L, "GetChildAt", &UIPanel::GetChildAt);
            lua_tinker::class_def<UIPanel>(L, "GetNumberOfChildren", &UIPanel::GetNumberOfChildren);
            lua_tinker::class_def<UIPanel>(L, "IsAncestorOf", &UIPanel::IsAncestorOf);
        lua_tinker::class_add<UIWindow>(L, "UIWindow");
            lua_tinker::class_inh<UIWindow, UIPanel>(L);
            lua_tinker::class_con<UIWindow>(L, lua_tinker::constructor<UIWindow>);
            lua_tinker::class_def<UIWindow>(L, "Clone", static_cast<UIWindow* (UIWindow::*)() const>(&UIWindow::Clone));
            lua_tinker::class_def<UIWindow>(L, "AddChild", &UIWindow::AddChild);
            lua_tinker::class_def<UIWindow>(L, "RemoveChild", &UIWindow::RemoveChild);
            lua_tinker::class_def<UIWindow>(L, "RemoveChildAt", &UIWindow::RemoveChildAt);
            lua_tinker::class_def<UIWindow>(L, "RemoveAllChildren", &UIWindow::RemoveAllChildren);
        lua_tinker::class_add<UIButton>(L, "UIButton");
            lua_tinker::class_inh<UIButton, UIPanel>(L);
            lua_tinker::class_con<UIButton>(L, lua_tinker::constructor<UIButton>);
            lua_tinker::class_def<UIButton>(L, "Freeze", &UIButton::Freeze);
            lua_tinker::class_def<UIButton>(L, "Unfreeze", &UIButton::Unfreeze);
            lua_tinker::class_def<UIButton>(L, "GetNormal", &UIButton::GetNormal);
            lua_tinker::class_def<UIButton>(L, "SetNormal", &UIButton::SetNormal);
            lua_tinker::class_def<UIButton>(L, "GetPushed", &UIButton::GetPushed);
            lua_tinker::class_def<UIButton>(L, "SetPushed", &UIButton::SetPushed);
            lua_tinker::class_def<UIButton>(L, "GetHovering", &UIButton::GetHovering);
            lua_tinker::class_def<UIButton>(L, "SetHovering", &UIButton::SetHovering);
            lua_tinker::class_def<UIButton>(L, "GetCurrent", &UIButton::GetCurrent);
            lua_tinker::class_def<UIButton>(L, "GetHideInactives", &UIButton::GetHideInactives);
            lua_tinker::class_def<UIButton>(L, "SetHideInactives", &UIButton::SetHideInactives);
            lua_tinker::class_def<UIButton>(L, "GetFocusVisible", &UIButton::GetFocusVisible);
            lua_tinker::class_def<UIButton>(L, "SetFocusVisible", &UIButton::SetFocusVisible);
            lua_tinker::class_def<UIButton>(L, "GetFrozen", &UIButton::GetFrozen);
            lua_tinker::class_def<UIButton>(L, "SetFrozen", &UIButton::SetFrozen);
        lua_tinker::class_add<UICheckBox>(L, "UICheckBox");
            lua_tinker::class_inh<UICheckBox, UIButton>(L);
            lua_tinker::class_con<UICheckBox>(L, lua_tinker::constructor<UICheckBox>);
            lua_tinker::class_def<UICheckBox>(L, "GetCheckedNormal", &UICheckBox::GetCheckedNormal);
            lua_tinker::class_def<UICheckBox>(L, "SetCheckedNormal", &UICheckBox::SetCheckedNormal);
            lua_tinker::class_def<UICheckBox>(L, "GetCheckedPushed", &UICheckBox::GetCheckedPushed);
            lua_tinker::class_def<UICheckBox>(L, "SetCheckedPushed", &UICheckBox::SetCheckedPushed);
            lua_tinker::class_def<UICheckBox>(L, "GetCheckedHovering", &UICheckBox::GetCheckedHovering);
            lua_tinker::class_def<UICheckBox>(L, "SetCheckedHovering", &UICheckBox::SetCheckedHovering);
            lua_tinker::class_def<UICheckBox>(L, "GetChecked", &UICheckBox::GetChecked);
            lua_tinker::class_def<UICheckBox>(L, "SetChecked", &UICheckBox::SetChecked);
        lua_tinker::class_add<UIRadioButton>(L, "UIRadioButton");
            lua_tinker::class_inh<UIRadioButton, UICheckBox>(L);
            lua_tinker::class_con<UIRadioButton>(L, lua_tinker::constructor<UIRadioButton>);
        /*//MOBILE
        lua_tinker::class_add<UISpark>(L, "UISpark");
            lua_tinker::class_inh<UISpark, UIVisual>(L);
            lua_tinker::class_con<UISpark>(L, lua_tinker::constructor<UISpark, lua_tinker::table>);
            lua_tinker::class_def<UISpark>(L, "GetTimeline", &UISpark::GetTimeline);
            lua_tinker::class_def<UISpark>(L, "SetTimeline", &UISpark::SetTimeline);
            lua_tinker::class_def<UISpark>(L, "GetAutoRemove", &UISpark::GetAutoRemove);
            lua_tinker::class_def<UISpark>(L, "SetAutoRemove", &UISpark::SetAutoRemove);
        */

        lua_tinker::class_add<UIGeometryEffect>(L, "UIGeometryEffect");
            lua_tinker::class_inh<UIGeometryEffect, UIElement>(L);
        lua_tinker::class_add<UITintEffect>(L, "UITintEffect");
            lua_tinker::class_inh<UITintEffect, UIGeometryEffect>(L);
            lua_tinker::class_con<UITintEffect>(L, lua_tinker::constructor<UITintEffect>);
            lua_tinker::class_def<UITintEffect>(L, "GetValue", &UITintEffect::GetValue);
            lua_tinker::class_def<UITintEffect>(L, "SetValue", &UITintEffect::SetValueRGBA);
        lua_tinker::class_add<UISineCurveEffect>(L, "UISineCurveEffect");
            lua_tinker::class_inh<UISineCurveEffect, UIGeometryEffect>(L);
            lua_tinker::class_con<UISineCurveEffect>(L, lua_tinker::constructor<UISineCurveEffect>);
            lua_tinker::class_def<UISineCurveEffect>(L, "GetOffset", &UISineCurveEffect::GetOffset);
            lua_tinker::class_def<UISineCurveEffect>(L, "SetOffset", &UISineCurveEffect::SetOffset);
            lua_tinker::class_def<UISineCurveEffect>(L, "GetLength", &UISineCurveEffect::GetLength);
            lua_tinker::class_def<UISineCurveEffect>(L, "SetLength", &UISineCurveEffect::SetLength);
            lua_tinker::class_def<UISineCurveEffect>(L, "GetAmplitude", &UISineCurveEffect::GetAmplitude);
            lua_tinker::class_def<UISineCurveEffect>(L, "SetAmplitude", &UISineCurveEffect::SetAmplitude);
            lua_tinker::class_def<UISineCurveEffect>(L, "GetForm", &UISineCurveEffect::GetForm);
            lua_tinker::class_def<UISineCurveEffect>(L, "SetForm", &UISineCurveEffect::SetForm);
        lua_tinker::class_add<UIAfterImageEffect>(L, "UIAfterImageEffect");
            lua_tinker::class_inh<UIAfterImageEffect, UIGeometryEffect>(L);
            lua_tinker::class_con<UIAfterImageEffect>(L, lua_tinker::constructor<UIAfterImageEffect>);
            lua_tinker::class_def<UIAfterImageEffect>(L, "GetSkippedFrames", &UIAfterImageEffect::GetSkippedFrames);
            lua_tinker::class_def<UIAfterImageEffect>(L, "SetSkippedFrames", &UIAfterImageEffect::SetSkippedFrames);
            lua_tinker::class_def<UIAfterImageEffect>(L, "GetTotalFrames", &UIAfterImageEffect::GetTotalFrames);
            lua_tinker::class_def<UIAfterImageEffect>(L, "SetTotalFrames", &UIAfterImageEffect::SetTotalFrames);
            lua_tinker::class_def<UIAfterImageEffect>(L, "GetActive", &UIAfterImageEffect::GetActive);
            lua_tinker::class_def<UIAfterImageEffect>(L, "SetActive", &UIAfterImageEffect::SetActive);

        lua_tinker::class_add<UIPixelEffect>(L, "UIPixelEffect");
            lua_tinker::class_inh<UIPixelEffect, UIElement>(L);
        lua_tinker::class_add<UIColorMatrixEffect>(L, "UIColorMatrixEffect");
            lua_tinker::class_inh<UIColorMatrixEffect, UIPixelEffect>(L);
            lua_tinker::class_con<UIColorMatrixEffect>(L, lua_tinker::constructor<UIColorMatrixEffect>);
            lua_tinker::class_def<UIColorMatrixEffect>(L, "Reset", &UIColorMatrixEffect::Reset);
            lua_tinker::class_def<UIColorMatrixEffect>(L, "Grayscale", &UIColorMatrixEffect::GrayscaleRGBA);
            lua_tinker::class_def<UIColorMatrixEffect>(L, "Tint", &UIColorMatrixEffect::TintRGB);
            lua_tinker::class_def<UIColorMatrixEffect>(L, "Fill", &UIColorMatrixEffect::FillRGB);
            lua_tinker::class_def<UIColorMatrixEffect>(L, "SetRed", &UIColorMatrixEffect::SetRedRGBA);
            lua_tinker::class_def<UIColorMatrixEffect>(L, "SetGreen", &UIColorMatrixEffect::SetGreenRGBA);
            lua_tinker::class_def<UIColorMatrixEffect>(L, "SetBlue", &UIColorMatrixEffect::SetBlueRGBA);
        lua_tinker::class_add<UIBlendingEffect>(L, "UIBlendingEffect");
            lua_tinker::class_inh<UIBlendingEffect, UIPixelEffect>(L);
            lua_tinker::class_con<UIBlendingEffect>(L, lua_tinker::constructor<UIBlendingEffect, const char*>);
            lua_tinker::class_def<UIBlendingEffect>(L, "GetMode", &UIBlendingEffect::GetMode);
            lua_tinker::class_def<UIBlendingEffect>(L, "SetMode", &UIBlendingEffect::SetMode);
        lua_tinker::class_add<UIMaskEffect>(L, "UIMaskEffect");
            lua_tinker::class_inh<UIMaskEffect, UIPixelEffect>(L);
            lua_tinker::class_def<UIMaskEffect>(L, "GetMask", &UIMaskEffect::GetMask);
            lua_tinker::class_def<UIMaskEffect>(L, "SetMask", &UIMaskEffect::SetMask);
        lua_tinker::class_add<UIOpacityMaskEffect>(L, "UIOpacityMaskEffect");
            lua_tinker::class_inh<UIOpacityMaskEffect, UIMaskEffect>(L);
            lua_tinker::class_con<UIOpacityMaskEffect>(L, lua_tinker::constructor<UIOpacityMaskEffect>);
            lua_tinker::class_def<UIOpacityMaskEffect>(L, "GetStartPoint", &UIOpacityMaskEffect::GetStartPoint);
            lua_tinker::class_def<UIOpacityMaskEffect>(L, "SetStartPoint", &UIOpacityMaskEffect::SetStartPoint);
            lua_tinker::class_def<UIOpacityMaskEffect>(L, "GetLength", &UIOpacityMaskEffect::GetLength);
            lua_tinker::class_def<UIOpacityMaskEffect>(L, "SetLength", &UIOpacityMaskEffect::SetLength);
            lua_tinker::class_def<UIOpacityMaskEffect>(L, "GetFill", &UIOpacityMaskEffect::GetFill);
            lua_tinker::class_def<UIOpacityMaskEffect>(L, "SetFill", &UIOpacityMaskEffect::SetFill);

        lua_tinker::class_add<UITransform>(L, "UITransform");
            lua_tinker::class_inh<UITransform, UIElement>(L);
        lua_tinker::class_add<UITransform2D>(L, "UITransform2D");
            lua_tinker::class_inh<UITransform2D, UITransform>(L);
            lua_tinker::class_con<UITransform2D>(L, lua_tinker::constructor<UITransform2D>);
            lua_tinker::class_def<UITransform2D>(L, "Reset", &UITransform2D::Reset);
        lua_tinker::class_add<UITransform3D>(L, "UITransform3D");
            lua_tinker::class_inh<UITransform3D, UITransform>(L);
            lua_tinker::class_con<UITransform3D>(L, lua_tinker::constructor<UITransform3D>);
            lua_tinker::class_def<UITransform3D>(L, "Reset", &UITransform3D::Reset);
            lua_tinker::class_def<UITransform3D>(L, "Rotate", &UITransform3D::RotateXYZ);
            lua_tinker::class_def<UITransform3D>(L, "GetLocalOffset", &UITransform3D::GetLocalOffset);
            lua_tinker::class_def<UITransform3D>(L, "SetLocalOffset", &UITransform3D::SetLocalOffsetXYZ);
            lua_tinker::class_def<UITransform3D>(L, "GetGlobalOffset", &UITransform3D::GetGlobalOffset);
            lua_tinker::class_def<UITransform3D>(L, "SetGlobalOffset", &UITransform3D::SetGlobalOffsetXYZ);
            lua_tinker::class_def<UITransform3D>(L, "GetRotation", &UITransform3D::GetRotation);
            lua_tinker::class_def<UITransform3D>(L, "SetRotation", &UITransform3D::SetRotationXYZ);
            lua_tinker::class_def<UITransform3D>(L, "GetRotationCenter", &UITransform3D::GetRotationCenter);
            lua_tinker::class_def<UITransform3D>(L, "SetRotationCenter", &UITransform3D::SetRotationCenterXY);
            lua_tinker::class_def<UITransform3D>(L, "GetScale", &UITransform3D::GetScale);
            lua_tinker::class_def<UITransform3D>(L, "SetScale", &UITransform3D::SetScaleXY);
            lua_tinker::class_def<UITransform3D>(L, "GetScaleCenter", &UITransform3D::GetScaleCenter);
            lua_tinker::class_def<UITransform3D>(L, "SetScaleCenter", &UITransform3D::SetScaleCenterXY);

        lua_tinker::class_add<UIEventMap>(L, "UIEventMap");
            lua_tinker::class_inh<UIEventMap, UIElement>(L);

        lua_tinker::class_add<CollisionSpace2D>(L, "CollisionSpace2D");
            lua_tinker::class_inh<CollisionSpace2D, GameModule>(L);
            lua_tinker::class_def<CollisionSpace2D>(L, "Add", &CollisionSpace2D::Add);
            lua_tinker::class_def<CollisionSpace2D>(L, "Remove", &CollisionSpace2D::Remove);
            lua_tinker::class_def<CollisionSpace2D>(L, "Clear", static_cast<void (CollisionSpace2D::*)()>(&CollisionSpace2D::Clear));
            lua_tinker::class_def<CollisionSpace2D>(L, "ClearGroup", static_cast<void (CollisionSpace2D::*)(int)>(&CollisionSpace2D::Clear));
            lua_tinker::class_def<CollisionSpace2D>(L, "Find", &CollisionSpace2D::Find);
            lua_tinker::class_def<CollisionSpace2D>(L, "GetGroup", &CollisionSpace2D::GetGroup);
            lua_tinker::class_def<CollisionSpace2D>(L, "SetGroup", &CollisionSpace2D::SetGroup);
            lua_tinker::class_def<CollisionSpace2D>(L, "GetNumberOfGroups", &CollisionSpace2D::GetNumberOfGroups);
            lua_tinker::class_def<CollisionSpace2D>(L, "SetNumberOfGroups", &CollisionSpace2D::SetNumberOfGroups);
            lua_tinker::class_def<CollisionSpace2D>(L, "GetCollisionRelationship", &CollisionSpace2D::GetCollisionRelationship);
            lua_tinker::class_def<CollisionSpace2D>(L, "SetCollisionRelationship", &CollisionSpace2D::SetCollisionRelationship);

        lua_tinker::class_add<Shape2D>(L, "Shape2D");
            lua_tinker::class_inh<Shape2D, GameComponent>(L);
            lua_tinker::class_def<Shape2D>(L, "GetPosition", &Shape2D::GetPosition);
            lua_tinker::class_def<Shape2D>(L, "SetPosition", &Shape2D::SetPositionXY);
            lua_tinker::class_def<Shape2D>(L, "GetRotation", &Shape2D::GetRotation);
            lua_tinker::class_def<Shape2D>(L, "SetRotation", &Shape2D::SetRotation);
            lua_tinker::class_def<Shape2D>(L, "GetScale", &Shape2D::GetScale);
            lua_tinker::class_def<Shape2D>(L, "SetScale", &Shape2D::SetScale);

        lua_tinker::class_add<AxisAlignedBoxShape2D>(L, "AxisAlignedBoxShape2D");
            lua_tinker::class_inh<AxisAlignedBoxShape2D, GameComponent>(L);
            lua_tinker::class_con<AxisAlignedBoxShape2D>(L, lua_tinker::constructor<AxisAlignedBoxShape2D>);
            lua_tinker::class_def<AxisAlignedBoxShape2D>(L, "GetMin", &AxisAlignedBoxShape2D::GetMin);
            lua_tinker::class_def<AxisAlignedBoxShape2D>(L, "SetMin", &AxisAlignedBoxShape2D::SetMinXY);
            lua_tinker::class_def<AxisAlignedBoxShape2D>(L, "GetMax", &AxisAlignedBoxShape2D::GetMax);
            lua_tinker::class_def<AxisAlignedBoxShape2D>(L, "SetMax", &AxisAlignedBoxShape2D::SetMaxXY);

        lua_tinker::class_add<BoxShape2D>(L, "BoxShape2D");
            lua_tinker::class_inh<BoxShape2D, Shape2D>(L);
            lua_tinker::class_con<BoxShape2D>(L, lua_tinker::constructor<BoxShape2D>);
            lua_tinker::class_def<BoxShape2D>(L, "GetOrientation", &BoxShape2D::GetOrientation);
            lua_tinker::class_def<BoxShape2D>(L, "SetOrientation", &BoxShape2D::SetOrientationXY);
            lua_tinker::class_def<BoxShape2D>(L, "GetExtension", &BoxShape2D::GetExtension);
            lua_tinker::class_def<BoxShape2D>(L, "SetExtension", &BoxShape2D::SetExtensionXY);

        lua_tinker::class_add<SphereShape2D>(L, "SphereShape2D");
            lua_tinker::class_inh<SphereShape2D, Shape2D>(L);
            lua_tinker::class_con<SphereShape2D>(L, lua_tinker::constructor<SphereShape2D>);
            lua_tinker::class_def<SphereShape2D>(L, "GetRadius", &SphereShape2D::GetRadius);
            lua_tinker::class_def<SphereShape2D>(L, "SetRadius", &SphereShape2D::SetRadius);

        lua_tinker::class_add<UserShape2D>(L, "UserShape2D");
            lua_tinker::class_inh<UserShape2D, Shape2D>(L);

        lua_tinker::class_add<SpatialObject2D>(L, "SpatialObject2D");
            lua_tinker::class_inh<SpatialObject2D, GameComponent>(L);
            lua_tinker::class_def<SpatialObject2D>(L, "GetPosition", &SpatialObject2D::GetPosition);
            lua_tinker::class_def<SpatialObject2D>(L, "SetPosition", &SpatialObject2D::SetPositionXY);
    }

    int Lua::RegisterCallback(int index)
    {
        lua_State* L = state;

        if (lua_isfunction(L, index))
        {
            // newIndex = #_CALLBACKS + 1
            lua_getglobal(L, "_CALLBACKS");
            int callbackIndex = lastCallbackIndex++;

            // _CALLBACKS[newIndex] = callback
            lua_pushvalue(L, index);
            lua_rawseti(L, -2, callbackIndex);

            // pop _CALLBACKS
            lua_pop(L, 1);

            return callbackIndex;
        }
        else
            return -1;
    }

    void Lua::UnregisterCallback(int callbackIndex)
    {
        if (state == nullptr || callbackIndex == -1)
            return;

        // newIndex = #_CALLBACKS + 1
        lua_getglobal(state, "_CALLBACKS");

        // _CALLBACKS[callbackIndex] = nil
        lua_pushnil(state);
        lua_rawseti(state, -2, callbackIndex);

        // pop _CALLBACKS
        lua_pop(state, 1);
    }

    static void* alloc(void* ud, void* ptr, size_t osize, size_t nsize)
    {
        (void)ud;
        (void)osize;
        if (nsize > 0)
            return realloc(ptr, nsize);
        else
        {
            free(ptr);
            return NULL;
        }
    }

    static int panic(lua_State* L)
    {
        (void)L;  /* to avoid warnings */
        const String error = String("PANIC: unprotected error in call to Lua API  (") + lua_tostring(L, -1) + ")";
        Bibim::Log::Error(error.CStr());
        return 0;
    }
}