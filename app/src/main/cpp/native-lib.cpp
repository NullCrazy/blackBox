#include <jni.h>
#include "LuckinXxaaxxMain/BYUJhIpYsodLgizj.hpp"
#include <android/log.h>
#define LOG_TAG "System.out"
#define LOGD(...)__android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

extern "C"
JNIEXPORT void JNICALL
Java_com_luck_lib_security_internal_NativeLib_initBox(JNIEnv *env, jobject instance,
                                                      jstring picPath_,
                                                      jstring jsonFilePath_,
                                                      jstring identifier_) {
    const char *picPath = env->GetStringUTFChars(picPath_, 0);
    const char *jsonFilePath = env->GetStringUTFChars(jsonFilePath_, 0);
    const char *identifier = env->GetStringUTFChars(identifier_, 0);
    LOGD("initBox:%s", picPath);
    LOGD("initBox:%s", jsonFilePath);
    LOGD("initBox:%s", identifier);
    bool result = LXJnHeecVKJYZAik(picPath, jsonFilePath, identifier);
    LOGD("init:%d", result);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_luck_lib_security_internal_NativeLib_encryptsKeyValue(JNIEnv *env, jobject instance,
                                                               jstring key_,
                                                               jstring val_) {
    const char *key = env->GetStringUTFChars(key_, 0);
    const char *val = env->GetStringUTFChars(val_, 0);
    bool result = MwZKCaGavjcfKMUU(val, key);

    LOGD("encry:%d", result);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_luck_lib_security_internal_NativeLib_decryptsValue(JNIEnv *env, jobject instance,
                                                            jstring key_) {
    const char *key = env->GetStringUTFChars(key_, 0);
    return env->NewStringUTF(yxDwKILNAcJOvzZW(key).c_str());
}