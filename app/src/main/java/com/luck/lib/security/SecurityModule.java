package com.luck.lib.security;

import android.content.Context;

import com.luck.lib.security.internal.LcHandler;
import com.luck.lib.security.utils.FileUtils;

import java.io.File;

public final class SecurityModule {
    //内部密钥存储的图片路径
    private static final String IMG = "secret.bmp";
    //安全组件内部实现
    private LcHandler mAbsHandler;

    //唯一单例
    private volatile static SecurityModule securityModule;

    private SecurityModule() {
    }

    /**
     * 初始化安全组件
     *
     * @param context
     */
    public void initSecurity(Context context, String identifier) {
        if (mAbsHandler != null) {
            return;
        }

        String filePatchParent = context.getFilesDir().getPath();
        String secretImgPatch = filePatchParent + File.separator + IMG;
        String secretTextPatch = filePatchParent;

        if (!FileUtils.checkFileExists(secretImgPatch)) {
            FileUtils.copyFilesAssets(context, IMG, secretImgPatch);
        }
/*        if (!FileUtils.checkFileExists(secretTextPatch)) {
            FileUtils.copyFilesAssets(context, LOCAL_JSON, secretTextPatch);
        }*/
        mAbsHandler = new LcHandler(secretImgPatch, secretTextPatch, identifier);
    }

    public static SecurityModule getInstance() {
        synchronized (SecurityModule.class) {
            if (securityModule == null) {
                synchronized (SecurityModule.class) {
                    securityModule = new SecurityModule();
                }
            }
        }
        return securityModule;
    }

    public LcHandler getAbsHandler() {
        //检测安全组件没被初始化将抛出空指针异常！
        if (mAbsHandler == null) {
            throw new NullPointerException("NativeLib is Null, Please call initSecurity!!");
        }
        return mAbsHandler;
    }
}
