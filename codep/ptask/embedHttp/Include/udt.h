/*****************************************************************************
Copyright (c) 2001 - 2008, The Board of Trustees of the University of Illinois.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

* Redistributions of source code must retain the above
copyright notice, this list of conditions and the
following disclaimer.

* Redistributions in binary form must reproduce the
above copyright notice, this list of conditions
and the following disclaimer in the documentation
and/or other materials provided with the distribution.

* Neither the name of the University of Illinois
nor the names of its contributors may be used to
endorse or promote products derived from this
software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************/

/*****************************************************************************
written by
Yunhong Gu, last updated 12/01/2008
*****************************************************************************/

#ifndef __UDT_H__
#define __UDT_H__


#ifndef WIN32
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#else
#pragma warning(disable:4127)
#pragma warning(disable:4251)
#include <WinSock2.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
#include <fstream>
#include <set>
#include <string>

////////////////////////////////////////////////////////////////////////////////
//#include "debug.h"
//#include "../win/TPeerProtocol.h"
#include <boost/shared_ptr.hpp>
class TBaseNetwork;	
class Connection;
class ConnMng;
//class TPeerImpl;
//class TPeerMngImpl;
class NPeerMng;
struct TBasePack;


////////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
// Explicitly define 32-bit and 64-bit numbers
typedef __int32 int32_t;
typedef __int64 int64_t;
typedef unsigned __int32 uint32_t;
#if _MSC_VER >= 1300
typedef unsigned __int64 uint64_t;
#else
// VC 6.0 does not support unsigned __int64: may cause potential problems.
typedef __int64 uint64_t;
#endif

#ifdef UDT_EXPORTS
#define UDT_API __declspec(dllexport)
#else
#define UDT_API __declspec(dllimport)
#endif
#else
#define UDT_API
#endif

#define NO_BUSY_WAITING

#ifndef WIN32
typedef int UDPSOCKET;
#else
typedef SOCKET UDPSOCKET;
#endif

typedef int UDTSOCKET;

typedef std::set<UDTSOCKET> ud_set;
#define UD_CLR(u, uset) ((uset)->erase(u))
#define UD_ISSET(u, uset) ((uset)->find(u) != (uset)->end())
#define UD_SET(u, uset) ((uset)->insert(u))
#define UD_ZERO(uset) ((uset)->clear())

////////////////////////////////////////////////////////////////////////////////

enum UDTOpt
{
	UDT_MSS,             // the Maximum Transfer Unit
	UDT_SNDSYN,          // if sending is blocking
	UDT_RCVSYN,          // if receiving is blocking
	UDT_CC,              // custom congestion control algorithm
	UDT_FC,		// Flight flag size (window size)
	UDT_SNDBUF,          // maximum buffer in sending queue
	UDT_RCVBUF,          // UDT receiving buffer size
	UDT_LINGER,          // waiting for unsent data when closing
	UDP_SNDBUF,          // UDP sending buffer size
	UDP_RCVBUF,          // UDP receiving buffer size
	UDT_MAXMSG,          // maximum datagram message size
	UDT_MSGTTL,          // time-to-live of a datagram message
	UDT_RENDEZVOUS,      // rendezvous connection mode
	UDT_SNDTIMEO,        // send() timeout
	UDT_RCVTIMEO,        // recv() timeout
	UDT_REUSEADDR,	// reuse an existing port or create a new one
	UDT_MAXBW		// maximum bandwidth (bps) that the connection can use
};

////////////////////////////////////////////////////////////////////////////////

struct CPerfMon
{
	// global measurements
	int64_t msTimeStamp;                 // time since the UDT entity is started, in milliseconds
	int64_t pktSentTotal;                // total number of sent data packets, including retransmissions
	int64_t pktRecvTotal;                // total number of received packets
	int pktSndLossTotal;                 // total number of lost packets (sender side)
	int pktRcvLossTotal;                 // total number of lost packets (receiver side)
	int pktRetransTotal;                 // total number of retransmitted packets
	int pktSentACKTotal;                 // total number of sent ACK packets
	int pktRecvACKTotal;                 // total number of received ACK packets
	int pktSentNAKTotal;                 // total number of sent NAK packets
	int pktRecvNAKTotal;                 // total number of received NAK packets

