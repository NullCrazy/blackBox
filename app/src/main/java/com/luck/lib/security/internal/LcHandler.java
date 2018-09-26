package com.luck.lib.security.internal;

public class LcHandler {
    protected NativeLib mNativeLib;

    public LcHandler(String secretImgPatch, String secretTextPatch, String identifier) {
        mNativeLib = new NativeLib();
        mNativeLib.initBox(secretImgPatch, secretTextPatch, identifier);
    }

    /**
     * 把数据动态存入黑盒
     *
     * @param key
     * @param value
     * @return 加密后的数据
     */
    public synchronized void saveBoxKeyValue(String key, String value) {
        mNativeLib.encryptsKeyValue(key, value);
    }

    /**
     * 获取对应key解密后的内容
     *
     * @param key
     * @return 解密后的内容
     */
    public synchronized String getDecryptsValue(String key) {
        return mNativeLib.decryptsValue(key);
    }
}
