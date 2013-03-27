package org.bibim.android;

import android.app.Activity;
import android.os.Bundle;

public class BaseActivity extends Activity {
	public static BaseActivity activity;
	
    private SurfaceView view;
    
    public SurfaceView getSurfaceView() {
    	return view;
    }

    @Override
    protected void onCreate(Bundle icicle) {
        super.onCreate(icicle);
        
        activity = this;
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