	// local measurements
	int64_t pktSent;                     // number of sent data packets, including retransmissions
	int64_t pktRecv;                     // number of received packets
	int pktSndLoss;                      // number of lost packets (sender side)
	int pktRcvLoss;                      // number of lost packets (receiverer side)
	int pktRetrans;                      // number of retransmitted packets
	int pktSentACK;                      // number of sent ACK packets
	int pktRecvACK;                      // number of received ACK packets
	int pktSentNAK;                      // number of sent NAK packets
	int pktRecvNAK;                      // number of received NAK packets
	double mbpsSendRate;                 // sending rate in Mb/s
	double mbpsRecvRate;                 // receiving rate in Mb/s

	// instant measurements
	double usPktSndPeriod;               // packet sending period, in microseconds
	int pktFlowWindow;                   // flow window size, in number of packets
	int pktCongestionWindow;             // congestion window size, in number of packets
	int pktFlightSize;                   // number of packets on flight
	double msRTT;                        // RTT, in milliseconds
	double mbpsBandwidth;                // estimated bandwidth, in Mb/s
	int byteAvailSndBuf;                 // available UDT sender buffer size
	int byteAvailRcvBuf;                 // available UDT receiver buffer size
};

////////////////////////////////////////////////////////////////////////////////

class UDT_API CUDTException
{
public:
	CUDTException(int major = 0, int minor = 0, int err = -1);
	CUDTException(const CUDTException& e);
	virtual ~CUDTException();

	// Functionality:
	//    Get the description of the exception.
	// Parameters:
	//    None.
	// Returned value:
	//    Text message for the exception description.

	virtual const char* getErrorMessage();

	// Functionality:
	//    Get the system errno for the exception.
	// Parameters:
	//    None.
	// Returned value:
	//    errno.

	virtual const int getErrorCode() const;

	// Functionality:
	//    Clear the error code.
	// Parameters:
	//    None.
	// Returned value:
	//    None.

	virtual void clear();

private:
	int m_iMajor;        // major exception categories

	// 0: correct condition
	// 1: network setup exception
	// 2: network connection broken
	// 3: memory exception
	// 4: file exception
	// 5: method not supported
	// 6+: undefined error

	int m_iMinor;		// for specific error reasons
	int m_iErrno;		// errno returned by the system if there is any
	std::string m_strMsg;	// text error message

public: // Error Code
	static const int SUCCESS;
	static const int ECONNSETUP;
	static const int ENOSERVER;
	static const int ECONNREJ;
	static const int ESOCKFAIL;
	static const int ESECFAIL;
	static const int ECONNFAIL;
	static const int ECONNLOST;
	static const int ENOCONN;
	static const int ERESOURCE;
	static const int ETHREAD;
	static const int ENOBUF;
	static const int EFILE;
	static const int EINVRDOFF;
	static const int ERDPERM;
	static const int EINVWROFF;
	static const int EWRPERM;
	static const int EINVOP;
	static const int EBOUNDSOCK;
	static const int ECONNSOCK;
	static const int EINVPARAM;
	static const int EINVSOCK;
	static const int EUNBOUNDSOCK;
	static const int ENOLISTEN;
	static const int ERDVNOSERV;
	static const int ERDVUNBOUND;
	static const int ESTREAMILL;
	static const int EDGRAMILL;
	static const int EDUPLISTEN;
	static const int ELARGEMSG;
	static const int EASYNCFAIL;
	static const int EASYNCSND;
	static const int EASYNCRCV;
	static const int EUNKNOWN;
};

namespace UDT
{
	typedef CUDTException ERRORINFO;
	typedef UDTOpt SOCKOPT;
	typedef CPerfMon TRACEINFO;
	typedef ud_set UDSET;

	UDT_API extern const UDTSOCKET INVALID_SOCK;
#undef ERROR
	UDT_API extern const int ERROR;

