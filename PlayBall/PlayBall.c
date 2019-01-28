
#include <stdio.h>
#include <windows.h>


/*
* ���ö��߳�ģ����Ա����
* */
const static int MAX_PLAYER = 5;   //��Ա����

const char Players[] = "ABCDEFGHIJ";   //��Ա���
UINT nIndex = 0;
BOOL bBall = FALSE;
//HANDLE hEvent = NULL;

//����һ����Ա�߳�
DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	char Player = Players[nIndex++];
	printf("%c begin.\n", Player);
	
	//WaitForSingleObject(hEvent, INFINITE);
	
	while(TRUE)
	{
		if(bBall)
		{
			printf("%c got the ball\n", Player);   //����
			bBall = FALSE;
			Sleep(1000);
			
			printf("%c passed the ball\n", Player);   //����
			bBall = TRUE;
			Sleep(1000);
		}
	}
    return 0;
}


int main(void)
{
	//HANDLE hThread[MAX_PLAYER];
	HANDLE* hThread = (HANDLE*)calloc(MAX_PLAYER, sizeof(HANDLE));
	DWORD dwThreadID;
	int i;
	
	//hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	
	for(i=0; i<MAX_PLAYER; i++)
	{
		hThread[i] = CreateThread(NULL, NULL, ThreadProc, NULL, 0, &dwThreadID);
		if(hThread == NULL)
		{
			printf("An error occured when initialization.\n");
			return 1;
		}
	}
	
	printf("The match start.\n");
	Sleep(1000);
	
	//SetEvent(hEvent);
	
	bBall = TRUE;   //����
	
	WaitForMultipleObjects(MAX_PLAYER, hThread, TRUE, INFINITE);

	return 0;
}