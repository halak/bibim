#include <Bibim/PCH.h>
#include <Bibim/UIColorMatrixEffect.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/ShaderEffect.h>

namespace Bibim
{
    BBImplementsComponent(UIColorMatrixEffect);

    const Vector4 UIColorMatrixEffect::DefaultRed(1.0f, 0.0f, 0.0f, 0.0f);
    const Vector4 UIColorMatrixEffect::DefaultGreen(0.0f, 1.0f, 0.0f, 0.0f);
    const Vector4 UIColorMatrixEffect::DefaultBlue(0.0f, 0.0f, 1.0f, 0.0f);

    UIColorMatrixEffect::UIColorMatrixEffect()
        : Base(ClassIndex, false, true),
          red(DefaultRed),
          green(DefaultGreen),
          blue(DefaultBlue)
    {
    }

    UIColorMatrixEffect::UIColorMatrixEffect(Vector4 red, Vector4 green, Vector4 blue)
        : Base(ClassIndex, false, true),
          red(red),
          green(green),
          blue(blue)
    {
    }

    UIColorMatrixEffect::~UIColorMatrixEffect()
    {
    }

    UIRenderer::Effector* UIColorMatrixEffect::CreateEffector(UIRenderer::Effector* parent, bool isShaderFunctionRendering)
    {
        if (isShaderFunctionRendering)
            return new Effector(static_cast<Effector*>(parent), this);
        else
            return nullptr;
    }

    void UIColorMatrixEffect::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        red = reader.ReadVector4();
        blue = reader.ReadVector4();
        green = reader.ReadVector4();
    }

    void UIColorMatrixEffect::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        red = o->red;
        green = o->green;
        blue = o->blue;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIColorMatrixEffect::Effector::Effector(Effector* parent, UIColorMatrixEffect* effect)
        : UIRenderer::Effector(UIColorMatrixEffect::ClassID)
    {
        if (parent)
        {
            red.X = parent->red.X * effect->red.X;
            red.Y = parent->red.Y * effect->red.Y;
            red.Z = parent->red.Z * effect->red.Z;
            red.W = parent->red.W * effect->red.W;
            green.X = parent->green.X * effect->green.X;
            green.Y = parent->green.Y * effect->green.Y;
            green.Z = parent->green.Z * effect->green.Z;
            green.W = parent->green.W * effect->green.W;
            blue.X = parent->blue.X * effect->blue.X;
            blue.Y = parent->blue.Y * effect->blue.Y;
            blue.Z = parent->blue.Z * effect->blue.Z;
            blue.W = parent->blue.W * effect->blue.W;
        }
        else
        {
            red = effect->red;
            green = effect->green;
            blue = effect->blue;
        }
    }

    UIColorMatrixEffect::Effector::~Effector()
    {
    }

    void UIColorMatrixEffect::Effector::Setup(ShaderEffect* effect)
    {
        if (ShaderEffect::ParameterPtr param = effect->FindParameter("Red"))
            param->SetValue(red);
        if (ShaderEffect::ParameterPtr param = effect->FindParameter("Green"))
            param->SetValue(green);
        if (ShaderEffect::ParameterPtr param = effect->FindParameter("Blue"))
            param->SetValue(blue);
    }
}