	UDT_API int startup();
	UDT_API int cleanup();
	UDT_API UDTSOCKET socket(int af, int type, int protocol);
	UDT_API int bind(UDTSOCKET u, const struct sockaddr* name, int namelen);
	UDT_API int bind(UDTSOCKET u, UDPSOCKET udpsock);
	UDT_API int listen(UDTSOCKET u, int backlog);
	UDT_API UDTSOCKET accept(UDTSOCKET u, struct sockaddr* addr, int* addrlen);
	UDT_API int connect(UDTSOCKET u, const struct sockaddr* name, int namelen);
	UDT_API int close(UDTSOCKET u);
	UDT_API int getpeername(UDTSOCKET u, struct sockaddr* name, int* namelen);
	UDT_API int getsockname(UDTSOCKET u, struct sockaddr* name, int* namelen);
	UDT_API int getsockopt(UDTSOCKET u, int level, SOCKOPT optname, void* optval, int* optlen);
	UDT_API int setsockopt(UDTSOCKET u, int level, SOCKOPT optname, const void* optval, int optlen);
	UDT_API int send(UDTSOCKET u, const char* buf, int len, int flags);
	UDT_API int recv(UDTSOCKET u, char* buf, int len, int flags);
	UDT_API int sendmsg(UDTSOCKET u, const char* buf, int len, int ttl = -1, bool inorder = false);
	UDT_API int recvmsg(UDTSOCKET u, char* buf, int len);
	UDT_API int64_t sendfile(UDTSOCKET u, std::ifstream& ifs, int64_t offset, int64_t size, int block = 364000);
	UDT_API int64_t recvfile(UDTSOCKET u, std::ofstream& ofs, int64_t offset, int64_t size, int block = 7280000);
	UDT_API int select(int nfds, UDSET* readfds, UDSET* writefds, UDSET* exceptfds, const struct timeval* timeout);
	UDT_API ERRORINFO& getlasterror();
	UDT_API int perfmon(UDTSOCKET u, TRACEINFO* perf, bool clear = true);

	//====================================================
	//UDT����ӿڣ���������������������͸
	//====================================================
	//added by tianzuo,2009-2-5
	//�ȴ��µ����ӵ������κε�ַ�������������ӵľ��
	//UDT_API int waitconnect(UDTSOCKET u, const struct timeval* timeout);

	//====================================================
	//P2P�����ײ�ӿ�
	//�������û�ID�ͷ���ǽ��͸����
	//====================================================
	//������Ϣ������
	class UDT_API INetworkListener
	{
	public:
		virtual ~INetworkListener(){};
		enum enNetworkCode{
			NL_CODE_NEWCONN = 0,    //���ӽ���
			NL_CODE_BREAKDOWN = 1,  //�����ж�
			//NL_CODE_SENDSUCCEED = 2,//���ݷ��ͳɹ�
			//NL_CODE_SENDFAILED = 3, //���ݷ���ʧ��
		};
		virtual void OnConnectionMsg(int iConn,enNetworkCode code,int param) = 0;
		virtual void OnData(int iConn,int iLen, const char *pData) = 0;
	};
	class UDT_API P2PNetworkBase
	{
	public:
		P2PNetworkBase(int iUDPPort);
		P2PNetworkBase(const sockaddr* name, int namelen);
		~P2PNetworkBase();
		int GetPort();
		//����������Ϣ������
		void SetNetworkListener(INetworkListener *pListener);
		//��ĳ����ַ�������ӣ���������ɹ����ᴥ�� NL_CODE_NEWCONN ��Ϣ��
		void ShootTo(const sockaddr* name, int namelen);
		//�������ݡ�
		//�����첽���͡�
		//���ͳɹ��ᴥ��NL_CODE_SENDSUCCEED��Ϣ�����򴥷�NL_CODE_SENDFAILED��Ϣ��
		//��Ϣ��param����iMsgID��
		int SendTo(int iConn,int iLen, const char *pData);
		//�ر�����
		void CloseConn(int iConn);

		//���ⲿ������socket�����������
		void AddConn(UDTSOCKET u);
		//��ȡ��������
		void GetConns(std::set<UDTSOCKET> &setConns);

		//��������
		UDTSOCKET CreateSocket(bool bRendezvous=true);
	private:
		TBaseNetwork *m_pBase;
	};

	//====================================================
	//P2P�����ײ�ӿ� - �������ӵķ�װ
	//�������û�ID�ͷ���ǽ��͸����
	//====================================================
	class TConnectMng;
	unsigned int WINAPI ThreadTryConnect(LPVOID s);

	//��װһ��UDT����
	class UDT_API TConnection
	{
	public:
		TConnection(TConnectMng *pMng,UDTSOCKET u=UDT::INVALID_SOCK);
		virtual ~TConnection();
		void SetSocket(UDTSOCKET u);
		UDTSOCKET GetSocket();
		//TConnectMng *GetMng();
		//void GetAddr(sockaddr* name, int &namelen);
		bool ConnectToEx(const sockaddr* name, int namelen);
		bool IsReady();

		int  Send(const char* pData,int iLen);
		int GetPerformance(TRACEINFO &ti,bool bClear=true);
		bool Close();

		virtual void  OnConnected(bool bSuccess);
		virtual void  OnDisConnected();
		virtual void  OnData(const char* pData, int ilen);

