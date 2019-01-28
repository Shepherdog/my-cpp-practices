
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "words.h"


int retrieve_data(void)
{
	FILE* fp = NULL;
	char temp[30];
	int wc = 0;
	
	//读取数据文件
	fp = fopen("words.txt", "r");
	if(!fp)
	{
		perror("An error occured when open file");
		fclose(fp);
		return 0;
	}
	
	while(wc < MAX_WORD)
	{
		if(!feof(fp))
		{
			memset(temp, 0, sizeof(temp));
			fscanf(fp, "%s", &temp);
			//printf("%s\n", temp);
			//strncpy(word[wc], temp, sizeof(temp));
			strcpy(word[wc], temp);
			wc++;
		}
	}
	return 1;
}

void create_hash(void)
{
	int i, j;
	int k, n=0;
	int bExist = 0;
	ValueNode* valuenode;
	
	//初始化Hash散列表
	for(i=0; i<MAX_NODE; i++)
	{
		hashnode[i].index = '\0';
		hashnode[i].valuenode = NULL;
	}
	
	//开始构建Hash散列表
	for(j=0; j<MAX_WORD; j++)
	{
		k = 0;
		bExist = 0;
		
		//检查是否有重码
		while(k < MAX_NODE)
		{
			if(hashnode[k].index == word[j][0])
			{
				bExist = 1;
				break;
			}
			else
			{
				k++;
			}
		}
		
		//没有重码
		if(!bExist)
		{
			hashnode[++n].index = word[j][0];
			valuenode = (ValueNode*)calloc(1, sizeof(ValueNode));
			strcpy(valuenode->value, word[j]);
			//printf("load %s\n", word[j]);
			valuenode->next = NULL;
			hashnode[n].valuenode = valuenode;
		}
		//存在重码
		else
		{
			valuenode = (ValueNode*)calloc(1, sizeof(ValueNode));
			strcpy(valuenode->value, word[j]);
			//printf("load %s\n", word[j]);
			valuenode->next = NULL;
			valuenode->next = hashnode[k].valuenode;
			hashnode[k].valuenode = valuenode;
		}
	}
	//创建Hash散列表完成
}

int query_hash(char query[], char result[])
{
	int i;
	char* word;
	ValueNode* valuenode;
	
	//查询Hash表索引
	for(i=0; i<MAX_NODE; i++)
	{
		if(hashnode[i].index == query[0])
		{
			//从链表提取数据
			valuenode = hashnode[i].valuenode;
			while(valuenode != NULL)
			{
				word = valuenode->value;
				if(strstr(word, query) != NULL)
				{
					strcat(result, word);
					strcat(result, "  ");
				}
				valuenode = valuenode->next;
			}
			return 1;
		}
	}
	return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////

int main(void)
{
	char query[30];
	char result[256];
	
	system("color a");
	
	if(!retrieve_data())
	{
		exit(1);
	}
	else
	{
		create_hash();
		printf("________________________________________________\n");
		printf("\n");
		printf("________________________________________________\n");
		while(1)
		{
			printf("Please input your query:");
			scanf("%s", &query);
			system("cls");
			printf("________________________________________________\n");
			memset(result, 0, sizeof(result));
			if(query_hash(query, result))
			{
				printf("%s\n", result);
			}
			else
			{
				printf("\n");
			}
			printf("________________________________________________\n");
		}
	}
	return 0;
}