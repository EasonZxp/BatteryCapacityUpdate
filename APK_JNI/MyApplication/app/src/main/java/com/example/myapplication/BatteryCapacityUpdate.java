package com.example.myapplication;

import android.content.Context;
import android.os.BatteryManager;
import android.util.Log;

class BatteryCapacityUpdate {
    private static final String TAG = "BatteryCapacityUpdate";
    private static BatteryCapacityUpdate instance;
    private UsbGadgetHid usbHid;
    private byte COD_SEND_BAT_LEVEL = 0x11;
    private byte[] payload = {0};
    private BatteryManager batManager;

    private BatteryCapacityUpdate(Context context){
        batManager = (BatteryManager) context.getSystemService(Context.BATTERY_SERVICE);
        usbHid = new UsbGadgetHid();
    }

    static BatteryCapacityUpdate getInstance(Context context){
        if (instance == null) {
            instance = new BatteryCapacityUpdate(context);
        }
        return instance;
    }

    private int getBatteryCapacity(){
        return batManager.getIntProperty(BatteryManager.BATTERY_PROPERTY_CAPACITY);
    }

    boolean sendBatteryCapacity(){
        int ret = 0;

        ret = usbHid.open();
        if(ret != 0){
            Log.e(TAG, "usb hid dev node open failed.");
            return false;
        }

        payload[0] = (byte)getBatteryCapacity();

        ret = usbHid.hidSend(COD_SEND_BAT_LEVEL, payload);
        if(ret != 0){
            Log.e(TAG, "usb hid send failed, ret: " + ret);
            return false;
        }

        usbHid.close();
        return true;
    }
}
