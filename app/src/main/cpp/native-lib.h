#include <jni.h>
#include "string.h"
//
// Created by Administrator on 2018/9/21.
//

#ifndef TEST01_NATIVE_LIB_H
#define TEST01_NATIVE_LIB_H

JNIEXPORT void JNICALL
Java_com_luck_lib_security_internal_NativeLib_initBox(JNIEnv *env, jobject instance,
                                                      jstring picPath_,
                                                      jstring jsonFilePath_,
                                                      jstring identifier_);

JNIEXPORT void JNICALL
Java_com_luck_lib_security_internal_NativeLib_encryptsKeyValue(JNIEnv *env, jobject instance,
                                                               jstring key_,
                                                               jstring val_);

JNIEXPORT jstring JNICALL
Java_com_luck_lib_security_internal_NativeLib_decryptsValue(JNIEnv *env, jobject instance,
                                                            jstring key_);

#endif //TEST01_NATIVE_LIB_H
