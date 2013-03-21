#include <Bibim/PCH.h>
#include <Bibim/GameFramework.Android.h>
#include <Bibim/Environment.h>
#include <Bibim/FileStream.h>
#include <Bibim/GameFramework.h>
#include <Bibim/GameWindow.h>
#include <Bibim/Key.h>
#include <Bibim/Point2.h>
#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/log.h>
#include <android/input.h>
using namespace Bibim;

namespace Bibim
{
    GameFramework* GameFramework::SingletonInstance = nullptr;

    GameFramework::GameFramework()
    {
        Construct(0, 0);
    }

    GameFramework::GameFramework(int width, int height)
    {
        Construct(width, height);
    }

    GameFramework::~GameFramework()
    {
    }

    void GameFramework::Construct(int width, int height)
    {
        GameFrameworkBase::Construct(width, height, String::Empty);
    }
    
    void GameFramework::init()
    {
        Initialize();
        PostInitialize();
    }

    void GameFramework::step()
    {
        StepFrame();
    }
}

/*
Game* g = nullptr;

#define  LOG_TAG    "Hotblood-JNI"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
*/

extern "C" {
    JNIEXPORT void JNICALL Java_org_bibim_android_JNI_init(JNIEnv* env, jclass clazz,
                                                           jint width, jint height,
                                                           jstring localeName, jstring workingDirectory,
                                                           jobject assetManager);
    JNIEXPORT void JNICALL Java_org_bibim_android_JNI_step(JNIEnv* env, jclass clazz);

    JNIEXPORT void JNICALL Java_org_bibim_android_JNI_handleMouseMove(JNIEnv* env, jclass clazz, jint x, jint y);
    JNIEXPORT void JNICALL Java_org_bibim_android_JNI_handleMouseLeftButtonDown(JNIEnv* env, jclass clazz, jint x, jint y);
    JNIEXPORT void JNICALL Java_org_bibim_android_JNI_handleMouseLeftButtonUp(JNIEnv* env, jclass clazz, jint x, jint y);
    JNIEXPORT void JNICALL Java_org_bibim_android_JNI_handleMouseMiddleButtonDown(JNIEnv* env, jclass clazz, jint x, jint y);
    JNIEXPORT void JNICALL Java_org_bibim_android_JNI_handleMouseMiddleButtonUp(JNIEnv* env, jclass clazz, jint x, jint y);
    JNIEXPORT void JNICALL Java_org_bibim_android_JNI_handleMouseRightButtonDown(JNIEnv* env, jclass clazz, jint x, jint y);
    JNIEXPORT void JNICALL Java_org_bibim_android_JNI_handleMouseRightButtonUp(JNIEnv* env, jclass clazz, jint x, jint y);

    JNIEXPORT void JNICALL Java_org_bibim_android_JNI_handleKeyDown(JNIEnv* env, jclass clazz, jint keyCode);
    JNIEXPORT void JNICALL Java_org_bibim_android_JNI_handleKeyUp(JNIEnv* env, jclass clazz, jint keyCode);
};

static Key::Code ConvertKeyCode(int androidKeyCode);
static const Bibim::String ToString(JNIEnv* env, jstring s);

JNIEXPORT void JNICALL Java_org_bibim_android_JNI_init(JNIEnv* env, jclass clazz,
                                                       jint width, jint height,
                                                       jstring localeName, jstring workingDirectory,
                                                       jobject assetManager)
{
    Environment::Setup(ToString(env, localeName), ToString(env, workingDirectory));
    FileStream::SetAndroidAssetManager(AAssetManager_fromJava(env, assetManager));

    if (GameFramework::SingletonInstance == nullptr)
    {
        GameFramework::SingletonInstance = GameFramework::Create();
        GameFramework::SingletonInstance->GetWindow()->SetSize(Point2(width, height));
        GameFramework::SingletonInstance->init();
    }
    else
    {
        GameFramework::SingletonInstance->GetWindow()->SetSize(Point2(width, height));
        GameFramework::SingletonInstance->GetWindow()->RaiseResizedEvent();
    }
}

JNIEXPORT void JNICALL Java_org_bibim_android_JNI_step(JNIEnv* env, jclass clazz)
{
    GameFramework::SingletonInstance->step();
}

JNIEXPORT void JNICALL Java_org_bibim_android_JNI_handleMouseMove(JNIEnv* env, jclass clazz, jint x, jint y)
{
    GameFramework::SingletonInstance->GetWindow()->RaiseMouseMoveEvent(x, y);
}

