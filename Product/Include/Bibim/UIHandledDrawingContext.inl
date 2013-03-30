namespace Bibim
{
    UIHandledDrawingContext::IHandler* UIHandledDrawingContext::GetHandler() const
    {
        return handler;
    }

    void UIHandledDrawingContext::SetHandler(IHandler* value)
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