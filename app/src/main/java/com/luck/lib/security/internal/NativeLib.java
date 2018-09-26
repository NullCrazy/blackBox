package com.luck.lib.security.internal;

public class NativeLib {
    static {
        System.loadLibrary("native-lib");
    }

    NativeLib() {
    }

    /**
     * @param picPath      加密图片路径
     * @param jsonFilePath 加密写入的本地json
     */
    native void initBox(String picPath, String jsonFilePath, String identifier);

    /**
     * 加密存储key，value
     *
     * @param key
     * @param val
     * @return
     */
    public native void encryptsKeyValue(String key, String val);


    /**
     * 获取解密后的对应key的内容
     *
     * @param key
     * @return
     */
    public native String decryptsValue(String key);
}