	protected:
		friend class TConnectMng;
		friend unsigned int WINAPI ThreadTryConnect(LPVOID s);
		bool  ThreadConnect();

		mutable UDTSOCKET m_uSocket;
		TConnectMng *m_pMng;
		uintptr_t m_threadTryConnect;

		sockaddr m_saDist;

	};

	//UDT���ӹ�����
	class UDT_API TConnectMng:
		public UDT::INetworkListener
	{
	public:
		TConnectMng(int iPort, void* pParam=NULL );
		virtual ~TConnectMng();

		//�����������������˺����ᱻ�����Բ���һ��TConnection����
		virtual TConnection *ConnFactory(UDTSOCKET u);

		//���Ӳ���
		inline void* GetParam(){ return m_pParam; };

		//////////////////////////////////////////////////////////////////////////
	private:
		void AddConn(TConnection *pConn);
		void RemoveConn(TConnection *pConn);

		void OnConnectionMsg(int iConn,enNetworkCode code,int param);
		void OnData(int iConn,int iLen, const char *pData);
		UDT::P2PNetworkBase *GetBase();
		UDTSOCKET CreateSocket(bool bRendezvous=true);


	private:
		friend class ConnMng;
		friend class TConnection;
		ConnMng *m_pConnMng;
		void* m_pParam;
	};

	//һ������ʹ�õ�ģ���࣬�Ա�ʹ���߿��Բ��ش���TConnectMng���࣬Ҳ��ʹ��TConnection
	//����������������ʱ�򣬻��Զ�new T_Conn��
	template<class T_Conn>
	class TConnectMngTemplate
		:public TConnectMng
	{
	public:
		TConnectMngTemplate(int iPort, void* pParam=NULL):TConnectMng(iPort , pParam ){};
		virtual ~TConnectMngTemplate(){};
		TConnection *ConnFactory(UDTSOCKET u)
		{
			return new T_Conn(this,u);
		}
	};

	//1.TPeer�ࡣ
	//TPeer�ഴ����ʱ��Ҫ��NPeerMng����id-->TPeer���ϡ�
	//TPeer��ֱ�ӽ��У���������ͳһ����NPeerMng�ƹܡ�
	//TPeer��Ҫ������պ�ת����Ϣ��
	//TPeer����ͬʱʹ�ö�����ӣ�Ŀǰ������UDT���ӣ����Ӹ������ӷ����������ݣ���������ղ�����Ӧ�ò���������һЩ�㷨�������ظ���ע�⣬����ʹ���˶�����ӣ���ô����Ҳ���п��ܵġ�
	//�������ݣ�����ѡ����л��һ�����ӣ�����������Ϊ���á�
	//�����������жϵ�ʱ�򣬲Żᷢ�������ж���Ϣ��
	//TPeer�˳���ʱ������������Ӷ�ɾ����
	class TPeerMng;
	class UDT_API TPeer
	{
	public:
		//������ֱ�Ӵ�����ɾ����������NPeerMng�е���غ�����
		//iPeerId��Ŀ��id��Ŀ��idΪ0��ʾ������������peer��id�����Ӻ���ȷ��      
		TPeer(TPeerMng *pMng,unsigned int iPeerId);
	public:

		virtual ~TPeer(void);
		//====�������ӷ�ʽ====
		//ͨ��STUN��������ѯ��ַ����
		bool  PeerConnect(int iWaitTime=0);       
		//֪����ַ��ֱ������
		bool  PeerConnect(const sockaddr* nameKnown, int namelen,bool bTrySTUN=false);
		//֪����ַ�͸����û�id��ֱ������
		bool  PeerConnect(const sockaddr* nameKnown, int namelen,int iHelperId,bool bTrySTUN=false); 

		unsigned int GetPeerId();
		int GetSpeed(int &iUpSpeed,int &iDownSpeed);
		bool IsReady();

		int  SendPeerMsg(const char* pData,int iLen);
		int  SendPack(const TBasePack *pPack,int iLen);
		void Close();
	public:
		//�ص�����
		virtual void  OnPeerConnected(bool bSuccess);           
		virtual void  OnPeerDisConnected();
		virtual void  OnPeerData(const char* pData, int ilen);
	protected:
		friend class TPeerMng;
		friend class NPeerMng;

