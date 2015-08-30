//
//  DigitalMarking.h
//  GameTest
//
//  Created by Tim on 15/8/29.
//  Copyright (c) 2015年 Wk. All rights reserved.
//

#ifndef __GameTest__DigitalMarking__
#define __GameTest__DigitalMarking__

#include <stdio.h>
#include <string>

using namespace std;

class DigitalMarking
{
private:
    string password;
    string waterMark;
    string strPathName;
    
public:
    void OnUpdateEmbeded(void *pCmdUI);
    void OnUpdateExtract(void *pCmdUI);
private:
    bool commonBehaviorOfHandleImage();
    void generateEmbededWaterMarkImage();
public:
    void OnPasswordGenrate();
    void OnWaterMarkGenerate();
    void setPassword(string&);
    void setWaterMarking(string&);
    void OnBnClickedButton4();
};


#endif /* defined(__GameTest__DigitalMarking__) */
