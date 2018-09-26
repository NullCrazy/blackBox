//
//  AESTool.cpp
//  EncodeFileTest
//
//  Created by Tony Gao on 2018/9/6.
//  Copyright © 2018 Tony Gao. All rights reserved.
//

#include "AESTool.hpp"
#include "aes.h"
#include "zbase64.h"
#define KEYCODELENGTH 16

void Padding( unsigned char* pSrc, int nSrcLen )
{
    if( nSrcLen < KEYCODELENGTH )
    {
        unsigned char ucPad = KEYCODELENGTH - nSrcLen;
        for( int nID = KEYCODELENGTH; nID > nSrcLen; --nID )
        {
            pSrc[nID - 1] = ucPad;
        }
    }
}

void StringToHex(const char* pSrc, unsigned char* pDest, int nDestLen)
{
    int nSrcLen = 0;
    if( pSrc != 0 )
    {
        nSrcLen = (int)strlen(pSrc);
        memcpy(pDest, pSrc, nSrcLen > nDestLen ? nDestLen : nSrcLen);
    }
    Padding(pDest, nSrcLen > nDestLen ? nDestLen : nSrcLen);
}

bool is_str_utf8(const char* str)
{
    unsigned int nBytes = 0;//UFT8可用1-6个字节编码,ASCII用一个字节
    unsigned char chr = *str;
    bool bAllAscii = true;
    
    for (unsigned int i = 0; str[i] != '\0'; ++i){
        chr = *(str + i);
        //判断是否ASCII编码,如果不是,说明有可能是UTF8,ASCII用7位编码,最高位标记为0,0xxxxxxx
        if (nBytes == 0 && (chr & 0x80) != 0){
            bAllAscii = false;
        }
        
        if (nBytes == 0) {
            //如果不是ASCII码,应该是多字节符,计算字节数
            if (chr >= 0x80) {
                
                if (chr >= 0xFC && chr <= 0xFD){
                    nBytes = 6;
                }
                else if (chr >= 0xF8){
                    nBytes = 5;
                }
                else if (chr >= 0xF0){
                    nBytes = 4;
                }
                else if (chr >= 0xE0){
                    nBytes = 3;
                }
                else if (chr >= 0xC0){
                    nBytes = 2;
                }
                else{
                    return false;
                }
                
                nBytes--;
            }
        }
        else{
            //多字节符的非首字节,应为 10xxxxxx
            if ((chr & 0xC0) != 0x80){
                return false;
            }
            //减到为零为止
            nBytes--;
        }
    }
    
    //违返UTF8编码规则
    if (nBytes != 0)  {
        return false;
    }
    
    if (bAllAscii){ //如果全部都是ASCII, 也是UTF8
        return true;
    }
    
    return true;
}

string encrypts(string strKey, string strSrc)
{
    ZBase64 tool;
    aes_context ctx;
    const char* pSrc = 0;
    const char* pTmpSrc = 0;
    unsigned char* pDest = 0;
    unsigned char* pTmpDest = 0;
    int nSrcLen = 0;
    int nDestLen = 0;
    unsigned char buf[KEYCODELENGTH];
    unsigned char key[KEYCODELENGTH];
    StringToHex( strKey.c_str(), key, KEYCODELENGTH );
    aes_set_key( &ctx, key, 128);
    pSrc = strSrc.c_str();
    nSrcLen = (int)strSrc.size();
    nDestLen = (nSrcLen / KEYCODELENGTH) * KEYCODELENGTH + KEYCODELENGTH;
    pDest = new unsigned char[nDestLen];
    memset( pDest, 0, nDestLen );
    pTmpSrc = pSrc;
    pTmpDest = pDest;
    while( (pTmpSrc - pSrc) < nSrcLen )
    {
        StringToHex(pTmpSrc, buf, KEYCODELENGTH);
        aes_encrypt( &ctx, buf, buf );
        memcpy( pTmpDest, buf, KEYCODELENGTH );
        pTmpSrc += KEYCODELENGTH;
        pTmpDest += KEYCODELENGTH;
    }
    if( (pTmpDest - pDest) < nDestLen )    // if the source size % KEYCODELENGTH == 0 then need to add an extra buffer
    {
        StringToHex(0, buf, KEYCODELENGTH);
        aes_encrypt( &ctx, buf, buf );
        memcpy( pTmpDest, buf, KEYCODELENGTH );
    }
    
    string strRet = tool.Encode(pDest, nDestLen);
    delete [] pDest;
    return strRet;
}
string decrypts(string strKey, string strSrc)
{
    ZBase64 tool;
    aes_context ctx;
    const char* pSrc = 0;
    const char* pTmpSrc = 0;
    unsigned char* pDest = 0;
    unsigned char* pTmpDest = 0;
    int nSrcLen = 0;
    int nDestLen = 0;
    unsigned char buf[KEYCODELENGTH];
    unsigned char key[KEYCODELENGTH];
    StringToHex(strKey.c_str(), key, KEYCODELENGTH);
    aes_set_key( &ctx, key, 128);
    string strSrcHex = tool.Decode(strSrc.c_str(), (int)strSrc.size(), nSrcLen);
    pSrc = strSrcHex.data();
    nDestLen = nSrcLen;
    pDest = new unsigned char[nDestLen];
    memset( pDest, 0, nDestLen );
    pTmpSrc = pSrc;
    pTmpDest = pDest;
    while( (pTmpSrc - pSrc) < nSrcLen )
    {
        memcpy(buf, pTmpSrc, KEYCODELENGTH);
        aes_decrypt( &ctx, buf, buf );
        memcpy(pTmpDest, buf, KEYCODELENGTH);
        pTmpSrc += KEYCODELENGTH;
        pTmpDest += KEYCODELENGTH;
    }
    unsigned char ucTest = 0;
    ucTest = *(pTmpDest - 1);
    while(ucTest)
    {
        if( ucTest > 0 && ucTest <= 0x10 )
            *(pTmpDest-1) = 0;
        else
            break;
        pTmpDest--;
        ucTest = *(pTmpDest - 1);
    }
    std::string strRet = (char*)pDest;
    delete [] pDest;
    const char *result = strRet.c_str();
    if(is_str_utf8(result)){
        return strRet;
    }
    
    return "";
}
