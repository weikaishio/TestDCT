//
//  testredis.cpp
//  TestConsole
//
//  Created by Tim on 14-11-14.
//  Copyright (c) 2014年 Wk. All rights reserved.
//

#include "redishelper.h"
#include <string>
#include "document.h"
#include "rapidjson.h"
#include <sstream>
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace rapidjson;

redishelper::redishelper()
{
    struct timeval timeout = {2, 0}; //2s的超时时间
    //redisContext是Redis操作对象
    pRedisContext = (redisContext*)redisConnectWithTimeout("182.92.64.170", 6379, timeout);
    
    if ( (NULL == pRedisContext) || (pRedisContext->err) )
    {
        if (pRedisContext)
        {
            std::cout << "connect error:" << pRedisContext->errstr << std::endl;
        }
        else
        {
            std::cout << "connect error: can't allocate redis context." << std::endl;
        }
        throw -1;
    }
}
redishelper::~redishelper()
{
    free(pRedisContext);
}
static redishelper* _sharedInstance;
redishelper* redishelper::getInstance()
{
    if (!_sharedInstance) {
        _sharedInstance=new redishelper();
    }
    return _sharedInstance;
}
void redishelper::getlist()
{
    redisReply *pRedisReply = (redisReply*)redisCommand(pRedisContext, "zrange content:hot 0 200000000"); //执行INFO命令
    std::cout << pRedisReply->type << std::endl;
    std::cout << pRedisReply->elements << std::endl;
    auto lst=pRedisReply->element;
    for (int i=0; i<pRedisReply->elements; i++) {
        redisReply* item=lst[i];
        std::cout << item->type << std::endl;
//        std::cout << item->str << std::endl;
        struct TopicModel tm=unserialtopic(item->str);
        std::cout<<tm.Contents<<std::endl;
    }
    //当多条Redis命令使用同一个redisReply对象时
    //每一次执行完Redis命令后需要清空redisReply 以免对下一次的Redis操作造成影响
    freeReplyObject(pRedisReply);
}
/*{"ApprovedStatus":0,"CID":"1002373868_cfmh2eBWVAA1","Contents":"     有这么个地方，允许我言语自由，不受人品头论足，24岁的年纪我老吗？不，我真不觉得，虽然我时常羡慕同学结婚生子那种人生轨道的日子，  甚至想过有个人能和我结婚，一生就这样开始了，那是多美妙！想想如今现状却已是梦。","CreateTime":"2014-11-03 09:56:41","FType":0,"Hearts":494,"ID":607328,"ImageAddress":"http:\/\/img.qiaoqiao.co\/t01c33d6fa5778f6676.jpg","IsAllowComment":true,"IsPublic":false,"IsSubscribe":false,"Lat":0,"Lon":0,"POI":"","PrimaryKeyName":"ID","Replys":51,"ShareUrl":"http:\/\/m.qiaoqiao.co\/\/w\/s\/1470701344","Stamp":23739421767629169,"StyleID":9,"UID":1002373868}*/
struct TopicModel redishelper::unserialtopic(char* data)
{
    struct TopicModel tm;
    do{
        rapidjson::Document _doc;
        _doc.Parse<0>(data);
        if(_doc.HasParseError()) {
            std::cout<<"break:_doc.HasParseError()"<<std::endl;
            break;
        }
        if(!_doc.IsObject()) {
            std::cout<<"break:_doc.IsObject()"<<std::endl;
            break;
        }
        const rapidjson::Value &contents=_doc["Contents"];
                tm.Contents=contents.GetString();
                tm.CreateTime=_doc["CreateTime"].GetString();
                tm.FType=_doc["FType"].GetInt();
                tm.Hearts=_doc["Hearts"].GetInt();
                tm.ID=_doc["CID"].GetString();
                tm.ImageAddress=_doc["ImageAddress"].GetString();
        ostringstream oss;
        oss<<_doc["Lat"].GetDouble();
                tm.lat=string(oss.str());
                tm.lon=_doc["Lon"].GetDouble();
                tm.StyleID=_doc["StyleID"].GetInt();
                tm.POI=_doc["POI"].GetString();
                tm.Replys=_doc["Replys"].GetInt();
        
    }while (0);
    return tm;
}