JNIEXPORT void JNICALL Java_org_bibim_android_JNI_handleMouseLeftButtonDown(JNIEnv* env, jclass clazz, jint x, jint y)
{
    GameFramework::SingletonInstance->GetWindow()->RaiseMouseLeftButtonDownEvent(x, y);
}

JNIEXPORT void JNICALL Java_org_bibim_android_JNI_handleMouseLeftButtonUp(JNIEnv* env, jclass clazz, jint x, jint y)
{
    GameFramework::SingletonInstance->GetWindow()->RaiseMouseLeftButtonUpEvent(x, y);
}

JNIEXPORT void JNICALL Java_org_bibim_android_JNI_handleMouseMiddleButtonDown(JNIEnv* env, jclass clazz, jint x, jint y)
{
    GameFramework::SingletonInstance->GetWindow()->RaiseMouseMiddleButtonDownEvent(x, y);
}

JNIEXPORT void JNICALL Java_org_bibim_android_JNI_handleMouseMiddleButtonUp(JNIEnv* env, jclass clazz, jint x, jint y)
{
    GameFramework::SingletonInstance->GetWindow()->RaiseMouseMiddleButtonUpEvent(x, y);
}

JNIEXPORT void JNICALL Java_org_bibim_android_JNI_handleMouseRightButtonDown(JNIEnv* env, jclass clazz, jint x, jint y)
{
    GameFramework::SingletonInstance->GetWindow()->RaiseMouseRightButtonDownEvent(x, y);
}

JNIEXPORT void JNICALL Java_org_bibim_android_JNI_handleMouseRightButtonUp(JNIEnv* env, jclass clazz, jint x, jint y)
{
    GameFramework::SingletonInstance->GetWindow()->RaiseMouseRightButtonUpEvent(x, y);
}

JNIEXPORT void JNICALL Java_org_bibim_android_JNI_handleKeyDown(JNIEnv* env, jclass clazz, jint keyCode)
{
    GameFramework::SingletonInstance->GetWindow()->RaiseKeyDownEvent(ConvertKeyCode(keyCode));
}

JNIEXPORT void JNICALL Java_org_bibim_android_JNI_handleKeyUp(JNIEnv* env, jclass clazz, jint keyCode)
{
    GameFramework::SingletonInstance->GetWindow()->RaiseKeyUpEvent(ConvertKeyCode(keyCode));
}

