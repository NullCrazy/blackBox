//
//  LCJsonStorage.hpp
//  EncodeFileTest
//
//  Created by qiuximou on 2018/9/15.
//  Copyright © 2018年 jryx. All rights reserved.
//

#ifndef LCJsonStorage_hpp
#define LCJsonStorage_hpp

#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "../json/json.h"
#include "../AES/AESTool.hpp"

using namespace std;
using namespace Json;

/**
 初始化json存储文件
 
 @param filePath 文件存储路径
 @return 创建成功标志位
 */
bool initJsonStoreFile(string filePath, string encryptKey);


/**
 读取文件中特定的值

 @param key 传入的key
 @param encryptKey 解密key
 @return 返回解密后的值
 */
string readJsonFromStorageFileForKey(string key, string encryptKey);

/**
  写值到文件中

  @param value 写入的值
  @param key 对应的key
  @param encryptKey 加密key
  @return 成功标志位
  */

bool writeJsonValueForKey(string value, string key, string encryptKey);


#endif /* LCJsonStorage_hpp */
