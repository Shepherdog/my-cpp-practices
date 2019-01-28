
#include <stdio.h>
#include <winsock2.h>
#include "mstcpip.h"   //from \Visual Studio 8\VC\PlatformSDK\Include
#include "header.h"

#pragma comment(lib, "WS2_32.lib")


int main()
{
	WSADATA wsadata;
	SOCKET sock;
	SOCKADDR_IN addr, from;
	DWORD num;
	int rcvall;
	char* buf;
	
	WSAStartup(WINSOCK_VERSION, &wsadata);
	sock = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
	if(sock == INVALID_SOCKET)
	{
		printf("Failed Socket.\n");
		WSACleanup();
		return 0;
	}
	
	memset(&addr, 0, sizeof(addr));
	//addr.sin_addr.s_addr = inet_addr("172.0.0.1");
	addr.sin_family = AF_INET;
	
	if(bind(sock, (PSOCKADDR_IN)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		printf("Failed Bind.\n");
		closesocket(sock);
		WSACleanup();
		return 0;
	}
	
	//�����׽ӿ�IO���ƣ�ʹ������������ݰ�
	rcvall = RCVALL_ON;
	if(WSAIoctl(sock, SIO_RCVALL, &rcvall, sizeof(rcvall), NULL, 0, &num, NULL, NULL) == SOCKET_ERROR)
	{
		printf("Failed WSAIoctl.\n");
		closesocket(sock);
		WSACleanup();
		return 0;
	}
	
	//ѭ���������ݰ�������
	while(1)
	{
		buf = (char*)xmalloc(1024);
		memset(&buf, 0, sizeof(buf));
		memset(&from, 0, sizeof(from));
		
		if(recvfrom(sock, buf, sizeof(buf), 0, (PSOCKADDR_IN)&from, (int*)sizeof(from)) != SOCKET_ERROR)
		{
			switch(((IPHdr*)buf)->proto)
			{
			case IPPROTO_TCP:    //TCPЭ�����ݰ�
				printf("TCP from %s\n", inet_ntoa(from.sin_addr));
				break;
				
			case IPPROTO_UDP:    //UDPЭ�����ݰ�
				printf("UDP from %s\n", inet_ntoa(from.sin_addr));
				break;
				
			case IPPROTO_ICMP:   //ICMPЭ�����ݰ�
				printf("ICMP from %s\n", inet_ntoa(from.sin_addr));
				break;
				
			case IPPROTO_IGMP:   //IGMPЭ�����ݰ�
				printf("IGMP from %s\n", inet_ntoa(from.sin_addr));
				break;
				
			default:
				printf("Unknown datagram from %s\n", inet_ntoa(from.sin_addr));
			}
		}
		else
		{
			Sleep(1);
		}
		xfree(buf);
	}
	
	closesocket(sock);
	WSACleanup();
	
	return 0;
}