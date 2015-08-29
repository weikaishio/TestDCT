//
//  base64.h
//  testgame
//
//  Created by Tim on 14-11-4.
//
//

#ifndef __testgame__base64__
#define __testgame__base64__

#include <stdio.h>
#include <string>
using namespace std;

class base64
{
public:
    /*编码
     DataByte
     [in]输入的数据长度,以字节为单位
     */
    string Encode(const unsigned char* Data,int DataByte);
    /*解码
     DataByte
     [in]输入的数据长度,以字节为单位
     OutByte
     [out]输出的数据长度,以字节为单位,请不要通过返回值计算
     输出数据的长度
     */
    string Decode(const char* Data,int DataByte,int& OutByte);
};
#endif /* defined(__testgame__base64__) */
