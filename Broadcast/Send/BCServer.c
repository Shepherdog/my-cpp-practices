
#include <winsock2.h>
#include <stdio.h>

#pragma comment(lib, "WS2_32.lib")

#define BUFF_SIZE 1024


int main(int argc, char* argv[])
{
	SOCKET s;
	SOCKADDR_IN addr;
	int bBroadcast = 1;
	char szMsg[BUFF_SIZE];
	u_int nMsgId = 0;
	
	//��ʼ��WS2_32.dll
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 0);
	WSAStartup(sockVersion, &wsaData);
	
	//�����׽���
	s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(s == INVALID_SOCKET)
	{
		printf("Failed socket.\n");
		WSACleanup();
		return 0;
	}
	
	//�����׽ӿ�ѡ��ʹ��֧�ֹ㲥����
	if(setsockopt(s, SOL_SOCKET, SO_BROADCAST, (char*)&bBroadcast, sizeof(bBroadcast)) == SOCKET_ERROR)
	{
		printf("Failed setsockopt.\n");
		WSACleanup();
		return 0;
	}
	
	//���sockaddr_in�ṹ
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);
	addr.sin_addr.s_addr = INADDR_BROADCAST;   //inet_addr("255.255.255.255"); //���ع㲥��ַ
	
	printf("Sending Broadcast...");
	//ѭ�����͹㲥��Ϣ
	while(1)
	{
		sprintf(szMsg, "Message[ID:%d]", nMsgId);
		sendto(s, szMsg, strlen(szMsg), 0, (PSOCKADDR_IN)&addr, sizeof(addr));
		nMsgId++;
		
		Sleep(3000);
	}
	
	//�رռ����׽���
	closesocket(s);
	//�ͷ�WS2_32��
	WSACleanup();
	
	return 0;
}