#include <Bibim/PCH.h>
#include <Bibim/HttpClient.Android.h>
#include <jni.h>
#include <android/log.h>
#define  LOG_TAG    "Hotblood-JNI"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

namespace Bibim
{
    JNIEnv* env = nullptr;

    HttpClient::HttpClient()
    {
    }

    HttpClient::~HttpClient()
    {
    }

    HttpClient::Response* HttpClient::OnRequest(Request* request)
    {
        LOGI("HttpClient::OnRequest");

        if (env == nullptr)
            return nullptr;

        jclass bibimClass = env->FindClass("com/ikinagames/hotblood/Bibim");
        LOGI("com/ikinagames/hotblood/Bibim");
        const char* signature = "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;";
        jmethodID sendHttpRequestMethod = env->GetStaticMethodID(bibimClass, "sendHttpRequest", signature);
        if (sendHttpRequestMethod == nullptr)
            return nullptr;

        LOGI("(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;");

        jstring method = env->NewStringUTF(request->GetMethod());
        jstring url = env->NewStringUTF(request->GetURL().CStr());
        jstring params = env->NewStringUTF("");
        jstring userAgent = env->NewStringUTF(request->GetUserAgent().CStr());

        jstring response = (jstring)env->CallStaticObjectMethod(bibimClass,
                                                                sendHttpRequestMethod,
                                                                method,
                                                                url,
                                                                params,
                                                                userAgent);
        const char* x = env->GetStringUTFChars(response, nullptr);

        env->ReleaseStringUTFChars(response, x);
    }

    void HttpClient::SetJNIEnv(void* value)
    {
        env = (JNIEnv*)value;
    }
}