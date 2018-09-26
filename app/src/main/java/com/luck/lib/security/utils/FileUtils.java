package com.luck.lib.security.utils;

import android.content.Context;
import android.util.Log;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

public final class FileUtils {

    /**
     * 复制assets下的文件到指定目录
     *
     * @param context
     * @param fileName 文件名称
     * @param newPath
     */
    public static void copyFilesAssets(Context context, String fileName, String newPath) {
        InputStream is = null;
        FileOutputStream fos = null;
        try {
            File file = new File(newPath);

            is = context.getAssets().open(fileName);
            fos = new FileOutputStream(file);
            byte[] buffer = new byte[1024];
            int byteCount;
            while ((byteCount = is.read(buffer)) != -1) {//循环从输入流读取 buffer字节
                fos.write(buffer, 0, byteCount);//将读取的输入流写入到输出流
                Log.e("xmq", buffer.length + "");
            }
        } catch (IOException ex) {
            ex.printStackTrace();
        } finally {
            try {
                if (is != null) {
                    is.close();
                }
                if (fos != null) {
                    fos.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * 检查文件是否存在
     *
     * @param filePatch
     * @return
     */
    public static boolean checkFileExists(String filePatch) {
        File file = new File(filePatch);
        return file.exists();
    }
}