#pragma once
//HTTP��hashЭ��

//////////////////////////////////////////////////////////////////////////
//CS����

//��¼Э��
//�����ַ�0��ʾ�ɹ���������ʾ������
const char *HCC_LOGIN = "http://%s:%d/login?id=%dd&servtype1=%d&servaddr1=%s&servtype2=%d&servadd2r=%s&servtype3=%d&servaddr3=%s";

//���˵���Լ������ߡ��޷��ء�
const char *HCC_KEEPLIVE = "http://%s:%d/keeplive?id=%d";

//�˳���¼���޷��ء�
const char *HCC_LOGOUT = "http://%s:%d/logout?id=%d";

//���ñ��ط����ַ�������ַ�0��ʾ�ɹ���������ʾ������
//const char *HCC_SETSERVER = "http://%s:%d/setServ?id=%";

//��Ϊ��post
//�ϴ��ļ�
const char *HCC_ADDFILE	= "http://%s:%d/addFile?id=%dfid=%s";

//ɾ���ļ�
const char *HCC_DELFILE	= "http://%s:%d/delFile?id=%dfid=%s";

//��Ϊ��post
//��ѯ�ļ�ӵ���ߡ�����{�û����������͡������ַ}�б����ؿձ�ʾ�Ҳ�����
const char *HCC_GETFILEUSER	= "http://%s:%d/getUser?fid=%s&pos=%d&size=%d";

//////////////////////////////////////////////////////////////////////////
//CC����
//////////////////////////////////////////////////////////////////////////
//������������
//����ֵ��RaPack�ṹ�壬������ΪRA_SC_LoginRet
const char *HCS_CONNECT = "http://%s:%d/connect?id=%d&fid=%s";

//�ļ�Ƭ������Э�顣
//����ֵ��RaPack�ṹ�壬������ΪRA_GetData_Ret
//pos=-1��size=-1ʱ������ȡidv3��Ϣ
const char *HCS_DOWNLOAD = "http://%s:%d/getFile?id=%d&fid=%s&pos=%d&size=%d";

////pingЭ��
////����һ�����֣���ʾ�Է�ʱ��
//const char *HCS_PING = "http://%s:%d/ping??id=%d&mytime=%d";
//
////ȡid3��ϢЭ��
////���ؽṹ�壨�����ƣ������س���С�����ʾ�Ҳ�����
//const char *HCS_GETID3 = "http://%s:%d/ping??id=%d&fid=%s";


