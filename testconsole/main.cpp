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

#include "ziphelper.h"

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

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    //test zip
    unzipStatus result=ziphelper::unzip("/Users/qihoo/cpp/Test/TestConsole/testconsole/minizip/xx.zip", "/Users/qihoo/cpp/Test/TestConsole/testconsole/minizip", "config.ini", true, "123456");
    cout<<"ziphelper::unzip:"<<result<<endl;
    
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
