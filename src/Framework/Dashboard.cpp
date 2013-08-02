#include <Bibim/Config.h>
#include <Bibim/Dashboard.h>
#include <Bibim/Diagnostics.h>
#include <Bibim/Clock.h>
#include <Bibim/Math.h>
#include <Bibim/NetworkStream.h>
#include <Bibim/Socket.h>
#include <Bibim/UIPanel.h>
#include <Bibim/UIVisual.h>

namespace Bibim
{
    Dashboard::Dashboard()
    {
        Construct(IPEndPoint(IPEndPoint::Localhost, 51893));
    }

    Dashboard::Dashboard(IPEndPoint endPoint)
    {
        Construct(endPoint);
    }

    Dashboard::~Dashboard()
    {
        if (Diagnostics::GetStream() == socketStream)
            Diagnostics::SetStream(nullptr);
    }

    void Dashboard::Construct(IPEndPoint endPoint)
    {
        socket = new Socket(endPoint);
        socket->TryConnect();
        stringstream << std::boolalpha;
        selectedVisual = nullptr;

        if (socket->IsConnected())
        {
            socketStream = new NetworkStream(socket);
            Diagnostics::SetStream(socketStream);
        }
    }

    void Dashboard::TryConnect()
    {
        if (socket->IsConnected())
            return;

        if (socket->TryConnect())
        {
            socketStream = new NetworkStream(socket);
            Diagnostics::SetStream(socketStream);
        }
    }

    void Dashboard::OnBegan(UIHandledDrawingContext& context, UIVisual* target)
    {
        selectedVisualBounds = RectF::Empty;
        selectedVisualClippedBounds = RectF::Empty;
    }

    void Dashboard::OnEnded(UIHandledDrawingContext& context, UIVisual* target)
    {
        if (selectedVisualBounds.Width > 0.0f && selectedVisualBounds.Height > 0.0f)
        {
            const bool status = (Clock::GetCurrentMilliSeconds() % 500 < 250);
            const Color outerColor = status ? Color::Yellow : Color::Gray;
            const Color innerColor = status ? Color::Red    : Color::White;

            RectF bounds = selectedVisualBounds;
            bounds.Inflate(+1.0f);
            context.DrawDebugRect(bounds, outerColor);
            bounds.Inflate(-1.0f);
            context.DrawDebugRect(bounds, innerColor);
            bounds.Inflate(-1.0f);
            context.DrawDebugRect(bounds, outerColor);
        }

        TryConnect();

        if (socketStream && socketStream->CanRead())
        {
            /*
            static const int UIVisualSelectedPacketID = 44524;

            BinaryReader reader(queryStream);
            const int packetID = reader.ReadInt();
            switch (packetID)
            {
                case UIVisualSelectedPacketID:
                    selectedVisual = reinterpret_cast<void*>(reader.ReadLongInt());
                    break;
            }
            */
        }
    }

    void Dashboard::OnVisualBegan(UIHandledDrawingContext& context)
    {
    }

    void Dashboard::OnVisualEnded(UIHandledDrawingContext& context)
    {
        if (context.GetCurrentVisual() == selectedVisual)
        {
            selectedVisualBounds = context.GetCurrentBounds();
            selectedVisualClippedBounds = context.GetCurrentClippedBounds();
        }
    }

    void Dashboard::Jsonify(std::ostringstream& o, UIVisual* visual)
    {
        struct Inner
        {
            static void Property(std::ostream& sout, const char* key, const char* value, bool appendComma=true)
            {
                if (value == nullptr)
                    return;

                sout << '"' << key << '"' << ':' << '"' << value << '"';
                if (appendComma)
                    sout << ',';
            }

            static void Property(std::ostream& sout, const char* key, const String& value, bool appendComma=true)
            {
                Property(sout, key, value.CStr(), appendComma);
            }

            static void Property(std::ostream& sout, const char* key, bool value, bool appendComma=true)
            {
                sout << '"' << key << '"'  << ':' << value;
                if (appendComma)
                    sout << ',';
            }

            static void Property(std::ostream& sout, const char* key, int value, bool appendComma=true)
            {
                sout << '"' << key << '"'  << ':' << value;
                if (appendComma)
                    sout << ',';
            }

            static void Property(std::ostream& sout, const char* key, longint value, bool appendComma=true)
            {
                sout << '"' << key << '"'  << ':' << value;
                if (appendComma)
                    sout << ',';
            }

            static String Humanize(float value, UIVisual::PositionMode mode)
            {
                switch (mode)
                {
                    case UIVisual::AbsolutePosition:
                        return String::CFormat("%d", static_cast<int>(value));
                    case UIVisual::RelativePosition:
                        return String::CFormat("%d%%", static_cast<int>(value * 100.0f));
                    default:
                        return "Undefined";
                }
            }

            static String Humanize(float value, UIVisual::SizeMode mode)
            {
                switch (mode)
                {
                    case UIVisual::AbsoluteSize:
                        return String::CFormat("%d", static_cast<int>(value));
                    case UIVisual::RelativeSize:
                        return String::CFormat("%d%%", static_cast<int>(value * 100.0f));
                    case UIVisual::ContentSize:
                        if (Math::Equals(value, 1.0f))
                            return String("auto");
                        else
                            return String::CFormat("C%d%%", static_cast<int>(value * 100.0f));
                    case UIVisual::AdjustiveSize:
                        return String::CFormat("parent+%d", static_cast<int>(value));
                    default:
                        return "Unknown";
                }
            }

            static void Do(std::ostream& sout, const UIVisual* visual)
            {
                const String x = Humanize(visual->GetX(), visual->GetXMode());
                const String y = Humanize(visual->GetY(), visual->GetYMode());
                const String width = Humanize(visual->GetWidth(), visual->GetHeightMode());
                const String height = Humanize(visual->GetHeight(), visual->GetHeightMode());

                sout << "{";
                Property(sout, "id", reinterpret_cast<longint>(visual));
                Property(sout, "class", visual->GetClassID());
                Property(sout, "name", visual->GetName());
                Property(sout, "xy", String::CFormat("%s, %s", x.CStr(), y.CStr()));
                Property(sout, "size", String::CFormat("%s, %s", width.CStr(), height.CStr()));
                Property(sout, "anchor", UIVisual::ConvertFromAnchorPointToString(visual->GetAnchorPoint()));
                if (Math::Equals(visual->GetOrigin(), Vector2(0.5f, 0.5f)))
                    Property(sout, "origin", "Center");
                else
                    Property(sout, "origin", String::CFormat("%d%%, %d%%", static_cast<int>(visual->GetOrigin().X * 100.0f),
                                                                           static_cast<int>(visual->GetOrigin().Y * 100.0f)));
                Property(sout, "visibility", UIVisual::ConvertFromVisibilityToString(visual->GetVisibility()));
                Property(sout, "opacity", String::CFormat("%d%%", static_cast<int>(visual->GetOpacity() * 100.0f)));
                Property(sout, "pickable", visual->GetPickable());
                Property(sout, "focusable", visual->GetFocusable(), false);

                if (visual->IsPanel())
                {
                    sout << ",";
                    sout << "\"children\": [";
                    typedef UIPanel::VisualCollection VisualCollection;
                    const VisualCollection& children = static_cast<const UIPanel*>(visual)->GetChildren();
                    for (VisualCollection::const_iterator it = children.begin(); it != children.end(); it++)
                    {
                        Inner::Do(sout, *it);

                        if (it != children.end() - 1)
                            sout << ",";
                    }
                    sout << "]";
                }

                sout << "}";
            }
        };

        o.clear();
        o.str("");
        Inner::Do(o, visual);
    }
}