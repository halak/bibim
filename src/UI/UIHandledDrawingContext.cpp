#include <Bibim/Config.h>
#include <Bibim/UIHandledDrawingContext.h>
#include <Bibim/Color.h>
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

    void UIHandledDrawingContext::OnBegan(UIVisual* root)
    {
        if (handler)
            handler->OnBegan(*this, root);
    }

    void UIHandledDrawingContext::OnEnded(UIVisual* root)
    {
        if (handler)
            handler->OnEnded(*this, root);
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
                return Color::TransparentBlack;

            switch (visual->GetClassID())
            {
                case UIImage::ClassID:
                    return Color::Blue;
                case UILabel::ClassID:
                    return Color::Yellow;
                case UISprite::ClassID:
                    return Color::Cyan;
                case UIDocument::ClassID:
                    return Color::YellowGreen;
                case UIWindow::ClassID:
                    return Color::White;
            }

            if (visual->IsPanel())
                return Color::Gray;
            else
                return Color::Black;
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