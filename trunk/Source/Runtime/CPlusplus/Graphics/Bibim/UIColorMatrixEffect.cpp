#include <Bibim/PCH.h>
#include <Bibim/UIColorMatrixEffect.h>
#include <Bibim/ComponentStreamReader.h>

namespace Bibim
{
    BBImplementsComponent(UIColorMatrixEffect);

    const Vector4 UIColorMatrixEffect::DefaultRed(1.0f, 0.0f, 0.0f, 0.0f);
    const Vector4 UIColorMatrixEffect::DefaultGreen(0.0f, 1.0f, 0.0f, 0.0f);
    const Vector4 UIColorMatrixEffect::DefaultBlue(0.0f, 0.0f, 1.0f, 0.0f);
    const Vector4 UIColorMatrixEffect::DefaultAlpha(0.0f, 0.0f, 0.0f, 0.0f);

    UIColorMatrixEffect::UIColorMatrixEffect()
        : Base(ClassIndex),
          red(DefaultRed),
          green(DefaultGreen),
          blue(DefaultBlue),
          alpha(DefaultAlpha)
    {
    }

    UIColorMatrixEffect::UIColorMatrixEffect(Vector4 red, Vector4 green, Vector4 blue, Vector4 alpha)
        : Base(ClassIndex),
          red(red),
          green(green),
          blue(blue),
          alpha(alpha)
    {
    }

    UIColorMatrixEffect::~UIColorMatrixEffect()
    {
    }

    void UIColorMatrixEffect::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        red = reader.ReadVector4();
        blue = reader.ReadVector4();
        green = reader.ReadVector4();
        alpha = reader.ReadVector4();
    }

    void UIColorMatrixEffect::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        red = o->red;
        green = o->green;
        blue = o->blue;
        alpha = o->alpha;
    }
}