
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RAW_SIZE 7
#define MAX_SIZE (RAW_SIZE+2)
#define ARR_SIZE(x) (sizeof(x)/sizeof(x[0]))


/*
* 快速排序算法
* */
int Partition(int* array, int left, int right)
{
	int start = array[left];
	int tmp = 0;
	int pivot = 0;
	
	while(left != right)
	{
		if(array[left] == array[right])
		{
			left++;
		}
		while(array[left] < start)
		{
			left++;
		}
		while(array[right] > start)
		{
			right--;
		}
		
		/*swap(array[left],array[right])*/
		tmp = array[left];
		array[left] = array[right];
		array[right] = tmp;
	}
	
	pivot = left;
	return pivot;
}

void QuickSort(int* array, int left, int right)
{
	int pivot = 0;
	
	if(left < right)
	{
		pivot = Partition(array, left, right);
		QuickSort(array, left, pivot-1);
		QuickSort(array, pivot+1, right);
	}
}


/*
* 二分查找算法
* */
int BiSearch(int* array, int left, int right, int query)
{
	int middle;
	int index = -1;
	
	while((left+1) != right)
	{
		middle = left + (right-left)/2;
		
		if(array[middle] < query)
		{
			left = middle;
		}
		if(array[middle] > query)
		{
			right = middle;
		}
		if(array[middle] == query)
		{
			index = middle;
			return index;
		}
	}
	return -1;
}


////////////////////////////////////////////////////////////////////////////////////////

int main(void)
{
	int rawdata[RAW_SIZE] = {5, 3, 2, 6, 4, 1, 3};
	int len = ARR_SIZE(rawdata);
	int array[MAX_SIZE];
	int i;
	int query;
	int index = -1;
	
	QuickSort(rawdata, 0, len-1);
	
	for(i=0; i<len; i++)
	{
		array[i+1] = rawdata[i];
	}
	
	while(1)
	{
		printf("Input the query: ");
		scanf("%d", &query);
		
		index = BiSearch(array, -1, MAX_SIZE-1, query);
		if(index>0 && index<MAX_SIZE-1)
		{
			printf("Index of query: %d\n", index);
		}
		else
		{
			printf("No match found.\n");
		}
	}
	return 0;
}