		//���µ�ǰ����
		//���uΪINVALID_SOCKET����ô˵�����ӶϿ�
		void SetCurrentSocket(UDTSOCKET u);
		UDTSOCKET GetCurrentSocket();
		TPeerMng *GetPeerMng();
	private:
		TPeerMng *m_pMng;
		unsigned int m_iPeerId;
		UDTSOCKET m_currSocket;
	};

	//Peer��Ϣ������
	class UDT_API IPeerDataListener
	{
	public:
		//�ص�����
		//virtual void  OnPeerConnected(int iPeerId,bool bSuccess) = 0;           
		//virtual void  OnPeerDisConnected(int iPeerId) = 0;
		virtual void  OnPeerData(int iPeerId,const char* pData, int ilen) = 0;
	};

	//ָ��TPeer������ָ��
	typedef boost::shared_ptr<UDT::TPeer> TPeerPtr;
	class UDT_API TPeerMng
	{
	public:
		TPeerMng(unsigned int iMyId, const sockaddr* name, int namelen);  //ϵͳΨһ�Ľڵ�id����ڷ�������ַ
		virtual ~TPeerMng();

		//�Լ���id���ڿ�ʼ��ʱ�������0��ע�⣺IDֻ�ܸ���һ��
		bool UpdateId(unsigned int iMyId);
		unsigned int GetId();

		//���������������
		void ConnectToServer(unsigned int uiServerID, const sockaddr* name, int namelen);
		//�ر�������������ӣ���ʡ��������Դ��
		void CloseServerConnection();
		//����������ӵ�״̬
		bool IsServerConnectReady();

		//====�������ӷ�ʽ====
		//ͨ��STUN��������ѯ��ַ����
		bool  PeerConnect(unsigned int iPeerId,int iWaitTime=0);
		//֪����ַ��ֱ������
		bool  PeerConnect(unsigned int iPeerId,const sockaddr* nameKnown, int namelen,bool bTrySTUN=false);
		//֪����ַ�͸����û�id��ֱ������
		bool  PeerConnect(unsigned int iPeerId,const sockaddr* nameKnown, int namelen,unsigned int iHelperId,bool bTrySTUN=false); 

		//�û������Ƿ��Ѵ�����������û�������ϣ�
		bool  IsPeerExist(unsigned int iPeerId);
		//�û��Ƿ��Ѿ����ӳɹ�
		bool  IsPeerReady(unsigned int iPeerId);

		//����������û��б�
		void GetPeerSet(std::set<unsigned int> &setPeers);
		//�����û�ID�����û�
		TPeerPtr FindPeer(unsigned int iPeerId);
		//��ȡ�û���ַ���û��ж�����ӵģ����ص�ǰ�û���ַ
		bool GetPeerAddress( unsigned int iPeerId,sockaddr* name, int *namelen );
		//ͬ�ϡ�����û�û�����ӣ����ؿյ�ַ
		//KIpv4Addr GetPeerAddress(unsigned int iPeerId);

		//���û������û����ݣ��˺���Ч�ʽϵͣ��ᳫ��SendPeerPack��
		int SendPeerMsg( unsigned int iPeerId,const char *pData, int iLen );
		//���û�����TBasePack���ݰ�
		int SendPeerPack( unsigned int iPeerId,const TBasePack *pPack, int iLen );

		//����û�����ʵ��
		//�û�������ھͷ��أ���������ھ͵���PeerFactory��������һ��
		TPeerPtr GetPeerInstance(int iPeerId,int iTemplateType=0);
		//�ر����ӡ��˺����ر���������������ӣ��ͷŶ�Ӧ����ָ��
		void ClosePeer(unsigned int iPeerId);

		//ȫ����Ϣ������
		void AddPeerListener(IPeerDataListener *pListener);
		bool RemovePeerListener(const IPeerDataListener *pListener);
	private:
		friend class TPeer;
		friend class NPeerMng;
		NPeerMng *m_pPeerMngImpl;
	protected:
		//�û����󹤳���������������ʹ��
		virtual UDT::TPeerPtr PeerFactory(int iPeerId,int iTemplateType)=0; 
	};

	template<class T_Conn>
	class TPeerMngTemplate
		:public TPeerMng
	{
	public:
		TPeerMngTemplate(unsigned int iMyId, const sockaddr* name, int namelen):TPeerMng(iMyId,name,namelen){};
		virtual ~TPeerMngTemplate(){};
		UDT::TPeerPtr PeerFactory(int iPeerId,int iTemplateType)
		{
			return UDT::TPeerPtr(new T_Conn(this,iPeerId));
		}
	};
}

#endif
