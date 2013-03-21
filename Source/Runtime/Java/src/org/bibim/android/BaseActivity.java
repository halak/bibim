package org.bibim.android;

import android.app.Activity;
import android.os.Bundle;

public class BaseActivity extends Activity {
    private SurfaceView view;

    @Override
    protected void onCreate(Bundle icicle) {
        super.onCreate(icicle);
        
        view = createSurfaceView();
        setContentView(view);
    }

    @Override
    protected void onPause() {
        super.onPause();
        view.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        view.onResume();
    }
    
    protected SurfaceView createSurfaceView() {
    	return new SurfaceView(getApplication());
    }
}
