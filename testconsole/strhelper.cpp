//
//  strhelper.cpp
//  TestConsole
//
//  Created by Tim on 15/8/29.
//  Copyright (c) 2015年 Wk. All rights reserved.
//

#include "strhelper.h"

/*截取src字符串中,从下标为start开始到end-1(end前面)的字符串保存在dest中(下标从0开始)*/
void strhelper::substring(char *dest,char *src,int start,int end)
{
    int i=start;
    if(start>strlen(src))return;
    if(end>strlen(src))
        end=strlen(src);
    while(i<end)
    {
        dest[i-start]=src[i];
        i++;
    }
    dest[i-start]='\0';
    return;
}
/*返回str2第一次出现在str1中的位置(下表索引),不存在返回-1*/
int strhelper::indexOf(char *str1,char *str2)
{
    char *p=str1;
    int i=0;
    p=strstr(str1,str2);
    if(p==NULL)
        return -1;
    else{
        while(str1!=p)
        {
            str1++;
            i++;
        }
    }
    return i;
}
/*返回str1中最后一次出现str2的位置(下标),不存在返回-1*/
int strhelper::lastIndexOf(char *str1,char *str2)
{
    char *p=str1;
    int i=0,len=strlen(str2);
    p=strstr(str1,str2);
    if(p==NULL)return -1;
    while(p!=NULL)
    {
        for(;str1!=p;str1++)i++;
        p=p+len;
        p=strstr(p,str2);
    }
    return i;
}