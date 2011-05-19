#pragma once
//HTTP版hash协议

//////////////////////////////////////////////////////////////////////////
//CS部分

//登录协议
//返回字符0表示成功，其它表示错误码
const char *HCC_LOGIN = "http://%s:%d/login?id=%dd&servtype1=%d&servaddr1=%s&servtype2=%d&servadd2r=%s&servtype3=%d&servaddr3=%s";

//保活，说明自己仍在线。无返回。
const char *HCC_KEEPLIVE = "http://%s:%d/keeplive?id=%d";

//退出登录。无返回。
const char *HCC_LOGOUT = "http://%s:%d/logout?id=%d";

//设置本地服务地址。返回字符0表示成功，其它表示错误码
//const char *HCC_SETSERVER = "http://%s:%d/setServ?id=%";

//改为用post
//上传文件
const char *HCC_ADDFILE	= "http://%s:%d/addFile?id=%dfid=%s";

//删除文件
const char *HCC_DELFILE	= "http://%s:%d/delFile?id=%dfid=%s";

//改为用post
//查询文件拥有者。返回{用户、服务类型、服务地址}列表。返回空表示找不到。
const char *HCC_GETFILEUSER	= "http://%s:%d/getUser?fid=%s&pos=%d&size=%d";

//////////////////////////////////////////////////////////////////////////
//CC部分
//////////////////////////////////////////////////////////////////////////
//下载连接申请
//返回值是RaPack结构体，子类型为RA_SC_LoginRet
const char *HCS_CONNECT = "http://%s:%d/connect?id=%d&fid=%s";

//文件片段下载协议。
//返回值是RaPack结构体，子类型为RA_GetData_Ret
//pos=-1、size=-1时，代表取idv3信息
const char *HCS_DOWNLOAD = "http://%s:%d/getFile?id=%d&fid=%s&pos=%d&size=%d";

////ping协议
////返回一个数字，表示对方时间
//const char *HCS_PING = "http://%s:%d/ping??id=%d&mytime=%d";
//
////取id3信息协议
////返回结构体（二进制）。返回长度小于零表示找不到。
//const char *HCS_GETID3 = "http://%s:%d/ping??id=%d&fid=%s";


