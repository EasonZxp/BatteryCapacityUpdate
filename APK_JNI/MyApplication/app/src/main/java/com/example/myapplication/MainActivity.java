package com.example.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    private Button btnSendBatInfo;
    private BatteryCapacityUpdate batCapUpdate;
    private static final String TAG = "BatteryCapacityUpdate";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        batCapUpdate = BatteryCapacityUpdate.getInstance(this);
        btnSendBatInfo = findViewById(R.id.btn_send);
        btnSendBatInfo.setOnClickListener(this);

    }

    @Override
    public void onClick(View v) {
        if(v == btnSendBatInfo){
            new Thread(){
                @Override
                public void run() {
                    super.run();
                    if(!batCapUpdate.sendBatteryCapacity()){
                        Log.e(TAG, "sendBatteryCapacity failed.");
                    }
                }
            }.start();
        }
    }
}
