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

                bool HasAndroidRequest() const;
                Request PopAndroidRequest();
                void SubmitAndroidEdit(int id, const String& text);
                void CancelAndroidEdit(int id);

            private:
                virtual void OnRequest(const Request& request);

            private:
                std::queue<Request> requests;
        };
    }

#endif