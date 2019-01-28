/* add your platform includes here */
#include <stdio.h>

#include "zxtd_link_list.h"

#ifdef _DEBUG
	#include <assert.h>
#endif   /*_DEBUG*/


BOOL lnklst_push_back(LINK_LIST* lnklist, const _data* dat)
{
	ITEM* pNode = (ITEM*)_malloc(sizeof(ITEM));
	if (pNode == NULL)
	{
		//perror("Fatal Error");
		return FALSE;
	}
	
	pNode->data_area = dat;
	pNode->next_node = NULL;
	
	if (lnklist->last == NULL)
	{
		lnklist->head = pNode;
	}
	else
	{
		// insert to end
		lnklist->last->next_node = pNode;
	}
	lnklist->last = pNode;
	
	lnklist->count++;
	return TRUE;
}

BOOL lnklst_push_front(LINK_LIST* lnklist, const _data* dat)
{
	ITEM* pNode = (ITEM*)_malloc(sizeof(ITEM));
	if (pNode == NULL)
	{
		return FALSE;
	}
	
	pNode->data_area = dat;
	pNode->next_node = lnklist->head;	// insert to front
	
	lnklist->head = pNode;
	
	if (lnklist->last == NULL)
	{
		lnklist->last = pNode;
	}
	
	lnklist->count++;
	return TRUE;
}

// for inner use
static ITEM* lnklst_get_node_by_index(LINK_LIST* lnklist, unsigned int index)
{
	ITEM* node = lnklist->head;
	
	if ((node != NULL) 
		&& (index >= 0) && (index < lnklist->count))	// check the index's boundary
	{
		while ((node->next_node != NULL) && (index--))
		{
			node = node->next_node;
		}
		
		return node;
	}

	return NULL;
}

// for inner use
static _data* lnklst_get_node_data(const ITEM* node)
{
	if (node != NULL)
	{
		return node->data_area;
	}
	return NULL;
}

_data* lnklst_pop_front(LINK_LIST* lnklist)
{
	ITEM* node = lnklist->head;
	_data* data = NULL;
	
	if (node != NULL)	/*found the node*/
	{
		/*set new head*/
		lnklist->head = node->next_node;
		
		/*get node's data*/
		data = node->data_area;
		
		/*delete the current node*/
		_free(node);
		node = NULL;
		
		lnklist->count--;
		return data;
	}
	
	return NULL;
}

_data* lnklst_get_data_by_index(const LINK_LIST* lnklist, unsigned int index)
{
	ITEM* node = lnklst_get_node_by_index(lnklist, index);
	
	return lnklst_get_node_data(node);
}

unsigned int lnklst_get_count(const LINK_LIST* lnklist)
{
	return lnklist->count;
}

BOOL lnklst_is_empty(const LINK_LIST* lnklist)
{
	return (lnklist->head == NULL);
}

void lnklst_remove_node(LINK_LIST* lnklist, unsigned int index, void del_func(_data*))
{
	ITEM** head = &(lnklist->head);
	ITEM** last = &(lnklist->last);
	
	ITEM* node = NULL;
	ITEM* prev = NULL;
	
	if ((*head == NULL)
		|| (index < 0) || (index > lnklist->count-1))	// index out of bounds
	{
		return;
	}
	
	if (index == 0)	/*front node*/
	{
		node = *head;
		/*set new head*/
		*head = node->next_node;

		if(node == *last)	/*has only one element*/
		{
			*last = NULL;
		}
	}
	else
	{
		prev = lnklst_get_node_by_index(lnklist, index-1);
		node = prev->next_node;
		
		if (node == *last)	/*tail node*/
		{
			/*set new tail*/
			*last = prev;
			prev->next_node = NULL;
		}
		else	/*middle node*/
		{
			prev->next_node = node->next_node;
		}
	}
	
	if (node != NULL)	/*found the node*/
	{
		/*delete node's data*/
		del_func(node->data_area);
		
		/*delete the current node*/
		_free(node);
		node = NULL;

		lnklist->count--;
	}
}

void lnklst_clear_list(LINK_LIST* lnklist, void del_func(_data*))
{
	ITEM* node = lnklist->head;
	ITEM* ptr = NULL;
	
	for( ; node != NULL; node = ptr)
	{
		ptr = node->next_node;
		
		if (node->data_area != NULL)
		{
			del_func(node->data_area);
		}
	#ifdef _DEBUG
		printf("Release Node_%x\n", node);
	#endif   /*_DEBUG*/
		_free(node);
	}

	// reset the list
	lnklist->head = NULL;
	lnklist->last = NULL;
	lnklist->count = 0;
}
