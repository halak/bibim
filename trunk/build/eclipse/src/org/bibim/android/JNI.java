package org.bibim.android;

import org.bibim.android.IME.DialogParams;

import android.content.Context;
import android.content.res.AssetManager;

public class JNI {
    public static native void init(Context context, int width, int height, String localeName, String workingDirectory, AssetManager assets);
    public static native void step(Context context);
     
    public static native void handleMouseMove(int x, int y);
    public static native void handleMouseLeftButtonDown(int x, int y);
    public static native void handleMouseLeftButtonUp(int x, int y);
    public static native void handleMouseMiddleButtonDown(int x, int y);
    public static native void handleMouseMiddleButtonUp(int x, int y);
    public static native void handleMouseRightButtonDown(int x, int y);
    public static native void handleMouseRightButtonUp(int x, int y);

    public static native void handleKeyDown(int keyCode);
    public static native void handleKeyUp(int keyCode);
    
    public static native void handleIMESubmit(int id, String text);
    public static native void handleIMECancel(int id);

    public static void exit() {
        BaseActivity.activity.finish();
    }
    
    public static final int EDIT_TEXT_FORMAT_PLAIN = 0;
    public static final int EDIT_TEXT_FORMAT_NUMBER = 1;
    public static final int EDIT_TEXT_FORMAT_PASSWORD = 2;
    public static final int EDIT_TEXT_FORMAT_EMAIL = 3;
    public static void edit(final Context context, final int id, final String text, final String title, final String description, final int format, final int maxLength) {
        BaseActivity.activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Context context = BaseActivity.activity;
            
                final DialogParams params =
                        new DialogParams(context, id, text, title, description, maxLength);
                switch (format) {
                    case EDIT_TEXT_FORMAT_PLAIN:
                        IME.showPlainDialog(params);
                        break;
                    case EDIT_TEXT_FORMAT_NUMBER:
                        IME.showNumberDialog(params);
                        break;
                    case EDIT_TEXT_FORMAT_PASSWORD:
                        IME.showPasswordDialog(params);
                        break;
                    case EDIT_TEXT_FORMAT_EMAIL:
                        IME.showEmailDialog(params);
                        break;
                }
            }
        });
    }

    public static void playBgm(final String path) {
        BaseActivity.activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                BaseActivity.activity.getBgm().play(path);
            }
        });
    }

    public static void setBgmVolume(final float value) {
        BaseActivity.activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                BaseActivity.activity.getBgm().setVolume(value);
            }
        });
    }

    public static void playSfx(final String path, final int group) {
        BaseActivity.activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                BaseActivity.activity.getSfx().play(path, group);
            }
        });
    }

    public static void setSfxVolume(final float value) {
        BaseActivity.activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                BaseActivity.activity.getSfx().setVolume(value);
            }
        });
    }
}
