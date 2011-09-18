#include <Bibim/PCH.h>
#include <Bibim/UIHandledDrawingContext.h>
#include <Bibim/Math.h>

namespace Bibim
{
    UIHandledDrawingContext::UIHandledDrawingContext(UIRenderer* renderer)
        : UIDrawingContext(renderer),
          handler(BoundsVisualizer::GetInstance())
    {
    }

    UIHandledDrawingContext::UIHandledDrawingContext(UIRenderer* renderer, IHandler* handler)
        : UIDrawingContext(renderer),
          handler(handler)
    {
    }

    UIHandledDrawingContext::~UIHandledDrawingContext()
    {
    }

    void UIHandledDrawingContext::OnBegan()
    {
        if (handler)
            handler->OnBegan(*this);
    }

    void UIHandledDrawingContext::OnEnded()
    {
        if (handler)
            handler->OnEnded(*this);
    }

    void UIHandledDrawingContext::OnVisit()
    {
        if (handler)
        {
            handler->OnVisualBegan(*this);
            UIDrawingContext::OnVisit();
            handler->OnVisualEnded(*this);
        }
        else
            UIDrawingContext::OnVisit();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    Color UIHandledDrawingContext::BoundsVisualizer::LineColor = Color(255, 255, 255);
    float UIHandledDrawingContext::BoundsVisualizer::LineWidth = 2.0f;

    UIHandledDrawingContext::BoundsVisualizer::BoundsVisualizer()
    {
    }

    UIHandledDrawingContext::BoundsVisualizer::~BoundsVisualizer()
    {
    }

    Color UIHandledDrawingContext::BoundsVisualizer::GetLineColor()
    {
        return LineColor;
    }
    
    void UIHandledDrawingContext::BoundsVisualizer::SetLineColor(Color value)
    {
        LineColor = value;
    }

    float UIHandledDrawingContext::BoundsVisualizer::GetLineWidth()
    {
        return LineWidth;
    }

    void UIHandledDrawingContext::BoundsVisualizer::SetLineWidth(float value)
    {
        LineWidth = Math::Max(value, 0.0f);
    }

    void UIHandledDrawingContext::BoundsVisualizer::OnVisualBegan(UIHandledDrawingContext& context)
    {
        context.DrawRect(context.GetCurrentBounds(), LineWidth, LineColor);
    }
}