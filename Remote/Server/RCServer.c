
#include <winsock2.h>
#include <stdio.h>
#include <windows.h>

#pragma comment(lib,"WS2_32.lib")


int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET s, client;
	SOCKADDR_IN sin, remoteAddr;
	int nAddrLen;
	char szIP[16];
	char szCmd[64];        //����ָ�����
	char szBuff[1024*8];   //������Ϣ������
	int nSend, nRecv;
	
	//��ʼ��WS2_32.dll
	WORD sockVersion = MAKEWORD(2, 0);
	WSAStartup(sockVersion, &wsaData);
	
	//�����׽���
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(s == INVALID_SOCKET)
	{
		printf("Failed socket() \n");
		WSACleanup();
		return 0;
	}
	
	//���sockaddr_in�ṹ
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	
	//������׽��ֵ�һ�����ص�ַ
	if(bind(s, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf("Failed bind() \n");
		WSACleanup();
		return 0;
	}
	
	//�������ģʽ
	if(listen(s, 2) == SOCKET_ERROR)
	{
		printf("Failed listen()");
		WSACleanup();
		return 0;
	}
	
	//���ܿͻ�������
	nAddrLen = sizeof(remoteAddr);
	client = accept(s, (SOCKADDR*)&remoteAddr, &nAddrLen);
	if(client == INVALID_SOCKET)
	{
		printf("Failed accept()");
	}
	printf(">A Connection Accepted:\n>IP:%s Port:%d\r\n", 
		inet_ntoa(remoteAddr.sin_addr), remoteAddr.sin_port);
	sprintf(szIP, "%s", inet_ntoa(remoteAddr.sin_addr));
	
	//ѭ����ͻ��˷��Ϳ���ָ��
	while(1)
	{
		//��ʼ��������
		memset(szCmd, 0, sizeof(szCmd));
		memset(szBuff, 0, sizeof(szBuff));
		
		//�û��������ָ��
		printf("[root@%s]: ", szIP);
		gets(szCmd);
		
		//��ͻ��˷��Ϳ���ָ��
		nSend = send(client, szCmd, strlen(szCmd), 0);
		
		//���ղ���ʾ���Կͻ��˵ķ�����Ϣ
		nRecv = recv(client, szBuff, sizeof(szBuff), 0);
		if(nRecv == SOCKET_ERROR)
		{
			MessageBox(NULL, "Client has been shut down", "Error", MB_OK);
			break;
		}
		if(nRecv > 0)
		{
			szBuff[nRecv] = '\0';
			printf("%s\n", szBuff);
		}
	}
	
	//�ر�ͬ�ͻ��˵�����
	closesocket(client);
	
	//�رռ����׽���
	closesocket(s);
	//�ͷ�WS2_32��
	WSACleanup();	
	
	return 0;
}