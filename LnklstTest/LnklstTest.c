// LnklstTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "vld.h"  // for memory leak detection

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//extern  "C"
//{ 
	#include "zxtd_link_list.h"
//}

typedef struct  
{
	int x; 
	int y;
	char* des;
} Point;

//static LINK_LIST DECLARE_LIST(point_list);
static LINK_LIST point_list = DECLARE_LIST();

Point* create_point(int x, int y, const char* _des)
{
	Point* p = (Point*)_malloc(sizeof(Point));

	char* des = (char*)_malloc(strlen(_des)+1);
	strcpy(des, _des);

	p->x = x;
	p->y = y;
	p->des = des;

	return p;
}

void show_point(_data* _p)
{
	if (_p)
	{
		Point* p = (Point*)_p;
		printf("[x=%d, y=%d]: %s\n", p->x, p->y, p->des);
	}
	return;
}

void del_point(_data* _p)
{
	if (_p)
	{
		Point* p = (Point*)_p;
		free(p->des);
		free(p);	// pay attention to this free();
	}
	_p = NULL;
	return;
}

//-----------------------------------------------------------------------------Test begin
void _test_add_node()
{
	//lnklst_push_front(&point_list, create_point(0, 0, "point 4"));
	//lnklst_push_front(&point_list, create_point(1, 2, "point 5"));

	lnklst_push_back(&point_list, create_point(0, 0, "point 0"));
	lnklst_push_back(&point_list, create_point(1, 2, "point 1"));

	//lnklst_push_front(&point_list, create_point(3, 4, "point 6"));
	//lnklst_push_front(&point_list, create_point(5, 6, "point 7"));

	//lnklst_push_back(&point_list, create_point(3, 4, "point 2"));
	//lnklst_push_back(&point_list, create_point(5, 6, "point 3"));
}

void _test_show_one_node(unsigned int index)
{
	_data* p = lnklst_get_data_by_index(&point_list, index);

	if (p)
	{
		show_point(p);
	}
}

void _test_edit_one_node(unsigned int index)
{
	_data* p = lnklst_get_data_by_index(&point_list, index);

	if (p)
	{
		Point* ep = (Point*)p;
		strcpy(ep->des, "+edit");
	}
}

void _test_show_node_count()
{
	printf("%d elements in the list\n", lnklst_get_count(&point_list));
}

void _test_show_all_node()
{
	//assert(point_list.head != NULL);

	Point* p = NULL;

	LIST_ITERATE(point_list, val, 
		// your code here
		p = (Point*)val;
		if (p != NULL)
		{
			printf("[x=%d, y=%d]: %s\n", p->x, p->y, p->des);
		}
	);
}

void _test_remove_top_node()
{
	_data* p = lnklst_pop_front(&point_list);

	if (p)
	{
		printf("remove top:");
		show_point(p);
		del_point(p);	// remember to free the data
	}
}

void _test_remove_one_node(unsigned int index)
{
	lnklst_remove_node(&point_list, index, del_point);
}

void _test_is_empty()
{
	if (lnklst_is_empty(&point_list))
	{
		printf("the list is empty with head=%02X, tail=%02X\n", point_list.head, point_list.last);
	}
	else
	{
		printf("the list is not empty with head=%02X, tail=%02X\n", point_list.head, point_list.last);
	}
}

void _test_release_list()
{
	lnklst_clear_list(&point_list, del_point);
}

int main(int argc, char* argv[])
{
	_test_add_node();

	_test_remove_one_node(0);
	_test_remove_one_node(0);

	//_test_remove_top_node();
	//_test_remove_top_node();
	//_test_remove_top_node();
	//_test_remove_top_node();

	//_test_show_one_node(-1);
	//_test_show_one_node(0);
	//_test_show_one_node(1);
	//_test_show_one_node(2);
	//_test_show_one_node(3);
	//_test_show_one_node(4);

	//_test_release_list();
	//_test_add_node();

	//_test_edit_one_node(0);

	_test_is_empty();
	lnklst_push_back(&point_list, create_point(7, 8, "point 9"));
	_test_is_empty();

	_test_show_all_node();
	_test_show_node_count();

	_test_release_list();

	//printf("end test!\n");
	return 0;
}
