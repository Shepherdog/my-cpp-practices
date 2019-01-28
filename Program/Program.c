
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define SQURE1(x) ((x)*(x))
#define SQURE2(x) (x*x)   //!宏只进行表达式替换，并且在字符替换中可能会产生错误


extern int global = 0;   //extern使该变量在多个源文件中都可以进行全局访问

typedef struct POINT   //结构体数据类型
{
	int x;
	int y;
}Point;

void display(int d)
{
	printf("The data is: %d\n", d);
}

void showData(int* array, int len, void(*func)(int d))   //指向函数的指针
{
	int i;
	for(i=0; i<len; i++)
	{
		func(array[i]);
	}
}

void count(int k)
{
	static int x = 0;   //内部静态变量,此内存空间在静态存储区域分配
	x += k;
	printf("%d\n", x);
}

/*
 * 内存管理函数
 * */
void* memalloc(unsigned int size)
{
	void* memblock = malloc(size);   //动态内存，此内存空间在堆中分配

	//如果没有足够内存，导致内存分配失败
	if(memblock == NULL)
	{
		//则退出程序
		exit(1);
	}

	return memblock;
}

void* meminit(void* memblock, char num, unsigned int size)
{
	unsigned int i;
	char* bytes;

	//如果内存区无效
	if(memblock == NULL)
	{
		//则退出函数
		return NULL;
	}
	
	//填充内存字节
	bytes = (char*)memblock;
	for(i=0; i<size; i++)
	{
		*(bytes++) = num;
	}

	return memblock;
}

/*
void memfree(void* memblock)
{
	if(memblock != NULL)
	{
		free(memblock);
		memblock = NULL;   //!此处操作的是memblock的副本
	}
}
*/
void memfree(void* *memblock)
{
	//如果内存区有效
	if(*memblock != NULL)
	{
		//则释放内存区
		free(*memblock);
		//清除内存区指针
		*memblock = NULL;
	}
}

/*
 * 字符串操作函数
 * */
char* strsamp(void)
{
	char* string = "Hello";   //位于静态存储区，它在程序生命期内是恒定不变的同一内存块，不能修改
	//char string[] = "Hello";   //函数内局部变量，此内存空间在栈中分配

	return string;
}

/*
void strcopy(char* strdest, char* strsour)
{
	if((strdest==NULL) || (strsour==NULL))
	{
		return;
	}

	while(*strsour != '\0')
	{
		*(strdest++) = *(strsour++);
	}
	*strdest = '\0';
}
*/
char* strcopy(char* strdest, char* strsour)
{
	char* t_strdest = strdest;   //保存目的内存指针

	if((strdest==NULL) || (strsour==NULL))
	{
		return NULL;
	}
	//!起始和目的指针不能指向同一内存区
	if(strdest == strsour)
	{
		return strdest;
	}

	//复制源内存区数据到目的内存区
	while(*strsour != '\0')
	{
		*(strdest++) = *(strsour++);
	}
	*strdest = '\0';

	return t_strdest;
}

int strleng(char* string)
{
	unsigned int len = 0;

	if(string == NULL)
	{
		return 0;
	}

	//统计非零字符的个数
	while(*(string++) != '\0')
	{
		len++;
	}

	return len;
}

char* strconn(char* strdest, char* strsour)
{
	int pos = 0;

	//!起始和目的指针不能指向同一内存区
	if((strdest==NULL) || (strdest==strsour))
	{
		return NULL;
	}
	if(strsour == NULL)
	{
		return strdest;
	}

	//复制源内存区数据到目的内存区的后部
	pos = strleng(strdest);
	/*
	int len = strleng(strsour);
	
	int i;
	for(i=0; i<len; i++)
	{
		*(strdest+pos+i) = *(strsour+i);
	}
	*(strdest+pos+len+1) = '\0';
	*/
	while(*strsour != '\0')
	{
		*(strdest+pos) = *(strsour++);
		pos++;
	}
	*(strdest+pos) = '\0';

	return strdest;
}

void main()
{
	/*
	int a = 4;   //全局变量,此内存空间在静态存储区域分配
	unsigned int b = 3;
	int c = 2;
	//printf("%d\n", a>b>c);
	printf("%d\n", (a>b)&&(b>c));
	//
	long d = 0x12345678;
	long e;
	e = d>>16;
	//e = d & 0x0000ffff;
	//e = d;   //e = (int)d;
	//printf("%x\n", e);
	//
	int h = 1;
	int i = 4;
	h *= i-2;   //h *= (i-2);
	//printf("%d\n", h);
	//
	//(2+2) * (2+2) = 16
	printf("%d\n", SQURE1(2+2));
	//2+2 * 2+2 = 8
	printf("%d\n", SQURE2(2+2));
	//
	for(int m=0; m<=3; m++)
	{
		count(m);
	}
	//
	int data[3] = {1, 2};
	showData(data, 3, display);
	*/
	//char str1[20];
	char* str1 = (char*)memalloc(sizeof(char)*20);
	//char str2[] = "Hello";
	//char* str2 = "Hello";
	char* str2 = strsamp();
	char* str3 = NULL;
	char str4[20];
	str1 = (char*)meminit(str1, 0, 20);
	str3 = strcopy(str1, str2);
	strcopy(str4, str2);
	strcopy(str2, str2);
	if(str1 != NULL)
	{
		printf("str1: %s\n", str1);
		printf("str2: %s\n", str2);
		printf("str3: %s\n", str3);
		printf("str4: %s\n", str4);
		printf("str1+4: %s\n", strconn(str1, str4));
		printf("str1+3: %s\n", strconn(str1, str3));
	}
	//memfree((void**)&str1);
	memfree(&str1);
	//str1 = NULL;
	printf("str1: %s\n", str1);
	printf("str3: %s\n", str3);
	memfree(&str1);
}