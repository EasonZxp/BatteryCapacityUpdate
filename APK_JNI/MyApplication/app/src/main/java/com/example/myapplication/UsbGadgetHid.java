package com.example.myapplication;

public class UsbGadgetHid{
    static {
        System.loadLibrary("UsbGadgetHidJni");
    }

    public native int open();
    public native void close();
    public native int hidSend(byte cmd, byte[] payload);
}