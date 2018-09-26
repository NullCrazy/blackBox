//
//  DecodeImageDemo
//
//  Created by qiuximou on 2018/9/4.
//  Copyright © 2018年 jryx. All rights reserved.
//

#include "../imageSteganography/EdecodeBmp.hpp"
#include <cmath>

//BMP文件头（14字节）
//位图信息头（40字节）
//当biBitCount=24时，1个像素占3个字节,按顺序分别为B,G,R；
//当biBitCount=32时，1个像素占4个字节,按顺序分别为B,G,R,A?

const int picHeadSize = 54;

int setBMPFileSecret(string inputPicPath, string inputStr, string outputPicPath) {

    int textSize = (int) inputStr.size();
    if (textSize == 0) {
        puts("没有字符");
        return 1;
    }

    ifstream pic(inputPicPath);
    if (!pic.is_open()) {
        perror("file open fail");
        return 3;
    }
    string pictureStr;
    string stemp;
    while (getline(pic, stemp)) {
        pictureStr += stemp;
        stemp.clear();
    }

    //获取位数
    int biBitCount = (int) pictureStr[28];
    int colorSize = 0;
    if (biBitCount < 24) {
        colorSize = pow(2, biBitCount);
    }
    int picSize = (int) pictureStr.size();

    int count = (picSize - picHeadSize - colorSize) / 8;

    if (textSize > count || textSize > 127 * 127) {//超过最大长度
        return 2;
    }


    pictureStr[6] = textSize / 127;//
    pictureStr[7] = textSize % 127;            //记录隐藏信息的长度到保留区中

    int ty = (picSize - picHeadSize) / (textSize * 8);  //计算间隔
    for (int i = picHeadSize, j = 0; j != textSize; ++j) {
        //把隐藏的信息转化成bit，写入到间隔的字节的最后一位。
        bitset<8> bt(inputStr[j]);
        for (int k = 0; k != 8; k++) {
            if (bt[8 - k - 1] == true) pictureStr[i] |= 1;
            else pictureStr[i] &= ~1;
            i += ty;
        }
    }
    ofstream out(outputPicPath);
    out << pictureStr << endl;
    pic.close();          //关闭文件流
    out.close();
    return 0;
}

int getPicContainerMaxSize(string inputPicPath) {
    ifstream pic(inputPicPath);
    if (!pic.is_open()) {
        perror("file open fail");
        return -1;
    }
    string stemp;
    string pictureStr;
    while (getline(pic, stemp)) {
        pictureStr += stemp;
        stemp.clear();
    }

    //获取位数
    int biBitCount = (int) pictureStr[28];
    int colorSize = 0;
    if (biBitCount < 24) {
        colorSize = pow(2, biBitCount);
    }
    int picSize = (int) pictureStr.size();

    int count = (picSize - picHeadSize - colorSize) / 8;
    return count;
}


string getBMPSecret(string picPath) {
    ifstream pic(picPath);
    string pictureStr;
    if (!pic.is_open()) {
        printf("文件打开失败");
        return "";
    }
    string stemp1;
    while (getline(pic, stemp1)) {
        pictureStr += stemp1;
    }

    //获取位数
    int biBitCount = (int) pictureStr[28];
    int colorSize = 0;
    if (biBitCount < 24) {
        colorSize = pow(2, biBitCount);
    }

    int picSize = (int) pictureStr.size();
    //从保留区提取出隐藏信息的长度
    int strLength = (pictureStr[6] * 127) + pictureStr[7];
    if (strLength <= 0) {
        return "";
    }
    //计算间隔
    int ty = (picSize - picHeadSize - colorSize) / (strLength * 8);

    char temp = 0;
    stringstream strStream; //获取字符串流
    string result;

    for (int i = picHeadSize + colorSize, j = 0; j != strLength; ++j) {
        //提取每个隐写字节末尾的bit，然后重组成隐藏信息。

        temp = 0;
        for (int k = 0; k != 8; k++) {
            temp <<= 1;
            temp += bitset<8>(pictureStr[i])[0];
            i += ty;
//            printf("----%c",temp);
        }
        cout << temp;
        strStream << temp;
    }
    result = strStream.str();
    pic.close();
    return result;
}
