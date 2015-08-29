//
//  mysqlhelper.cpp
//  TestConsole
//
//  Created by Tim on 14-11-14.
//  Copyright (c) 2014年 Wk. All rights reserved.
//

#include "mysqlhelper.h"
#include <mysql.h>
#include <stdio.h>
#include <iostream>

int mysqlhelper::connectdb(char* host,char* port,char* username,char* pwd,char* charset,char* db,char* msg)
{
//    MYSQL *connection, mysql;
//    mysql_init(&mysql);
//    connection = mysql_real_connect(&mysql,"127.0.0.1","root","psw","database",0,0,0);
//    if (connection == NULL)
//    {
//        //unable to connect
//        printf("Oh Noes!\n");
//    }
//    else
//    {
//        printf("Connected.\n");
//    }
//    return 0;
    int state=0;
    
    if(IsConnected()){
        return state;
    }
 
    mysql_init(&mysql);
    connection=mysql_real_connect(&mysql,host,username,pwd,
                                  db,0,NULL,0);
 
    if(!IsConnected()){
        const char* error= GetError();
        cout<<error<<endl;
        state=-1;
    }
    if(state<0){
        const char* error=GetError();
        cout<<error<<endl;
        state=-1;
    }
    return state;
}
mysqlhelper::~mysqlhelper()
{
    if(IsConnected())
        close();
}
mysqlhelper::mysqlhelper()
{
}
void mysqlhelper::close()
{
    if(!IsConnected())
        return;
    mysql_close(connection);
    connection=(MYSQL*)NULL;
}
const char* mysqlhelper::GetError()
{
    if(IsConnected())
        return mysql_error(connection);
    else
        return mysql_error(&mysql);
}

int mysqlhelper::IsConnected()
{
    return (connection!=NULL);
}
string mysqlhelper::select(char* sql)
{
    MYSQL_RES* result;
    int state;
    
    if(!IsConnected())
        throw "DataBase not connected.";
    
    state=mysql_query(connection,sql);
    
    if(state!=0)
        throw GetError();
    
    result=mysql_store_result(connection);
    
    //if the result was null,it was an update or an error occurred
    if(result==NULL)
    {
        int fieldCount=mysql_field_count(connection);
        if(fieldCount!=0)
            throw GetError();
        else{
            unsigned long long affectedRows=mysql_affected_rows(connection);
            cout<<"affectedRows:"<<affectedRows<<endl;
        }
        return NULL;
    }
    else{
        
    }
//    //return a Result instance for queries
//    return new Result(result);
    return NULL;
}
int mysqlhelper::commandexec(char* sql)
{
    return 0;
}
void mysqlhelper::selectlist(char* sql)
{
    if (connection==NULL) {
        return;
    }
    try {
    MYSQL_RES *result = NULL;
    MYSQL_FIELD *field = NULL; 
    mysql_query(connection, sql);
    result = mysql_store_result(connection);
        if (result==NULL) {
            return;
        }
//    unsigned long long rowcount = mysql_num_rows(result); ;
    int fieldcount = mysql_num_fields(result);
    MYSQL_ROW row = NULL;
    row = mysql_fetch_row(result);
    while(NULL != row)
    {
        for(int i=1; i<fieldcount; i++)
        {
            field = mysql_fetch_field_direct(result,i);
            cout << field->name<<":"<<row[i] << "\t\t";
        }
        cout << endl;
        row = mysql_fetch_row(result);
    }
    mysql_close(&mysql);
    } catch (const char* exceptionString) {
        cout<<exceptionString<<endl;
    }
}

