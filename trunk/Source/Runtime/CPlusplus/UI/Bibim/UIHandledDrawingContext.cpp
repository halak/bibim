#include <Bibim/PCH.h>
#include <Bibim/UIHandledDrawingContext.h>
#include <Bibim/BitMask.h>
#include <Bibim/Colors.h>
#include <Bibim/Math.h>
#include <Bibim/UIVisual.h>
#include <Bibim/UIImage.h>
#include <Bibim/UIDocument.h>
#include <Bibim/UILabel.h>
#include <Bibim/UISprite.h>
#include <Bibim/UIWindow.h>

namespace Bibim
{
    UIHandledDrawingContext::UIHandledDrawingContext(UIRenderer* renderer)
        : UIDrawingContext(renderer),
          handler(BoundsVisualizer::GetInstance())
    {
    }

    UIHandledDrawingContext::UIHandledDrawingContext(UIRenderer* renderer, Handler* handler)
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

    UIHandledDrawingContext::BoundsVisualizer::BoundsVisualizer()
    {
    }

    UIHandledDrawingContext::BoundsVisualizer::~BoundsVisualizer()
    {
    }

    namespace 
    {
        static Color GetBoundsColor(UIVisual* visual)
        {
            if (visual == nullptr)
                return Colors::TransparentBlack;

            switch (visual->GetClassID())
            {
                case UIImage::ClassID:
                    return Colors::Blue;
                case UILabel::ClassID:
                    return Colors::Yellow;
                case UISprite::ClassID:
                    return Colors::Cyan;
                case UIDocument::ClassID:
                    return Colors::YellowGreen;
                case UIWindow::ClassID:
                    return Colors::White;
            }

            if (visual->IsPanel())
                return Colors::Gray;
            else
                return Colors::Black;
        }
    }

    void UIHandledDrawingContext::BoundsVisualizer::OnVisualBegan(UIHandledDrawingContext& context)
    {
        UIVisual* visual = context.GetCurrentVisual();
        if (visual->IsPanel())
        {
            const Color boundsColor = GetBoundsColor(visual);

            RectF bounds = context.GetCurrentBounds();
            bounds.Inflate(+1.0f);
            context.DrawDebugRect(bounds, boundsColor);
            bounds.Inflate(-1.0f);
            context.DrawDebugRect(bounds, boundsColor);
            bounds.Inflate(-1.0f);
            context.DrawDebugRect(bounds, boundsColor);
        }
    }

    void UIHandledDrawingContext::BoundsVisualizer::OnVisualEnded(UIHandledDrawingContext& context)
    {
        UIVisual* visual = context.GetCurrentVisual();

        if (visual->IsPanel() == false)
            context.DrawDebugRect(context.GetCurrentBounds(), GetBoundsColor(visual));
    }
}