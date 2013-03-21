package org.bibim.android;

import android.content.res.AssetManager;

public class JNI {
     public static native void init(int width, int height, String localeName, String workingDirectory, AssetManager assets);
     public static native void step();
     
     public static native void handleMouseMove(int x, int y);
     public static native void handleMouseLeftButtonDown(int x, int y);
     public static native void handleMouseLeftButtonUp(int x, int y);
     public static native void handleMouseMiddleButtonDown(int x, int y);
     public static native void handleMouseMiddleButtonUp(int x, int y);
     public static native void handleMouseRightButtonDown(int x, int y);
     public static native void handleMouseRightButtonUp(int x, int y);

     public static native void handleKeyDown(int keyCode);
     public static native void handleKeyUp(int keyCode);
}
