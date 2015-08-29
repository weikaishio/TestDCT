//
//  redishelper.h
//  TestConsole
//
//  Created by Tim on 14-11-21.
//  Copyright (c) 2014年 Wk. All rights reserved.
//

#ifndef TestConsole_redishelper_h
#define TestConsole_redishelper_h

#include <stdio.h>
#include "hiredis.h"
#include "TopicModel.h"
//static redishelper* _sharedInstance;
class redishelper {
private:
    redisContext* pRedisContext;
public:
    redishelper();
    ~redishelper();
    static redishelper* getInstance();
    void getlist();
    struct TopicModel unserialtopic(char* data);
};

#endif
