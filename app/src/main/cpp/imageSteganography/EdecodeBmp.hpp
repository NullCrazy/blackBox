//
//  DecodeBmpFile.hpp
//  DecodeImageDemo
//
//  Created by qiuximou on 2018/9/4.
//  Copyright © 2018年 jryx. All rights reserved.
//

#ifndef EdecodeBmp_hpp
#define EdecodeBmp_hpp
#include<stdio.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <cstdlib>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

/**
 获取图片能存储的字符串长度（按C字符个数计算）
 
 @param inputPicPath 图片路径
 @return int 字符数（-1为文件打开失败）
 */
int getPicContainerMaxSize(string inputPicPath);


/**
 获取bmp图片中隐写的信息

 @param picPath 含有隐写信息的图片
 @return 返回隐写信息信息
 */
string getBMPSecret(string picPath);


/**
 保存字符串到图片中

 @param inputPicPath 输入文件路径
 @param inputStr 需要隐写的字符串
 @param outputPicPath 输出的文件路径
 @return code
 code
 0:成功
 1:字符串为空
 2:字符串超过图片能存储的长度
 3:图片文件打开失败
 */
int setBMPFileSecret(string inputPicPath, string inputStr, string outputPicPath);

#endif /* DecodeBmpFile_hpp */
