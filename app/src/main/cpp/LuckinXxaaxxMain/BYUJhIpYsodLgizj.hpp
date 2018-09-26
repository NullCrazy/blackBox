//
//  LuckinXxaaxx.hpp
//  EncodeFileTest
//  Black box Public Interface.
//
//  Created by Sileen on 2018/9/6.
//  Copyright © 2018年 jryx. All rights reserved.
//

#ifndef BYUJhIpYsodLgizj_hpp
#define BYUJhIpYsodLgizj_hpp

#include <stdio.h>
#include <string>
#include <stdint.h>

using namespace std;

/**
 名称混淆说明：
 #define instanceBlackbox LXJnHeecVKJYZAik
 #define LuckinBlackbox BYUJhIpYsodLgizj
 #define getKeyValueWithKey lXRkGxwhRDlkEntY
 #define getEncryDataWithKey MwZKCaGavjcfKMUU
 #define getDecryDataWithKey yxDwKILNAcJOvzZW
 #define getBlackboxSecret IPjOIThZjfhSFLmI
 #define blackboxSecret zEgCRXNWkmTRLgMR
 #define aaxxSecret zyLrFXgcGIJDKMXz

 
 */

/**
 初始化黑匣子服务
 
 @param picPath       存储的BMP图片的路径
 @param jsonFilePath  加密后数据存储JSON文件路径
 @param identifier    设备唯一id，拼接到密钥之中，传空字符串则不拼接（防止文件转移）
 @return              true：成功，false：失败
 */
bool LXJnHeecVKJYZAik(string picPath, string jsonFilePath, string identifier);

/**
 获取key对应加密过的数据
 
 @param keyStr        对应加密数据的key值
 @return              keyValue对应加密的数据string
 */
string lXRkGxwhRDlkEntY(string keyStr);

/**
 对key对应value数据进行加密
 
 @param keyValue        需加密数据的keyValue值
 @param keyStr          需加密数据的key值
 @return                keyValue对应加密过的数据
 */
bool MwZKCaGavjcfKMUU(string keyValue,string keyStr);

/**
 对key对应value数据进行解密
 
 @param keyStr        需解密数据的key值
 @return              keyValue对应加密的数据
 */
string yxDwKILNAcJOvzZW(string keyStr);


#endif /* BYUJhIpYsodLgizj_hpp */

