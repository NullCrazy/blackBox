//
//  LCJsonStorage.cpp
//  EncodeFileTest
//
//  Created by qiuximou on 2018/9/15.
//  Copyright © 2018年 jryx. All rights reserved.
//

#include "LCJsonStorage.hpp"

static const string fileFormat = "/defaultAccount.json";
//包含加密内容文件，含有文件名后缀
static string secretContentFilePath;
//文件路径，无后缀
static string contentFilePath;

string getJsonStringFromFile(string filePath, string encryptKey);
bool outputJsonToFile(string filePath, Json::FastWriter writer, Json::Value root, string encryptKey);

#pragma mark pulbic method

bool initJsonStoreFile(string filePath,string encryptKey) {
    if (!filePath.size()) {
        return false;
    }
#pragma clang diagnostic push
#pragma clang diagnostic ignored"-Wdeprecated-declarations"
    Json::Value root;
    Json::Reader reader;
    Json::FastWriter sw;
#pragma clang diagnostic pop
    string finalFilePath = filePath + fileFormat;
    secretContentFilePath = finalFilePath;
    contentFilePath = filePath;
    //直接判断文件是否存在,存在则不重新初始化，没有初始化，防止重复初始化
    ifstream in(finalFilePath, ios::binary);
    if(!in.is_open())
    {
        //没有初始化
        cout << "no opening file\n";
        //初始化根节点属性，只是为了占位用;
        root["version"] = Json::Value(true);
        in.close();
        //输出到文件
        return outputJsonToFile(secretContentFilePath, sw, root, encryptKey);
    } else {
        return true;
    }
}

string readJsonFromStorageFileForKey(string key, string encryptKey) {

    if (!secretContentFilePath.size() || !key.size()) {
        return "";
    }
    ifstream reader(secretContentFilePath,ios::binary);
    if (!reader.is_open()) {
        //首次读取无文件则创建文件
        bool success = initJsonStoreFile(contentFilePath + fileFormat, encryptKey);
        if (success) {
            string encrypt = readJsonFromStorageFileForKey(key, encryptKey);
            return encrypt;
        }
        return "";
    }
#pragma clang diagnostic push
#pragma clang diagnostic ignored"-Wdeprecated-declarations"
    Json::Reader jsonReader;
#pragma clang diagnostic pop
    Json::Value value;
    ostringstream strBuffer;
    char ch;
    while (strBuffer && reader.get(ch)) {
        strBuffer.put(ch);
    }
    string decrptStr = decrypts(encryptKey, strBuffer.str());
    string retureValue;
    if (decrptStr.size()) {
        if (jsonReader.parse(decrptStr,value)) {
            retureValue = value[key].asString();
        }
    }
    return retureValue;
}

bool writeJsonValueForKey(string value, string key, string encryptKey) {

    if (!secretContentFilePath.size() || !key.size()) {
        return false;
    }
#pragma clang diagnostic push
#pragma clang diagnostic ignored"-Wdeprecated-declarations"
    Json::Reader reader;
    Json::Value root;
    Json::FastWriter sw;
    Json::Value::Members members;
#pragma clang diagnostic pop
    string decryptStr = getJsonStringFromFile(secretContentFilePath, encryptKey);
    if (!reader.parse(decryptStr, root,false)) {
        return false;
    }
    //遍历存储在文件中json字符串中原有的key及对应的值
    members = root.getMemberNames();
    for (Json::Value::Members::iterator iterMember = members.begin(); iterMember != members.end(); iterMember++) {
        string strKey = *iterMember;
        if (root[strKey.c_str()].isString()) {
            root[strKey.c_str()] = root[strKey.c_str()].asString();
        } else if (root[strKey.c_str()].isBool()) {
            root[strKey.c_str()] = root[strKey.c_str()].asBool();
        }
    }
    //拼接上新值
    root[key] = Json::Value(value);
    cout << "FastWriter:" << endl;
    cout << sw.write(root) << endl << endl;
    //输出到文件
    return outputJsonToFile(secretContentFilePath, sw, root, encryptKey);
}


#pragma mark private method--私有方法
/**
 获取文件中json字符串

 @param filePath 文件路径
 @param encryptKey 加解密secret
 @return 返回值
 */
string getJsonStringFromFile(string filePath, string encryptKey) {
    ifstream in(filePath, ios::binary);
    if(!in.is_open() )
    {
        cout << "Error opening file\n";
        in.close();
        return "";
    }
    //字符缓冲区
    ostringstream strBuffer;
    char ch;
    while (strBuffer && in.get(ch)) {
        strBuffer.put(ch);
    }
    //返回解密后的json字符串
    string decryptStr = decrypts(encryptKey, strBuffer.str());
    in.close();
    return decryptStr;
}


/**
 输出json文件

 @param filePath 文件路径
 @param writer json写入器
 @param root <#root description#>
 @param encryptKey 加解密值
 @return 返回值
 */
bool outputJsonToFile(string filePath, Json::FastWriter writer, Json::Value root, string encryptKey) {
    ofstream os;
    os.open(filePath);
    if (os.is_open()) {
        string tempStr = writer.write(root);
        string encryptStr = encrypts(encryptKey, tempStr);
        os << encryptStr;
        os.close();
        return true;
    }
    os.close();
    return false;
}
