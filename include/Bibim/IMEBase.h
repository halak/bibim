#pragma once
#ifndef __BIBIM_IME_BASE_H__
#define __BIBIM_IME_BASE_H__

#include <Bibim/FWD.h>
#include <Bibim/GameModule.h>
#include <Bibim/String.h>
#include <map>

namespace Bibim
{
    class IMEBase : public GameModule
    {
        BBAbstractModuleClass(IMEBase, GameModule);
        public:
            enum TextFormat
            {
                Plain,
                Number,
                Email,
                Password,
            };

            class Callback
            {
                public:
                    virtual ~Callback() { }

                    virtual void OnTextEdited(const String& text) = 0;
                    virtual void OnTextEditCancelled() = 0;
            };

            static const int NO_MAX_LENGTH = 0;

        public:
            IMEBase();
            IMEBase(Window* window);
            virtual ~IMEBase();

            void Edit(const String& text,
                      const String& title,
                      const String& description,
                      TextFormat format,
                      int maxLength,
                      Callback* callback);

            inline Window* GetWindow() const;
            inline void SetWindow(Window* value);

        public:
            class Request
            {
                public:
                    Request();
                    Request(const Request& original);
                    ~Request();

                    void Submit(const String& value) const;
                    void Cancel() const;

                    inline int GetID() const;
                    inline const String& GetText() const;
                    inline const String& GetTitle() const;
                    inline const String& GetDescription() const;
                    inline TextFormat GetFormat() const;
                    inline int GetMaxLength() const;

                    Request& operator = (const Request& right);

                private:
                    Request(IMEBase* ime, int id, const String& text, const String& title, const String& description, TextFormat format, int maxLength);

                private:
                    IMEBase* ime;
                    int id;
                    String text;
                    String title;
                    String description;
                    TextFormat format;
                    int maxLength;

                    friend class IMEBase;
            };

        protected:
            virtual void OnRequest(const Request& request) = 0;

            void SubmitEdit(int callbackID, const String& text);
            void CancelEdit(int callbackID);

        private:
            int RegisterCallback(Callback* callback);
            Callback* UnregisterCallback(int callbackID);
            typedef std::map<int, Callback*> CallbackMap;

        private:
            Window* window;
            CallbackMap callbacks;
            int lastCallbackID;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    Window* IMEBase::GetWindow() const
    {
        return window;
    }

    void IMEBase::SetWindow(Window* value)
    {
        window = value;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    int IMEBase::Request::GetID() const
    {
        return id;
    }

    const String& IMEBase::Request::GetText() const
    {
        return text;
    }

    const String& IMEBase::Request::GetTitle() const
    {
        return title;
    }

    const String& IMEBase::Request::GetDescription() const
    {
        return description;
    }

    IMEBase::TextFormat IMEBase::Request::GetFormat() const
    {
        return format;
    }

    int IMEBase::Request::GetMaxLength() const
    {
        return maxLength;
    }
}

#endif