static Key::Code ConvertKeyCode(int androidKeyCode)
{
    switch (androidKeyCode)
    {
        case AKEYCODE_UNKNOWN: return Key::None;
        case AKEYCODE_SOFT_LEFT: return Key::None;
        case AKEYCODE_SOFT_RIGHT: return Key::None;
        case AKEYCODE_HOME: return Key::None;
        case AKEYCODE_BACK: return Key::None;
        case AKEYCODE_CALL: return Key::None;
        case AKEYCODE_ENDCALL: return Key::None;
        case AKEYCODE_0: return Key::D0;
        case AKEYCODE_1: return Key::D1;
        case AKEYCODE_2: return Key::D2;
        case AKEYCODE_3: return Key::D3;
        case AKEYCODE_4: return Key::D4;
        case AKEYCODE_5: return Key::D5;
        case AKEYCODE_6: return Key::D6;
        case AKEYCODE_7: return Key::D7;
        case AKEYCODE_8: return Key::D8;
        case AKEYCODE_9: return Key::D9;
        case AKEYCODE_STAR: return Key::None;
        case AKEYCODE_POUND: return Key::None;
        case AKEYCODE_DPAD_UP: return Key::Up;
        case AKEYCODE_DPAD_DOWN: return Key::Down;
        case AKEYCODE_DPAD_LEFT: return Key::Left;
        case AKEYCODE_DPAD_RIGHT: return Key::Right;
        case AKEYCODE_DPAD_CENTER: return Key::None;
        case AKEYCODE_VOLUME_UP: return Key::None;
        case AKEYCODE_VOLUME_DOWN: return Key::None;
        case AKEYCODE_POWER: return Key::None;
        case AKEYCODE_CAMERA: return Key::None;
        case AKEYCODE_CLEAR: return Key::None;
        case AKEYCODE_A: return Key::A;
        case AKEYCODE_B: return Key::B;
        case AKEYCODE_C: return Key::C;
        case AKEYCODE_D: return Key::D;
        case AKEYCODE_E: return Key::E;
        case AKEYCODE_F: return Key::F;
        case AKEYCODE_G: return Key::G;
        case AKEYCODE_H: return Key::H;
        case AKEYCODE_I: return Key::I;
        case AKEYCODE_J: return Key::J;
        case AKEYCODE_K: return Key::K;
        case AKEYCODE_L: return Key::L;
        case AKEYCODE_M: return Key::M;
        case AKEYCODE_N: return Key::N;
        case AKEYCODE_O: return Key::O;
        case AKEYCODE_P: return Key::P;
        case AKEYCODE_Q: return Key::Q;
        case AKEYCODE_R: return Key::R;
        case AKEYCODE_S: return Key::S;
        case AKEYCODE_T: return Key::T;
        case AKEYCODE_U: return Key::U;
        case AKEYCODE_V: return Key::V;
        case AKEYCODE_W: return Key::W;
        case AKEYCODE_X: return Key::X;
        case AKEYCODE_Y: return Key::Y;
        case AKEYCODE_Z: return Key::Z;
        case AKEYCODE_COMMA: return Key::None;
        case AKEYCODE_PERIOD: return Key::None;
        case AKEYCODE_ALT_LEFT: return Key::Alt;
        case AKEYCODE_ALT_RIGHT: return Key::Alt;
        case AKEYCODE_SHIFT_LEFT: return Key::Shift;
        case AKEYCODE_SHIFT_RIGHT: return Key::Shift;
        case AKEYCODE_TAB: return Key::None;
        case AKEYCODE_SPACE: return Key::Space;
        case AKEYCODE_SYM: return Key::None;
        case AKEYCODE_EXPLORER: return Key::None;
        case AKEYCODE_ENVELOPE: return Key::None;
        case AKEYCODE_ENTER: return Key::Enter;
        case AKEYCODE_DEL: return Key::Delete;
        case AKEYCODE_GRAVE: return Key::None;
        case AKEYCODE_MINUS: return Key::None;
        case AKEYCODE_EQUALS: return Key::None;
        case AKEYCODE_LEFT_BRACKET: return Key::None;
        case AKEYCODE_RIGHT_BRACKET: return Key::None;
        case AKEYCODE_BACKSLASH: return Key::None;
        case AKEYCODE_SEMICOLON: return Key::None;
        case AKEYCODE_APOSTROPHE: return Key::None;
        case AKEYCODE_SLASH: return Key::None;
        case AKEYCODE_AT: return Key::None;
        case AKEYCODE_NUM: return Key::None;
        case AKEYCODE_HEADSETHOOK: return Key::None;
        case AKEYCODE_FOCUS: return Key::None;
        case AKEYCODE_PLUS: return Key::None;
        case AKEYCODE_MENU: return Key::None;
        case AKEYCODE_NOTIFICATION: return Key::None;
        case AKEYCODE_SEARCH: return Key::None;
        case AKEYCODE_MEDIA_PLAY_PAUSE: return Key::None;
        case AKEYCODE_MEDIA_STOP: return Key::None;
        case AKEYCODE_MEDIA_NEXT: return Key::None;
        case AKEYCODE_MEDIA_PREVIOUS: return Key::None;
        case AKEYCODE_MEDIA_REWIND: return Key::None;
        case AKEYCODE_MEDIA_FAST_FORWARD: return Key::None;
        case AKEYCODE_MUTE: return Key::None;
        case AKEYCODE_PAGE_UP: return Key::None;
        case AKEYCODE_PAGE_DOWN: return Key::None;
        case AKEYCODE_PICTSYMBOLS: return Key::None;
        case AKEYCODE_SWITCH_CHARSET: return Key::None;
        case AKEYCODE_BUTTON_A: return Key::None;
        case AKEYCODE_BUTTON_B: return Key::None;
        case AKEYCODE_BUTTON_C: return Key::None;
        case AKEYCODE_BUTTON_X: return Key::None;
        case AKEYCODE_BUTTON_Y: return Key::None;
        case AKEYCODE_BUTTON_Z: return Key::None;
        case AKEYCODE_BUTTON_L1: return Key::None;
        case AKEYCODE_BUTTON_R1: return Key::None;
        case AKEYCODE_BUTTON_L2: return Key::None;
        case AKEYCODE_BUTTON_R2: return Key::None;
        case AKEYCODE_BUTTON_THUMBL: return Key::None;
        case AKEYCODE_BUTTON_THUMBR: return Key::None;
        case AKEYCODE_BUTTON_START: return Key::None;
        case AKEYCODE_BUTTON_SELECT: return Key::None;
        case AKEYCODE_BUTTON_MODE: return Key::None;
        default: return Key::None;
    }
}

static const String ToString(JNIEnv* env, jstring s)
{
    const int length = env->GetStringUTFLength(s);
    const char* buffer = env->GetStringUTFChars(s, nullptr);
    String result = String(buffer, 0, length);
    env->ReleaseStringUTFChars(s, buffer);
    return result;
}