
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define SQURE1(x) ((x)*(x))
#define SQURE2(x) (x*x)   //!��ֻ���б��ʽ�滻���������ַ��滻�п��ܻ��������


extern int global = 0;   //externʹ�ñ����ڶ��Դ�ļ��ж����Խ���ȫ�ַ���

typedef struct POINT   //�ṹ����������
{
	int x;
	int y;
}Point;

void display(int d)
{
	printf("The data is: %d\n", d);
}

void showData(int* array, int len, void(*func)(int d))   //ָ������ָ��
{
	int i;
	for(i=0; i<len; i++)
	{
		func(array[i]);
	}
}

void count(int k)
{
	static int x = 0;   //�ڲ���̬����,���ڴ�ռ��ھ�̬�洢�������
	x += k;
	printf("%d\n", x);
}

/*
 * �ڴ������
 * */
void* memalloc(unsigned int size)
{
	void* memblock = malloc(size);   //��̬�ڴ棬���ڴ�ռ��ڶ��з���

	//���û���㹻�ڴ棬�����ڴ����ʧ��
	if(memblock == NULL)
	{
		//���˳�����
		exit(1);
	}

	return memblock;
}

void* meminit(void* memblock, char num, unsigned int size)
{
	unsigned int i;
	char* bytes;

	//����ڴ�����Ч
	if(memblock == NULL)
	{
		//���˳�����
		return NULL;
	}
	
	//����ڴ��ֽ�
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
		memblock = NULL;   //!�˴���������memblock�ĸ���
	}
}
*/
void memfree(void* *memblock)
{
	//����ڴ�����Ч
	if(*memblock != NULL)
	{
		//���ͷ��ڴ���
		free(*memblock);
		//����ڴ���ָ��
		*memblock = NULL;
	}
}

/*
 * �ַ�����������
 * */
char* strsamp(void)
{
	char* string = "Hello";   //λ�ھ�̬�洢�������ڳ������������Ǻ㶨�����ͬһ�ڴ�飬�����޸�
	//char string[] = "Hello";   //�����ھֲ����������ڴ�ռ���ջ�з���

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
	char* t_strdest = strdest;   //����Ŀ���ڴ�ָ��

	if((strdest==NULL) || (strsour==NULL))
	{
		return NULL;
	}
	//!��ʼ��Ŀ��ָ�벻��ָ��ͬһ�ڴ���
	if(strdest == strsour)
	{
		return strdest;
	}

	//����Դ�ڴ������ݵ�Ŀ���ڴ���
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

	//ͳ�Ʒ����ַ��ĸ���
	while(*(string++) != '\0')
	{
		len++;
	}

	return len;
}

char* strconn(char* strdest, char* strsour)
{
	int pos = 0;

	//!��ʼ��Ŀ��ָ�벻��ָ��ͬһ�ڴ���
	if((strdest==NULL) || (strdest==strsour))
	{
		return NULL;
	}
	if(strsour == NULL)
	{
		return strdest;
	}

	//����Դ�ڴ������ݵ�Ŀ���ڴ����ĺ�
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
	int a = 4;   //ȫ�ֱ���,���ڴ�ռ��ھ�̬�洢�������
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