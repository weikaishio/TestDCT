//
//  main.cpp
//  TestConsole
//
//  Created by Tim on 14-11-13.
//  Copyright (c) 2014年 Wk. All rights reserved.
//

#include <iostream>
//#include "redishelper.h"
//#include "CHttpClient.h"
//#include "mysqlhelper.h"
#include <vector>

#include "ziphelper.h"
#include "miniini.h"

struct ConfigModel{
    int fileType;
    string fileName;
};

//void UnzipAndZip( const char* pScrFileName, const char* pDstFileName )
//{
//    struct FILE_DESC
//    {
//        unsigned char* pData;
//        size_t DataSize;
//    };
//    std::map<std::string, FILE_DESC> mapFileStreams;
//    ZZIP_DIR* pZipDir = zzip_opendir( pScrFileName );
//    ZZIP_DIRENT* pZipDirent = NULL;
//    while( pZipDirent = zzip_readdir( pZipDir ) )
//    {
//        size_t length = strlen(pZipDirent->d_name);
//        if( length > 0 )
//        {
//            if( pZipDirent->d_name[length - 1] != '//'
//               && pZipDirent->d_name[length - 1] != '/' )
//            {
//                ZZIP_FILE* pZipFile = zzip_file_open( pZipDir, pZipDirent->d_name, ZZIP_CASELESS );
//                if( pZipFile != NULL )
//                {
//                    ZZIP_STAT sz;
//                    memset( &sz, 0, sizeof(sz) );
//                    zzip_file_stat( pZipFile, &sz );
//                    if( sz.st_size > 0 )
//                    {
//                        unsigned char* pBuffer = new unsigned char[sz.st_size];
//                        zzip_file_read( pZipFile, pBuffer, sz.st_size );
//                        FILE_DESC data = { pBuffer, sz.st_size };
//                        mapFileStreams[pZipDirent->d_name] = data;
//                    }
//                    zzip_file_close( pZipFile );
//                }
//            }
//        }
//    }
//    if( pZipDir )
//        zzip_closedir( pZipDir );
//    zip_fileinfo ZipFileInfo;
//    zipFile ZipFile = zipOpen( pDstFileName, 0 );
//    std::map<std::string, FILE_DESC>::iterator iter = mapFileStreams.begin();
//    while( iter != mapFileStreams.end() )
//    {
//        int err = zipOpenNewFileInZip( ZipFile, iter->first.c_str(), &ZipFileInfo, NULL,    0, NULL, 0, NULL, 0, 0 );
//        zipWriteInFileInZip( ZipFile, iter->second.pData, iter->second.DataSize );
//        SAFE_DELETEARRAY( iter->second.pData );
//        ++iter;
//    }
//    zipClose( ZipFile, NULL );
//}
bool readIni(string filePath,ConfigModel &model){
    INIFile ini;
    if(!ini.OpenFile(filePath)){
        std::cout << "ERROR: Could not open ini" << std::endl;
        return false;
    }
    
    std::string sname = "xxx";
    INISection * general = ini.GetSection(sname);
    if(!general){
        std::cout << "ERROR: Missing section [general] in ini"
        << std::endl;
        return false;
    }
    
    std::string filename;
    int filetype;
    std::string filename_tag = "filename";
    std::string filetype_tag = "filetype";
    if(general->ReadString(filename_tag, filename)){
        std::cout << "section [" << filename
        << "] in ini" << std::endl;
        model.fileName=filename;
    }
    if(general->ReadInt(filetype_tag, filetype)){
        std::cout << "section [" << filetype
        <<"] in ini" << std::endl;
    model.fileType=filetype;
    }
    return true;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    vector<std::string> files;
    //test zip
    unzipStatus result=ziphelper::unzip("/Users/qihoo/cpp/Test/TestConsole/TestCPP/testconsole/xx.zip", "/Users/qihoo/cpp/Test/TestConsole/TestCPP/testconsole", true, "123456",files);
    std::cout<<"ziphelper::unzip:"<<result<<std::endl;
    
    string configFile="config.ini";
    vector<string>::iterator viter;
    for(viter = files.begin(); viter != files.end(); viter++)
    {
        cout<<"files1:"<<*viter<<endl;
        string fullPath=*viter;
        int index=fullPath.find_last_of('/');
        string pureFileName=fullPath.substr(index+1,fullPath.size()-index-1);
        if(pureFileName==configFile){
            cout<<"config:"<<fullPath<<endl;
            ConfigModel model;
            if (readIni(fullPath, model)) {
                cout<<"ConfigModel:"<<model.fileType<<","<<model.fileName<<endl;
            }
        }
        
    }
    
    //test redis
//    redishelper::getInstance()->getlist();
    
    //test libcurl
//    const std::string strurl="http://secret.qiaoqiao.co/message/add";
//    std::string response;
//    CHttpClient* cc=new CHttpClient();
//    cc->Get(strurl, response);
//    std::cout<<response<<std::endl;
//    string url="https://q.qiaoqiao.co/a/dlln";
//    string post=""; 
//    cc->Posts(url, post, response);
//    std::cout<<response<<std::endl;
    
    //test mysql
//    mysqlhelper* mysql=new mysqlhelper();
//    int state=mysql->connectdb("127.0.0.1", "3306", "root", "", "utf8", "test", NULL);
//    if (state==0) {
//        mysql->selectlist("select * from topic");
//    }
    return 0;
}
