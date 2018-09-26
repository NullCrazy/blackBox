//
// Created by Administrator on 2018/9/6.
//
#include "LCDataCache.h"
#include "string.h"
#include "../jsonStore/LCJsonStorage.hpp"
// 这个是自定义的LOG的标识
#define TAG "TAGS"
// 定义LOGD类型
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__)

struct node {
    string key;
    string val;
    struct node *next;
};

node *head = NULL;

static string staticFilePath;
static string staticEncryptKey;

char *stringToChar(string value) {
    //    newKey = new char[strlen(key) + 1];
    //    strcpy(newKey, key);
    //    insertNode(newKey, localVal);
    char *cValue;
    long length = value.length();
    cValue = (char *) malloc((length + 1) * sizeof(char));
    value.copy(cValue, length, 0);
    return cValue;
}


//检查鍵是否重复，如果重复则会覆盖原有值
bool updateNode(string key, string val) {
    node *ch = head;
    while (NULL != ch) {
        if (strcmp(key.c_str(), (ch->key).c_str()) == 0) {
            ch->val = val;
            return true;
        }
        ch = ch->next;
    }
    return false;
}

void insertNode(string keyStr, string valueStr) {
    //检查鍵是否重复，如果重复则会覆盖原有值，否则插入节点
    if (updateNode(keyStr, valueStr)) {
        return;
    }
    node *p = head;
    node *data = new node;
    data->key = keyStr;
    data->val = valueStr;
    head = data;
    data->next = p;
}

bool deleteNode(string key) {
    node *p = head;
    node *temp = NULL;
    while (NULL != p) {
        if (strcmp(key.c_str(), (p->key).c_str()) == 0) {
            if (temp != NULL) {
                if (p->next != NULL) {
                    temp->next = p->next;
                } else {
                    temp->next = NULL;
                }
            } else {
                head = p->next;
            }
            delete p;
            return true;
        } else {
            temp = p;
            p = p->next;
        }
    }
    return false;
}

bool initCache(string filePath, string encryptKey) {
    if (filePath.empty() || encryptKey.empty()) {
        return false;
    }
    staticFilePath = filePath;
    staticEncryptKey = encryptKey;
    return initJsonStoreFile(filePath, encryptKey);
}

string getValueForKey(string keyStr) {
    
    if (keyStr.empty() || staticEncryptKey.empty()) {
        return "";
    }

    const char *key = keyStr.c_str();
    node *p = head;
    while (NULL != p) {//先查找內存中是否存在，存在則直接返回
        if (strcmp(key, (p->key).c_str()) == 0) {
            return p->val;
        }
        p = p->next;
    }

    if (staticFilePath.empty()) {//需要操作文件再判断
        return "";
    }
    string result = readJsonFromStorageFileForKey(keyStr, staticEncryptKey);
    insertNode(keyStr, result);
    return result;
}

bool setValueForKey(string value, string keyStr) {

    if (keyStr.empty() || staticEncryptKey.empty() || staticFilePath.empty()) {
        return false;
    }

//    if (value.empty()) {//值为空删除值
//        return deleteNode(keyStr);
//    }

    insertNode(keyStr, value);

    writeJsonValueForKey(value, keyStr, staticEncryptKey);
    return true;
}