//bool mysqlhelper::execproc()
//{
//    int ret = 1;
//    PreparedStatement* prep_stmt = NULL;
//    ResultSet* res = NULL;
//    
//    try
//    {
//        con->setSchema(G<ConnectionPool>().GetDBName().c_str());
//        
//        //执行sql改变安装状态
//        std::string sql_statement = "update tb_host set reg_date=?, sn=?, ip=?, mac=?, state=?, sync_state=? where reg_code =? and state=?";//要执行的sql语句
//        //事务处理
//        con->setAutoCommit(0);
//        prep_stmt = con->prepareStatement(sql_statement.c_str());
//        
//        prep_stmt->setString(1, install_time.c_str());
//        prep_stmt->setString(2, harddrive_sn.c_str());
//        prep_stmt->setString(3, ip_address.c_str());
//        prep_stmt->setString(4, mac_address.c_str());
//        prep_stmt->setInt(5, HAS_INSTALL);
//        prep_stmt->setInt(6, HAS_SYNC);
//        prep_stmt->setString(7, install_code.c_str());
//        prep_stmt->setInt(8, NO_INSTALL);
//        
//        if(prep_stmt->executeUpdate() == 0)
//        {
//            ret = 2;
//            LOG4CXX_INFO(g_logger, ".....");
//            out.push_back(JSONNode(ERROR_MESSAGE, "....."));
//            goto Finally_handle;
//        }
//        //调用赋默认策略存储过程
//        std::string procedure = "CALL updateHostPolicyByModHost(?,?, @ret, @msg)";
//        prep_stmt = con->prepareStatement(procedure.c_str());
//        prep_stmt->setString(1, install_code.c_str());
//        prep_stmt->setInt(2, 0);
//        prep_stmt->execute();
//        
//        std::string query = "select @ret AS ret,@msg AS msg";
//        prep_stmt = con->prepareStatement(query.c_str());
//        res = prep_stmt->executeQuery();
//        while(res->next())
//        {
//            if(res->getInt("ret") != 0)
//            {
//                LOG4CXX_ERROR(g_logger, "....." << res->getString("msg").c_str() << res->getInt("ret"));
//                out.push_back(JSONNode(ERROR_MESSAGE, "....."));
//                goto Finally_handle;
//            }
//        }
//        con ->commit();
//        
//    }
//    catch (SQLException& e)
//    {
//        try
//        {
//            con->rollback();
//        }
//        catch (const char* exceptionString) {
//            cout<<exceptionString<<endl;
//            ret = 0;
//            LOG4CXX_ERROR(g_logger, "数据库异常" << e.what());
//            goto Finally_handle;
//        }
//        
//        ret = 0;
//        LOG4CXX_ERROR(g_logger, "数据库异常" << e.what());
//        out.push_back(JSONNode(ERROR_MESSAGE, e.what()));
//        goto Finally_handle;
//    }
//            catch (const char* exceptionString) {
//                cout<<exceptionString<<endl;
//        ret = 0;
//        LOG4CXX_ERROR(g_logger, "其他错误");
//        out.push_back(JSONNode(ERROR_MESSAGE, "其他错误"));
//        goto Finally_handle;
//    }
//    
//Finally_handle:
//    DestorySql(res, prep_stmt);
//    //将连接释放到连接池
//    G<ConnectionPool>().ReleaseConnection(con);
//    
//    if (ret == 1)
//    {
//        out.push_back(JSONNode(RESULT, ACTION_SUCCESS));
//        return true;
//    }
//    else if (ret == 2)
//    {
//        out.push_back(JSONNode(RESULT, ACTION_FALSE));
//        return true;
//    }
//    else
//    {
//        out.push_back(JSONNode(RESULT, ACTION_FALSE));
//        return false;
//    }
//    
//}
//
///************************************************************************/
///* 销毁数据库记录集资源                                                 */
///************************************************************************/
//void mysqlhelper::DestorySql(ResultSet* res, PreparedStatement* prep_stmt)
//{
//    if (res != NULL)
//    {
//        try
//        {
//            res ->close();
//        }
//        catch(const char* exceptionString) {
//            cout<<exceptionString<<endl;
////            LOG4CXX_ERROR(g_logger, "数据库异常" << e.what());
//        }
//        delete res;
//        res = NULL;
//    }
//    if (prep_stmt != NULL) {
//        try
//        {
//            prep_stmt->close();
//        }
//        catch(const char* exceptionString) {
//            cout<<exceptionString<<endl;
////            LOG4CXX_ERROR(g_logger, "数据库异常" << e.what());
//        }
//        delete prep_stmt;
//        prep_stmt = NULL;
//    }
//}