//
//  TopicModel.h
//  TestConsole
//
//  Created by Tim on 14-11-21.
//  Copyright (c) 2014年 Wk. All rights reserved.
//

#ifndef TestConsole_TopicModel_h
#define TestConsole_TopicModel_h
#include <stdio.h>
#include <string>
using namespace std;
struct TopicModel
{
    string Contents;
    string CreateTime;
    int FType;
    int Hearts;
    int Replys;
    string ID;
    string ImageAddress;
    string lat;
    string lon;
    string POI;
    int UID;
    int StyleID;
};
#endif
