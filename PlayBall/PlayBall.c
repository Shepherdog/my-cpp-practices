
#include <stdio.h>
#include <windows.h>


/*
* 利用多线程模拟球员传球
* */
const static int MAX_PLAYER = 5;   //球员人数

const char Players[] = "ABCDEFGHIJ";   //球员编号
UINT nIndex = 0;
BOOL bBall = FALSE;
//HANDLE hEvent = NULL;

//创建一个球员线程
DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	char Player = Players[nIndex++];
	printf("%c begin.\n", Player);
	
	//WaitForSingleObject(hEvent, INFINITE);
	
	while(TRUE)
	{
		if(bBall)
		{
			printf("%c got the ball\n", Player);   //接球
			bBall = FALSE;
			Sleep(1000);
			
			printf("%c passed the ball\n", Player);   //传球
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
	
	bBall = TRUE;   //发球
	
	WaitForMultipleObjects(MAX_PLAYER, hThread, TRUE, INFINITE);

	return 0;
}