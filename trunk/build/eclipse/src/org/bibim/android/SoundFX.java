package org.bibim.android;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map.Entry;
import android.content.Context;
import android.content.res.AssetFileDescriptor;
import android.media.AudioManager;
import android.media.SoundPool;

public final class SoundFX {
    private Context context;
    private SoundPool pool;
    private float volume;

    private HashMap<String, Integer> sounds; 
    private HashMap<Integer, ArrayList<Integer>> streams;

    public SoundFX(Context context) {
        this.context = context;
        this.pool = new SoundPool(1, AudioManager.STREAM_MUSIC, 0);
        this.volume = 1.0f;
        this.sounds = new HashMap<String, Integer>();
        this.streams = new HashMap<Integer, ArrayList<Integer>>();
    }

    public Integer load(final String path) {
        if (pool == null) {
            return null;
        }

        Integer soundId = sounds.get(path);
        if (soundId == null) {
            try {
                AssetFileDescriptor afd = context.getAssets().openFd(path);
                soundId = pool.load(afd, 1);
                if (soundId == 0) {
                    return null;
                }
            }
            catch (IOException e) {
                e.printStackTrace();
            }
            sounds.put(path, soundId);
        }

        return soundId;
    }

    public void unload(final String path) {
        if (pool == null) {
            return;
        }

        Integer soundId = sounds.get(path);
        if (soundId != null) {
            pool.unload(soundId);
            sounds.remove(path);
        }
    }

    public void play(final String path, final int group) {
        Integer soundId = load(path);
        if (soundId == null) {
            return;
        }

        Integer streamId = pool.play(soundId, volume, volume, 1, 0, 1.0f);
        if (streamId == 0) {
            return;
        }

        ArrayList<Integer> l = streams.get(group);
        if (l == null) {
            l = new ArrayList<Integer>();
            streams.put(group, l);
        }
        l.add(streamId);
    }

    public void setVolume(final float value) {
        volume = value;

        if (pool != null) {
            for (Entry<Integer, ArrayList<Integer>> entry : streams.entrySet()) {
                for (Integer streamId : entry.getValue()) {
                    pool.setVolume(streamId, value, value);
                }
            }
        }
    }

    public void pause() {
        if (pool != null) {
            pool.autoPause();
        }
    }

    public void resume() {
        if (pool != null) {
            pool.autoResume();
        }
    }

    public void destroy() {
        if (pool != null) {
            pool.release();
            pool = null;
        }
    }
}