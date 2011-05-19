/******************************************************************************************************
��Ŀ���ƣ�PP��ý��
�ļ����ƣ�K8TVProtoValue.h 
��    �ܣ�Э�鶨��
��    �ߣ�gaocheng
�������ڣ�2008��03��28
�޸ļ�¼��

******************************************************************************************************/
#ifndef K8TV_PROTOCOL_Value_H
#define K8TV_PROTOCOL_Value_H
 
 
const  DWORD c_dwMaxBufLen = 1024 * 64; 

const  DWORD c_dwMaxSubStream = 0xff;

//�ͻ�����ͻ���֮�������
enum Protocol_C2C
{
	RA_C2C_MIN        =  0x00010000,    //
	RA_C2C_GetID3Info,			        // ȡ��ID3Info
	RA_C2C_GetID3Info_Ret,			    // ����ID3Info
	RA_C2C_GetData,			            // ȡ���ļ�����
	RA_C2C_GetData_Ret,			        // �����ļ�����
	RA_C2C_PING,					    //����
	RA_C2C_PING_RET,			        //

	RA_C2C_MAX,  //tianzuo,2009-6-27
};


enum Protocol_C2S
{	
	RA_CS_MIN        =  0x00020000,        //
	RA_CS_LOGIN,                           //�û���¼
	RA_CS_LOGIN_RET,                       //�û���¼��Ӧ
	RA_CS_LOGOUT,                          //�û��ǳ�
	RA_CS_ACTIVE,                          //�û����ֻ
	RA_CS_FILEUSER,                        //��ȡ�ļ��û�
	RA_CS_FILEUSER_RET,                    //�����ļ��û�
	RA_CS_ADD,                             //����ļ�
	RA_CS_MAX
}; 


//��������ͻ��˽����Ĵ�����
enum Protocol_CS2C_RetResult
{
	TV_C2S_RET_RESULT_SUCCESS =     0x00000000,//��½�ɹ� 
	TV_C2S_RET_RESULT_ERRPWD,                  //�������
	TV_C2S_RET_RESULT_UNKWONERROR,             //δ֪���� ��һ��Ϊ���������

	TV_C2S_RET_RESULT_SHOOTTO_SUCCESS,         //���������ش�����,����ɹ�
	TV_C2S_RET_RESULT_SHOOTTO_NOUSER,          //���������ش�����
	TV_C2S_RET_RESULT_SHOOTTO_NOINCHANNEL,     //���ڹۿ���Ƶ����
	TV_C2S_RET_RESULT_SHOOTTO_FAILE,            //����δ֪����

	TV_C2S_RET_RESULT_CHCHANNEL_FAILE,      //һ�������Ҫ�Ƿ������������쳣

	TV_C2S_RET_RESULT_USERLIST_SUCCESS,     //ȡ���û�Դ�б�ɹ�
	TV_C2S_RET_RESULT_USERLIST_NOCHANEL,    //��Ҫȡ���û�Դ��Ƶ��������
	TV_C2S_RET_RESULT_USERLIST_NOUSER,      //û���û�Դ 

	TV_C2S_RET_RESULT_NODIR,               //Ҫ������Ŀ¼������    
	TV_CC_BUFER_EMPTY,					 //������Ϊ��
	TV_C2S_RET_RESULT_MAXNUM
};
#endif

