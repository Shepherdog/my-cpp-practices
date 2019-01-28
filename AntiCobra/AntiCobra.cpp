// AntiCobra.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#pragma warning(disable:4786)
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

#include <stdlib.h>
#include <direct.h>
#include <string.h> 
#include <io.h> 

using namespace std;

vector<string> files;

bool isEncrypted(const char* strFile);
bool processFile(const char* filename);
bool decryptFile(const char* filename);
bool enumFiles(const char* dir, const char* filespec);


bool isEncrypted(const char* strFile)
{
#define MAX_PATTERN_LEN 16
#define PATTERN_OFFSET 12

	char buffer[MAX_PATTERN_LEN+1];
	char pattern[] = {0x45, 0x2d, 0x53, 0x61, 0x66, 0x65, 0x4e, 0x65, 0x74, 0x00, 0x00, 0x00, 0x4c, 0x4f, 0x43, 0x4b, '\0'};

	FILE *fp = fopen(strFile, "r+b");
	
	if (fp == NULL)
	{
		printf("file open error!\n");
		return false;
	}
	
	memset(buffer, '\0', MAX_PATTERN_LEN+1);
	fseek(fp, PATTERN_OFFSET, SEEK_SET);
	fread(buffer, sizeof(char), MAX_PATTERN_LEN, fp);
	
	if (memcmp(buffer, pattern, MAX_PATTERN_LEN) == 0)
	{
		//fprintf(another_file_pointer, "%s\n", strFile);
		printf("[Encrypted] %s\n", strFile);
		return true;
	}
	
	fclose(fp);
	return false;
}

bool enumFiles(const char* dir, const char* filespec)
{
	_chdir(dir);
	
	//���Ȳ���dir�з���Ҫ����ļ�
	long hFile;
	_finddata_t fileinfo;
	
	if ((hFile = _findfirst(filespec, &fileinfo)) != -1)
	{
		do
		{
			//����ǲ���Ŀ¼
			//�������,����д���
			if (!(fileinfo.attrib & _A_SUBDIR))
			{
				char filename[_MAX_PATH];
				strcpy(filename, dir);
				strcat(filename, fileinfo.name);
				//if (!ProcessFile(filename))
				processFile(filename);
				//string name = fileinfo.name;
				//files.push_back(name);
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
	
	//����dir�е���Ŀ¼
	//��Ϊ�ڴ���dir�е��ļ�ʱ���������ProcessFile�п��ܸı���
	//��ǰĿ¼����˻�Ҫ�������õ�ǰĿ¼Ϊdir��
	//ִ�й�_findfirst�󣬿���ϵͳ��¼���������Ϣ����˸ı�Ŀ¼
	//��_findnextû��Ӱ�졣
	_chdir(dir);
	if ((hFile = _findfirst("*.*", &fileinfo)) != -1)
	{
		do
		{
			//����ǲ���Ŀ¼
			//�����,�ټ���ǲ��� . �� .. 
			//�������,���е���
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name,".") != 0 && strcmp (fileinfo.name,"..") != 0)
				{
					char subdir[_MAX_PATH];
					strcpy(subdir, dir);
					strcat(subdir, fileinfo.name);
					strcat(subdir, "\\");
					//ProcessDir(subdir, dir);
					if (!enumFiles(subdir, filespec))
						return false;
				}
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
	return true;
}

bool processFile(const char* filename)
{
	//if (isEncrypted(filename))
	//{
		files.push_back(filename);
	//}
	return true;
}

bool decryptFile(const char* filename)
{
	char cmdstr[512] = {0};
	sprintf(cmdstr, "type %s > %s.bak", filename, filename);
	system(cmdstr);
	return true;
}

void removePostfix(const char* filename)
{
	int len = strlen(filename);
	char* tmp = (char*) malloc(len);
	memset(tmp, '\0', len);

	strncpy(tmp, filename, len-4);	// remove ".bak"
	len = strlen(tmp);
	for(int i = len; *(tmp+i) != '\\'; i--);	// locate the last '\'
	char newfile[64] = {0};
	strcpy(newfile, tmp+i+1);

	free(tmp);

	char cmdstr[512] = {0};
	sprintf(cmdstr, "ren %s %s", filename, newfile);
	printf("%s\n", cmdstr);
	system(cmdstr);
}

int main(int argc, char* argv[])
{
	//if (argc < 3) return -1;

	//char spec_filter[][8] = { "*.h", "*.c", "*.cpp" };
	char spec_filter[][8] = { "*.bak" };

	int num_filter = sizeof(spec_filter)/sizeof(spec_filter[0]);
	for (int i=0; i<num_filter; i++)
	{
		//enumFiles(argv[1], spec_filter[i]);
		enumFiles("e:\\workspace\\", spec_filter[i]);
	}

	for (int j=0; j<files.size(); j++)
	{
		//decryptFile(files[j].c_str());
		removePostfix(files[j].c_str());
	}
	return 0;
}
