#pragma once
#include <winsock.h>
#include <string>

#pragma warning(disable:4200) //΢��Ǳ�׼��չ
#pragma pack(1)
// ��������
// Ԥ�������ݳ���
typedef unsigned __int8  t_uchar;	// ����Ϊһ�ֽڵ��޷�������
typedef unsigned __int16 t_ushort;	// ����Ϊ���ֽڵ��޷�������
typedef unsigned __int32 t_uint;	// ����Ϊ���ֽڵ��޷�������
typedef unsigned __int64 t_uword;	// ����Ϊ���ֽڵ��޷�������

// IPv4�ĵ�ַ��
struct KIpv4Addr
{
	t_uint uiIp;		// IP��ַ
	t_ushort usPort;	// �˿ں�

public:
	//=================================================
	//���캯��
	KIpv4Addr();
	KIpv4Addr(t_uint uiIp,t_ushort usPort);
	KIpv4Addr(char *strIp,t_ushort usPort);
	KIpv4Addr(SOCKADDR_IN addr);
	KIpv4Addr(const KIpv4Addr &addr);

	//����õ�ַ�ĸ��ֱ�ʾ��ʽ
	void GetAddr(SOCKADDR_IN &addr) const;
	void GetAddr(t_uint &uiIp,t_ushort &usPort) const;
	void GetAddr(std::string &strIp,t_ushort &usPort) const;
	std::string ToString() const;

	//������
	bool operator == (const KIpv4Addr &addr) const;
	bool operator != (const KIpv4Addr &addr) const;
	const KIpv4Addr & operator = (const KIpv4Addr &addr);
};

KIpv4Addr::KIpv4Addr(t_uint uiIp,t_ushort usPort)
{
	this->uiIp = uiIp;
	this->usPort = usPort;
}
KIpv4Addr::KIpv4Addr(char *strIp,t_ushort usPort)
{
	this->uiIp = ntohl(inet_addr(strIp));
	this->usPort = usPort;
}
KIpv4Addr::KIpv4Addr(SOCKADDR_IN addr)
{
	this->uiIp = ntohl(addr.sin_addr.S_un.S_addr);
	this->usPort = ntohs(addr.sin_port);
}
KIpv4Addr::KIpv4Addr(const KIpv4Addr &addr)
{
	this->uiIp = addr.uiIp;
	this->usPort = addr.usPort;
}

KIpv4Addr::KIpv4Addr()
{
	uiIp = 0;
	usPort = 0;
}
void KIpv4Addr::GetAddr(SOCKADDR_IN &addr) const
{
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(uiIp);
	addr.sin_port = htons(usPort);
}
void KIpv4Addr::GetAddr(t_uint &uiIp,t_ushort &usPort) const
{
	uiIp = this->uiIp;
	usPort = this->usPort;
}
void KIpv4Addr::GetAddr(std::string &strIp,t_ushort &usPort) const
{
	SOCKADDR_IN addr;
	GetAddr(addr);
	strIp = inet_ntoa(addr.sin_addr);
	usPort = this->usPort;
}
bool KIpv4Addr::operator == (const KIpv4Addr &addr) const
{
	return (this->uiIp==addr.uiIp) && (this->usPort==addr.usPort);
}

bool KIpv4Addr::operator != (const KIpv4Addr &addr) const
{
	return (this->uiIp!=addr.uiIp) || (this->usPort!=addr.usPort);
}

const KIpv4Addr & KIpv4Addr::operator = (const KIpv4Addr &addr)
{
	this->uiIp = addr.uiIp;
	this->usPort = addr.usPort;
	return *this;
}
std::string KIpv4Addr::ToString() const
{
	std::string strIp;
	t_ushort usPort;
	GetAddr(strIp,usPort);
	char buf[16];
	itoa(usPort,buf,10);
	return strIp + ":" + buf;
}


#pragma pack () //�ֽڶ��뷽ʽ���Ĭ��ֵ 