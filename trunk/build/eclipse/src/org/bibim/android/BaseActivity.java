package org.bibim.android;

import android.app.Activity;
import android.os.Bundle;

public class BaseActivity extends Activity {
    public static BaseActivity activity;
    
    private SurfaceView view;
    private BGM bgm;
    private SoundFX sfx;
    
    public SurfaceView getSurfaceView() {
        return view;
    }

    public BGM getBgm() {
        return bgm;
    }

    public SoundFX getSfx() {
        return sfx;
    }

    @Override
    protected void onCreate(Bundle icicle) {
        super.onCreate(icicle);
        
        activity = this;
        view = createSurfaceView();
        setContentView(view);
        bgm = new BGM(getApplication());
        sfx = new SoundFX(getApplication());
    }

    @Override
    protected void onPause() {
        super.onPause();
        view.onPause();
        bgm.pause();
        sfx.pause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        view.onResume();
        bgm.resume();
        sfx.resume();
    }

    @Override
    protected void onDestroy() {
        bgm.destroy();
        sfx.destroy();
        view.destroy();
        super.onDestroy();
    }
    
    protected SurfaceView createSurfaceView() {
        return new SurfaceView(getApplication());
    }
}
