namespace Bibim
{
    UIHandledDrawingContext::Handler* UIHandledDrawingContext::GetHandler() const
    {
        return handler;
    }

    void UIHandledDrawingContext::SetHandler(Handler* value)
    {
        handler = value;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIHandledDrawingContext::BoundsVisualizer* UIHandledDrawingContext::BoundsVisualizer::GetInstance()
    {
        static BoundsVisualizer Instance;
        return &Instance;
    }
}