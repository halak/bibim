package org.bibim.android;

import android.content.Context;
import android.content.res.AssetManager;
import android.util.Log;

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
     
     
     public static void edit(Context context, int id, String text, String description, int format, int maxLength) {
    	 Log.i("JNI", String.format("%d | %s | %s | %d | %d", id, text, description, format, maxLength));
     }
}
