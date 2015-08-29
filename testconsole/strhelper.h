//
//  strhelper.h
//  TestConsole
//
//  Created by Tim on 15/8/29.
//  Copyright (c) 2015年 Wk. All rights reserved.
//

#ifndef __TestConsole__strhelper__
#define __TestConsole__strhelper__

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;
class strhelper{
public:
    static void substring(char *dest,char *src,int start,int end);
    static int indexOf(char *str1,char *str2);
    static int lastIndexOf(char *str1,char *str2);
};
#endif /* defined(__TestConsole__strhelper__) */
