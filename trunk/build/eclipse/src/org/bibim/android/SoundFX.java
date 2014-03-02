package org.bibim.android;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import android.content.Context;
import android.content.res.AssetFileDescriptor;
import android.media.SoundPool;

public final class SoundFX {
    private Context context;
    private SoundPool pool;
    private float volume;

    private static HashMap<String, Integer> loadedSounds; 
    private static HashMap<String, ArrayList<Integer>> playingStreams; 

    public SoundFX(Context context) {
        this.context = context;
        this.pool = null;//new SoundPool(1, AudioManager.STREAM_MUSIC, 0);
        this.volume = 1.0f;
        this.loadedSounds = new HashMap<String, Integer>();
        this.playingStreams = new HashMap<String, ArrayList<Integer>>();
    }

    public void pause() {
    }

    public void resume() {
    }

    public void destroy() {
    }
}
