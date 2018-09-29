// jni头文件 
#include <jni.h>

#include <cassert>
#include <cstdlib>
#include <iostream>
#include "LuckinXxaaxxMain/BYUJhIpYsodLgizj.hpp"
#include "android/log.h"

#define LOG_TAG "System.out"
#define LOGD(...)__android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace std;

//native 方法实现
__attribute__((section (".mytext"))) JNICALL void init(JNIEnv *env, jobject,
                                                       jstring picPath_,
                                                       jstring jsonFilePath_,
                                                       jstring identifier_) {
    const char *picPath = env->GetStringUTFChars(picPath_, 0);
    const char *jsonFilePath = env->GetStringUTFChars(jsonFilePath_, 0);
    const char *identifier = env->GetStringUTFChars(identifier_, 0);
    bool result = LXJnHeecVKJYZAik(picPath, jsonFilePath, identifier);
    LOGD("init:%d", result);
}

__attribute__((section (".mytext"))) JNICALL void encrypts(JNIEnv *env, jobject,
                                                           jstring key_,
                                                           jstring val_) {
    const char *key = env->GetStringUTFChars(key_, 0);
    const char *val = env->GetStringUTFChars(val_, 0);
    bool result = MwZKCaGavjcfKMUU(val, key);
    LOGD("encry:%d", result);
}

__attribute__((section (".mytext"))) JNICALL jstring decrypts(JNIEnv *env, jobject,
                                                              jstring key_) {
    const char *key = env->GetStringUTFChars(key_, 0);
    return env->NewStringUTF(yxDwKILNAcJOvzZW(key).c_str());
}

/*需要注册的函数列表，放在JNINativeMethod 类型的数组中，
以后如果需要增加函数，只需在这里添加就行了
参数：
1.java代码中用native关键字声明的函数名字符串
2.签名（传进来参数类型和返回值类型的说明） 
3.C/C++中对应函数的函数名（地址）
*/
static JNINativeMethod getMethods[] = {
        {"initBox",          "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", (void *) init},
        {"encryptsKeyValue", "(Ljava/lang/String;Ljava/lang/String;)V",                   (void *) encrypts},
        {"decryptsValue",    "(Ljava/lang/String;)Ljava/lang/String;",                    (void *) decrypts},
};

//此函数通过调用JNI中 RegisterNatives 方法来注册我们的函数
static int registerNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *getMethods,
                                 int methodsNum) {
    jclass clazz;
    //找到声明native方法的类
    clazz = env->FindClass(className);
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    //注册函数 参数：java类 所要注册的函数数组 注册函数的个数
    if (env->RegisterNatives(clazz, getMethods, methodsNum) < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

static int registerNatives(JNIEnv *env) {
    //指定类的路径，通过FindClass 方法来找到对应的类
    const char *className = "com/luck/lib/security/internal/NativeLib";
    return registerNativeMethods(env, className, getMethods,
                                 sizeof(getMethods) / sizeof(getMethods[0]));
}
//回调函数 在这里面注册函数
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    //判断虚拟机状态是否有问题
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    assert(env != NULL);
    //开始注册函数 registerNatives -》registerNativeMethods -》env->RegisterNatives
    if (!registerNatives(env)) {
        return -1;
    }
    //返回jni 的版本 
    return JNI_VERSION_1_6;
}
