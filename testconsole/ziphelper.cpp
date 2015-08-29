//
//  ziphelper.cpp
//  TestConsole
//
//  Created by Tim on 15/8/29.
//  Copyright (c) 2015年 Wk. All rights reserved.
//

#include "ziphelper.h"
#include "minizip/unzip.h"
#include "minizip/zip.h"
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include "strhelper.h" 
#include "miniini.h"
#include <iostream>

bool ziphelper::isFileExist(string path){
    FILE* file;
    file=fopen(path.c_str(), "r");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}
unzipStatus ziphelper::unzip(string zipPath,string destPath,bool isOverWrite,string pwd,vector<std::string> &files){
    unzipStatus success=unzipStatusSuccess;
    zipFile zip = unzOpen(zipPath.c_str());
    if (zip==NULL) {
        printf("zip == NULL");
        success=unzipStatusFail;
        return success;
    }
    
    if (unzGoToFirstFile(zip)!=UNZ_OK) {
        printf("unzGoToFirstFile != 0");
        success=unzipStatusFail;
        return success;
    }
    
    int ret=0;
    unsigned char buffer[4096]={0};
    do{
        if (pwd.size() == 0) {
            ret = unzOpenCurrentFile(zip);
        } else {
            ret = unzOpenCurrentFilePassword(zip, pwd.c_str());
        }
        
        if (ret!=UNZ_OK) {
            success=unzipStatusFail;
            break;
        }
        
        unz_file_info fileInfo;
        memset(&fileInfo,0,sizeof(unz_file_info));
        
        ret=unzGetCurrentFileInfo(zip, &fileInfo, NULL, 0, NULL, 0, NULL, 0);
        if (ret!=UNZ_OK) {
            unzCloseCurrentFile(zip);
            success=unzipStatusFail;
            break;
        }
        
        char* filename=(char*)malloc(fileInfo.size_filename+1);
        int ret2=unzGetCurrentFileInfo(zip, &fileInfo, filename,fileInfo.size_filename+1, NULL, 0, NULL, 0);
        filename[fileInfo.size_filename]='\0';
        printf("ret2:%d\n",ret2);
        
        const uLong ZipUNIXVersion = 3;
        const uLong BSD_SFMT = 0170000;
        const uLong BSD_IFLNK = 0120000;
        
        int fileIsSymbolicLink = 0;
        if (((fileInfo.version >> 8) == ZipUNIXVersion) && BSD_IFLNK == (BSD_SFMT & (fileInfo.external_fa >> 16))) {
            fileIsSymbolicLink = 1;
        }
        //        printf("fileIsSymbolicLink:%d\n",fileIsSymbolicLink);
        
        int isDirectory=0;
        if (filename[fileInfo.size_filename-1]=='/'||filename[fileInfo.size_filename-1]=='\\') {
            isDirectory=1;
        }
        
//        char path[256]={0};
        string path;
        if (isDirectory==1) {
//            sprintf(path,"%s/%s", destPath,filename);
            path=destPath+"/"+filename;
            if (!isFileExist(path)) {
                int status=mkdir(path.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
                printf("isFileExist,path:%s,status:%d\n",path.c_str(),status);if (status!=0) {
                    success=unzipStatusCreateFolderFail;
                    break;
                }
            }
            
            unzCloseCurrentFile(zip);
            ret=unzGoToNextFile(zip);
            continue;
        }
        else{
            int index=string(filename).find_first_of('/');
            if (index>0) {
                path=destPath+"/"+string(filename).substr(0,index);
                if (!isFileExist(path)) {
                    int status=mkdir(path.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
                    
                    printf("isFileExist path:%s,status:%d\n",path.c_str(),status);if (status!=0) {
                        success=unzipStatusCreateFolderFail;
                        break;
                    }
                }
            }
        }
//        char fullPath[256]={0};
        string fullPath=destPath+"/"+filename;
//        sprintf(fullPath,"%s/%s", destPath,filename);
        
//        char* pureFileName=(char*)malloc(strlen(fullPath)-lastIndexOf(fullPath, "/")-1);
//        substring(pureFileName, fullPath, lastIndexOf(fullPath, "/")+1, strlen(fullPath));
//        int index=fullPath.find_last_of('/');
//        string pureFileName=fullPath.substr(index+1,fullPath.size()-index-1);
//        if (strcmp(pureFileName,"config.ini")==0) {
//        if(pureFileName==string("config.ini")){
//            strcpy(configPath, fullPath);
//            configPath=fullPath;
//            configPath[strlen(fullPath)]='\0';
//        }
//        free(pureFileName);
        free(filename);
        //        printf("filename:%s,%s\n",filename,fullPath);
        
        files.push_back(fullPath);
        if (isFileExist(fullPath)&&isOverWrite==0) {
//            printf("isFileExist:%s\n",fullPath);
            cout<<"isFileExist:"<<fullPath<<endl;
            unzCloseCurrentFile(zip);
            ret=unzGoToNextFile(zip);
            success=unzipStatusFileExists;
            continue;
        }
        FILE *fp = fopen(fullPath.c_str(), "wb");
        while (fp) {
            int readBytes = unzReadCurrentFile(zip, buffer, 4096);
            
            if (readBytes > 0) {
                fwrite(buffer, readBytes, 1, fp );
            } else {
                printf("readBytes:%d\n",readBytes);
                if (readBytes<0) {
                    success=unzipStatusCreateFileFail;
                }
                break;
            }
        }
        if (fp) {
            fclose(fp);
        }else{
            success=unzipStatusCreateFileFail;
        }
        
        unzCloseCurrentFile(zip);
        ret=unzGoToNextFile(zip);
    }while (ret==UNZ_OK&&ret!=UNZ_END_OF_LIST_OF_FILE);
    unzClose(zip);
//    vector<string>::iterator viter;
//    for(viter = files.begin(); viter != files.end(); viter++)
//    {
//        cout<<"files:"<<*viter<<endl;
//    }
    return success;
}