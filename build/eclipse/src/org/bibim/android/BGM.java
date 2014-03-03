package org.bibim.android;

import java.io.IOException;
import java.util.ArrayList;
import android.content.Context;
import android.content.res.AssetFileDescriptor;
import android.media.AudioManager;
import android.media.MediaPlayer;

public final class BGM {
    private Context context;
    private MediaPlayer player;
    private float volume;

    public BGM(Context context) {
        this.context = context;
        this.player = null;
        this.volume = 1.0f;
    }

    public void play(final String path) {
        if (player != null && player.isPlaying()) {
            player.stop();
            player.release();
            player = null;
        }

        if (path != null && !path.isEmpty()) {
            try {
                AssetFileDescriptor afd = context.getAssets().openFd(path);
                player = new MediaPlayer();
                player.setDataSource(afd.getFileDescriptor(), afd.getStartOffset(), afd.getLength());
                afd.close();
                player.setAudioStreamType(AudioManager.STREAM_MUSIC);
                player.prepare();
                player.setVolume(volume, volume);
                player.setLooping(true);
                player.start();
            }
            catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public void setVolume(final float value) {
        volume = value;

        if (player != null) {
            player.setVolume(value, value);
        }
    }

    public void pause() {
        if (player != null) {
            player.pause();
        }
    }

    public void resume() {
        if (player != null) {
            player.start();
        }
    }

    public void destroy() {
        if (player != null) {
            player.release();
            player = null;
        }
    }
}
