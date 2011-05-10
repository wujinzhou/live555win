/******************************************************************************************************
项目名称：PP流媒体
文件名称：K8TVProtoValue.h 
功    能：协议定义
作    者：gaocheng
创建日期：2008－03－28
修改记录：

******************************************************************************************************/
#ifndef K8TV_PROTOCOL_Value_H
#define K8TV_PROTOCOL_Value_H
 
 
const  DWORD c_dwMaxBufLen = 1024 * 64; 

const  DWORD c_dwMaxSubStream = 0xff;

//客户端与客户端之间的信令
enum Protocol_C2C
{
	RA_C2C_MIN        =  0x00010000,    //
	RA_C2C_GetID3Info,			        // 取得ID3Info
	RA_C2C_GetID3Info_Ret,			    // 返回ID3Info
	RA_C2C_GetData,			            // 取得文件数据
	RA_C2C_GetData_Ret,			        // 返回文件数据
	RA_C2C_PING,					    //测速
	RA_C2C_PING_RET,			        //

	RA_C2C_MAX,  //tianzuo,2009-6-27
};


enum Protocol_C2S
{	
	RA_CS_MIN        =  0x00020000,        //
	RA_CS_LOGIN,                           //用户登录
	RA_CS_LOGIN_RET,                       //用户登录回应
	RA_CS_LOGOUT,                          //用户登出
	RA_CS_ACTIVE,                          //用户保持活动
	RA_CS_FILEUSER,                        //获取文件用户
	RA_CS_FILEUSER_RET,                    //返回文件用户
	RA_CS_ADD,                             //添加文件
	RA_CS_MAX
}; 


//服务器与客户端交互的错误定义
enum Protocol_CS2C_RetResult
{
	TV_C2S_RET_RESULT_SUCCESS =     0x00000000,//登陆成功 
	TV_C2S_RET_RESULT_ERRPWD,                  //密码错误
	TV_C2S_RET_RESULT_UNKWONERROR,             //未知错误 （一般为信令包错误）

	TV_C2S_RET_RESULT_SHOOTTO_SUCCESS,         //服务器返回打洞请求,请求成功
	TV_C2S_RET_RESULT_SHOOTTO_NOUSER,          //服务器返回打洞请求，
	TV_C2S_RET_RESULT_SHOOTTO_NOINCHANNEL,     //不在观看的频道内
	TV_C2S_RET_RESULT_SHOOTTO_FAILE,            //发生未知错误

	TV_C2S_RET_RESULT_CHCHANNEL_FAILE,      //一般错误，主要是服务器程序发生异常

	TV_C2S_RET_RESULT_USERLIST_SUCCESS,     //取得用户源列表成功
	TV_C2S_RET_RESULT_USERLIST_NOCHANEL,    //所要取得用户源的频道不存在
	TV_C2S_RET_RESULT_USERLIST_NOUSER,      //没有用户源 

	TV_C2S_RET_RESULT_NODIR,               //要发布的目录不存在    
	TV_CC_BUFER_EMPTY,					 //缓冲区为空
	TV_C2S_RET_RESULT_MAXNUM
};
#endif

