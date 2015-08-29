//
//  ziphelper.h
//  TestConsole
//
//  Created by Tim on 15/8/29.
//  Copyright (c) 2015年 Wk. All rights reserved.
//

#ifndef __TestConsole__ziphelper__
#define __TestConsole__ziphelper__

#include <stdio.h>
#include <iostream>

enum unzipStatus{
    unzipStatusFail=0,
    unzipStatusSuccess=1,
    unzipStatusCreateFolderFail=-1,
    unzipStatusCreateFileFail=-2,
    unzipStatusFileExists=2
};

using namespace std;
class ziphelper{
public:
    static bool isFileExist(string path);
    static unzipStatus unzip(string zipPath,string destPath,string configPath,bool isOverWrite,string pwd);
};

#endif /* defined(__TestConsole__ziphelper__) */
