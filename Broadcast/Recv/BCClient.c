
#include <winsock2.h>
#include <stdio.h>

#pragma comment(lib, "WS2_32.lib")

#define BUFF_SIZE 1024


int main(int argc, char* argv[])
{
	SOCKET s;
	SOCKADDR_IN addr;
	char buff[BUFF_SIZE];
	
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
	
	//���sockaddr_in�ṹ
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);
	addr.sin_addr.s_addr = INADDR_ANY;
	
	//���׽ӿ����ַ�ṹ��
	if(bind(s, (PSOCKADDR_IN)&addr, sizeof(addr)) == -1)
	{
		printf("Failed bind.\n");
		WSACleanup();
		return 0;
	}
	
	printf("Receiving Broadcast...\n");
	//ѭ�����չ㲥��Ϣ
	memset(&buff, 0, sizeof(buff));
	while(1)
	{
		recvfrom(s, buff, sizeof(buff), 0, NULL, NULL);
		printf("%s\n", buff);
	}
	
	//�ر��׽���
	closesocket(s);
	//�ͷ�WS2_32��
	WSACleanup();
	
	return 0;
}