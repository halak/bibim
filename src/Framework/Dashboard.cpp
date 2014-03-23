#include <Bibim/Config.h>
#include <Bibim/Dashboard.h>
#include <Bibim/BinaryReader.h>
#include <Bibim/BinaryWriter.h>
#include <Bibim/StandardGame.EmbeddedFont.h>
#include <Bibim/Clock.h>
#include <Bibim/Font.h>
#include <Bibim/FontLibrary.h>
#include <Bibim/GameFramework.h>
#include <Bibim/GameModuleTree.h>
#include <Bibim/Math.h>
#include <Bibim/NetworkStream.h>
#include <Bibim/Performance.h>
#include <Bibim/Socket.h>
#include <Bibim/UIPanel.h>
#include <Bibim/UIVisual.h>

namespace Bibim
{
    Dashboard::Dashboard(GameFramework* framework)
        : framework(framework),
          fontRevision(-1)
    {
        Log::Add(this);
        Construct(IPEndPoint(IPEndPoint::Localhost, 51893));
    }

    Dashboard::Dashboard(GameFramework* framework, IPEndPoint endPoint)
        : framework(framework),
          fontRevision(-1)
    {
        Log::Add(this);
        Construct(endPoint);
    }

    Dashboard::~Dashboard()
    {
        Log::Remove(this);
    }

    void Dashboard::RemoveAllNotifications()
    {
        notifications.clear();
    }

    void Dashboard::Construct(IPEndPoint endPoint)
    {
#       if (defined(BIBIM_PLATFORM_WINDOWS))
        socket = new Socket(endPoint);
        socket->TryConnect();
        stringstream << std::boolalpha;
        selectedVisual = nullptr;

        if (socket->IsConnected())
        {
            socketStream = new NetworkStream(socket);
        }
#       endif
    }

    void Dashboard::Initialize(GameModuleTree* modules)
    {
        BBAssert(modules);

        if (FontLibrary* fontLibrary = modules->FindModule<FontLibrary>())
        {
            font = new Font(fontLibrary);
            font->SetFace(EMBEDDED_FONT_DATA,
                          sizeof(EMBEDDED_FONT_DATA) / sizeof(EMBEDDED_FONT_DATA[0]));
            font->SetColor(Color::White);
        }
    }

    void Dashboard::Finalize()
    {
        font.Reset();
    }
    
    void Dashboard::BeginFrame()
    {
        Performance::Reset();
    }

    void Dashboard::EndFrame()
    {
        typedef Performance::SampleCollection SampleCollection;
        const SampleCollection& samples = Performance::GetSamples();

        for (SampleCollection::const_iterator it = samples.begin(); it != samples.end(); ++it)
        {
        }
    }

    void Dashboard::TryConnect()
    {
        if (socket == nullptr ||
            socket->IsConnected())
            return;

        if (socket->TryConnect())
        {
            socketStream = new NetworkStream(socket);
        }
    }

    void Dashboard::OnBegan(UIHandledDrawingContext& /*context*/, UIVisual* /*target*/)
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

        static const Vector2 MARGIN = Vector2(10.0f, 15.0f);

        RectF bounds = context.GetCurrentBounds();
        bounds.X += MARGIN.X;
        bounds.Y += MARGIN.Y;
        bounds.Width  -= MARGIN.X * 2.0f;
        bounds.Height -= MARGIN.Y;

        DrawString(context, bounds, FontString(font, String::CFormat("FPS: %.1f", framework->GetFPS())), Color::White);

        bounds.Y -= font->GetLineHeight();
        bounds.Height -= font->GetLineHeight();

        if (notifications.empty() == false)
        {
            if (fontRevision != font->GetRevision())
            {
                fontRevision = font->GetRevision();
                for (NotificationCollection::iterator it = notifications.begin(); it != notifications.end(); ++it)
                {
                    FontString& text = (*it).Text;
                    text = FontString(text.GetFont(), text.GetText());
                }
            }

            for (NotificationCollection::const_iterator it = notifications.begin(); it != notifications.end(); ++it)
            {
                const Notification& item = (*it);

                DrawString(context, bounds, item.Text, item.TextColor);

                const float height = font->Measure(item.Text, bounds.Width).Size.Y;
                bounds.Y += height;
                bounds.Height -= height;
            }
        }

