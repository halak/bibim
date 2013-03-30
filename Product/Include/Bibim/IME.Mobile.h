#pragma once
#ifndef __BIBIM_IME_ANDROID_H__
#define __BIBIM_IME_ANDROID_H__

#   include <Bibim/FWD.h>
#   include <Bibim/IMEBase.h>
#   include <queue>

    namespace Bibim
    {
        class IME : public IMEBase
        {
            BBModuleClass(IME, IMEBase, 'I', 'M', 'E', '_');
            public:
                IME();
                IME(Window* window);
                virtual ~IME();

                bool HasMobileRequest() const;
                Request PopMobileRequest();
                void SubmitMobileEdit(int id, const String& text);
                void CancelMobileEdit(int id);

            private:
                virtual void OnRequest(const Request& request);

            private:
                std::queue<Request> requests;
        };
    }

#endif