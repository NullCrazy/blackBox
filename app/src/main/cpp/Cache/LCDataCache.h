//
// Created by Administrator on 2018/9/6.
//

#ifndef MYAPPLICATION7_CACHE_DATA_H
#define MYAPPLICATION7_CACHE_DATA_H

#include "stdio.h"
#include <string>

using namespace std;
/**
 初始化缓存

 @param filePath 加密json存储文件路径，为空直接初始化失败
 @param encryptKey 密钥，为空直接初始化失败
 @return 是否成功
 */

bool initCache(string filePath,string encryptKey);


/**
 获取值

 @param keyStr 键
 @return 解密失败或者获取不到返回空字符串
 */
string getValueForKey(string keyStr);


/**
 存储值

 @param value 值，可以为空字符串，传入空字符串时会删除这个值
 @param keyStr 重复的 键 直接覆盖，不能为空，空直接失败
 @return 成功或失败
 */
bool setValueForKey(string value,string keyStr);


#endif //MYAPPLICATION7_CACHE_DATA_H
