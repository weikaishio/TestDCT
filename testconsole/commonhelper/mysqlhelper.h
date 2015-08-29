//
//  mysqlhelper.h
//  TestConsole
//
//  Created by Tim on 14-11-14.
//  Copyright (c) 2014年 Wk. All rights reserved.
//

#ifndef __TestConsole__mysqlhelper__
#define __TestConsole__mysqlhelper__

#include <stdio.h>
#include <string>
#include <mysql.h>
using namespace std;

class mysqlhelper {
private:
    int affectedRows;
    MYSQL mysql;
    MYSQL* connection;
public: 
    ~mysqlhelper();
    mysqlhelper();
    void close();
    const char* GetError();
    int IsConnected();
    int connectdb(char* host,char* port,char* username,char* pwd,char* charset,char* db,char* msg);
    string select(char* sql);
    void selectlist(char* sql);
    int commandexec(char* sql);
};
#endif /* defined(__TestConsole__mysqlhelper__) */