        TryConnect();

        if (socketStream && socketStream->CanRead())
        {
            static const int UIDataPacketID = 44523;
            static const int UIVisualSelectedPacketID = 44524;
            static const int UISynchronize = 44525;

            const int packetID = BinaryReader::ReadIntFrom(socketStream);
            switch (packetID)
            {
                case UIVisualSelectedPacketID:
                    selectedVisual = reinterpret_cast<void*>(BinaryReader::ReadLongIntFrom(socketStream));
                    break;
                case UISynchronize:
                    Jsonify(stringstream, target);
                    BinaryWriter::WriteTo(socketStream, UIDataPacketID);
                    BinaryWriter::WriteTo(socketStream, stringstream.str().c_str());
                    break;
            }
        }
    }

    void Dashboard::OnVisualBegan(UIHandledDrawingContext& /*context*/)
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

    void Dashboard::Error(const char* category, const char* message)
    {
        AddLogNotification(Color(237, 28, 36), category, message);
    }

    void Dashboard::Warning(const char* category, const char* message)
    {
        AddLogNotification(Color(255, 242, 0), category, message);
    }

    void Dashboard::Information(const char* /*category*/, const char* /*message*/)
    {
    }

    void Dashboard::AddLogNotification(Color color, const char* category, const char* message)
    {
        if (font == nullptr)
            return;

        if (notifications.size() >= 20)
            notifications.pop_front();

        Notification n;
        n.TextColor = color;
        if (category && category[0] != '\0')
            n.Text = FontString(font, String::CFormat("[%s] %s", category, message));
        else
            n.Text = FontString(font, message);

        notifications.push_back(n);
    }

    void Dashboard::DrawString(UIHandledDrawingContext& context, RectF bounds, const FontString& text, Color color)
    {
        const Color oldColor = text.GetFont()->GetColor();
        text.GetFont()->SetColor(Color(0, 0, 0));
        bounds.X -= 1.0f;
        bounds.Y -= 1.0f;
        context.DrawString(bounds, bounds, text);
        bounds.X += 2.0f;
        context.DrawString(bounds, bounds, text);
        bounds.Y += 2.0f;
        context.DrawString(bounds, bounds, text);
        bounds.X -= 2.0f;
        context.DrawString(bounds, bounds, text);
        text.GetFont()->SetColor(color);
        bounds.X += 1.0f;
        bounds.Y -= 1.0f;
        context.DrawString(bounds, bounds, text);
        text.GetFont()->SetColor(oldColor);
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
                        if (value > 0)
                            return String::CFormat("parent+%d", static_cast<int>(value));
                        else if (value < 0)
                            return String::CFormat("parent%d", static_cast<int>(value));
                        else
                            return String::CFormat("100%%");
                    case UIVisual::ContentAdjustiveSize:
                        if (value > 0)
                            return String::CFormat("content+%d", static_cast<int>(value));
                        else if (value < 0)
                            return String::CFormat("content%d", static_cast<int>(value));
                        else
                            return String::CFormat("auto");
                    default:
                        return "Unknown";
                }
            }

            static void Do(std::ostream& sout, const UIVisual* visual)
            {
                const String x = Humanize(visual->GetX(), visual->GetXMode());
                const String y = Humanize(visual->GetY(), visual->GetYMode());
                const String width = Humanize(visual->GetWidth(), visual->GetWidthMode());
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
                Property(sout, "focusable", visual->GetFocusable());
                Property(sout, "z", visual->GetZOrder(), false);

                if (visual->IsPanel())
                {
                    sout << ",";
                    sout << "\"children\": [";
                    typedef UIPanel::VisualCollection VisualCollection;
                    const VisualCollection& children = static_cast<const UIPanel*>(visual)->GetChildren();
                    for (VisualCollection::const_iterator it = children.begin(); it != children.end(); ++it)
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