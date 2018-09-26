package com.luck.lib.security;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.luck.lib.security.internal.LcHandler;

public class MainActivity extends AppCompatActivity {
    private SecurityModule securityModule;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        securityModule = SecurityModule.getInstance();
        securityModule.initSecurity(this, "temp");
        final LcHandler absHandler = securityModule.getAbsHandler();

        findViewById(R.id.jiami).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                absHandler.saveBoxKeyValue("test", "1111111111111111");
                absHandler.getDecryptsValue("test");
            }
        });

        findViewById(R.id.jiemi).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
               /* new Thread(new Runnable() {
                    @Override
                    public void run() {
                        for (int i = 0; i < 10; i++) {
                            String key = "test" + Math.random();
                            absHandler.saveBoxKeyValue(key, key + "aaaaasadasdasdasdasdasdasassssssssvvvdasdasdasdasdasdasvvvvvvvvvvvv1111asdasdasdas111111111111");
                            Log.i("System.out", absHandler.getDecryptsValue(key));
                        }
                    }
                }).start();*/
                Log.i("System.out", absHandler.getDecryptsValue("test"));
            }
        });
    }
}
