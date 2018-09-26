//
//  BYUJhIpYsodLgizj
//  EncodeFileTest
//
//  Created by Sileen on 2018/9/6.
//  Copyright © 2018年 jryx. All rights reserved.
//

#include "BYUJhIpYsodLgizj.hpp"
#include "BYUJhIpYsodLgizjHeader.h"
#include "../Cache/LCDataCache.h"

static  string picPathStr;
static  string zEgCRXNWkmTRLgMR;

bool initWithDefaultProperty(string encryptKey);
string IPjOIThZjfhSFLmI();

/// MARK: instance box.
bool LXJnHeecVKJYZAik(string picPath, string jsonFilePath, string identifier)
{
    if (picPath.empty() || jsonFilePath.empty()){
        return false;
    }
    picPathStr = picPath;

    //获取黑匣子 secret
    string  zyLrFXgcGIJDKMXz = IPjOIThZjfhSFLmI();
    if(zyLrFXgcGIJDKMXz.size()==0)
    {
        return false;
    }
    
    if (!identifier.empty()){
        zyLrFXgcGIJDKMXz += identifier;
    }
    
    //初始化基础缺省值,常量数据加密存储JSON文件
    bool result = initCache(jsonFilePath,zyLrFXgcGIJDKMXz);
    return result;
}

/// MARK: 获取静态key对应解密过的数据
string getKeyValueWithKey(string keyStr)
{
    string  zyLrFXgcGIJDKMXz = IPjOIThZjfhSFLmI();
    if(zyLrFXgcGIJDKMXz.size()==0)
    {
        return "";
    }
    
    string keyValueStr = getValueForKey(keyStr);
    return keyValueStr;
}

/// MARK: 对key对应value数据进行加密
bool MwZKCaGavjcfKMUU(string keyValue,string keyStr)
{
    string  zyLrFXgcGIJDKMXz = IPjOIThZjfhSFLmI();
    if(zyLrFXgcGIJDKMXz.size()==0)
    {
        return false;
    }
    
    //加密对应key的value
    return setValueForKey(keyValue, keyStr);
}

/// MARK: 对key对应value数据进行解密
string yxDwKILNAcJOvzZW(string keyStr)
{
    string  zyLrFXgcGIJDKMXz = IPjOIThZjfhSFLmI();
    if(zyLrFXgcGIJDKMXz.size()==0)
    {
        return "";
    }
    
    string keyValueStr = getValueForKey(keyStr);
    return keyValueStr;
}

/// MARK:private Interface

//获取黑匣子秘钥，优先从内存中获取，失败从BMP图片读取
string IPjOIThZjfhSFLmI()
{
    if (zEgCRXNWkmTRLgMR.size()==0)
    {
        string  zyLrFXgcGIJDKMXz = getBMPSecret(picPathStr);
        if(zyLrFXgcGIJDKMXz.size()==0)
        {
            return "";
        }
        zEgCRXNWkmTRLgMR = zyLrFXgcGIJDKMXz;
        return zEgCRXNWkmTRLgMR;
    }
    
    return zEgCRXNWkmTRLgMR;
}

