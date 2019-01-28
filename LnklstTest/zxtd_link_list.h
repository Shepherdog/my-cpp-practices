/*
 * Linklist Algorithm Template for MTK
 *
 * A "template" for a single linked list module without an extra level
 * of indirection, implemented in a typesafe way.
 *
 * author: alex kon [6226830@163.com]
 * date: 10-14-2011
 */
 
#ifndef _LNK_LIST_H_
#define _LNK_LIST_H_

#define _malloc	malloc	// MTK's malloc()
#define _free 	free	// MTK's free()

/*Create a new empty list*/
#define DECLARE_LIST()		{NULL, NULL, 0}
//#define DECLARE_LIST(s)		s ={NULL, NULL, 0}

#define _data	void	// common data type

#define USE_BOOL_DEF	// use our BOOL definition if not native supported
#if defined(USE_BOOL_DEF)
	typedef enum {FALSE, TRUE} BOOL;
#endif   /*USE_BOOL_DEF*/

/* This is a node in the linked list. Note that if type is a struct
   and not a pointer, we get the same effect as if declaring the same
   struct with the next pointer added. */
typedef struct node_item
{
	_data* data_area;
	struct node_item* next_node;
} ITEM;

/* This keeps track of a particular list by its first and last
   node, enabling quick adding to the beginning and end. */
typedef struct link_list
{
	ITEM* head;
	ITEM* last;
	unsigned int count;
} LINK_LIST;


/* for ANSI_C */
/*-------------------------------------------------------------------------------*/
// Adds a value to the end of the list
BOOL lnklst_push_back(LINK_LIST* lnklist, const _data* dat);

// Adds a value to the front of the list
BOOL lnklst_push_front(LINK_LIST* lnklist, const _data* dat);

// Retrieves a pointer to data at position of given index[0..n]
_data* lnklst_get_data_by_index(const LINK_LIST* lnklist, unsigned int index);

// Get the total number of elements
unsigned int lnklst_get_count(const LINK_LIST* lnklist);

// Returns nonzero iff list is empty (contains no elements)
BOOL lnklst_is_empty(const LINK_LIST* lnklist);

// Gets a pointer to the data at the beginning of the list 
// and then removes it from the list
// NOTE: the data should be released by yourself
_data* lnklst_pop_front(LINK_LIST* lnklist);

// TODO:
// Gets a pointer to the data at the end of the list
//_data* lnklst_pop_back(LINK_LIST* lnklist);

// Removes the value at the position of given index[0..n]
// del_func() will be called to release the node's data
// NOTE: when removing more than one node, be cautious to re-calculate a new index!
void lnklst_remove_node(LINK_LIST* lnklist, unsigned int index, void del_func(_data*));

// Removes all elements of list, call this when done with it
// del_func() will be called to release each node's data
void lnklst_clear_list(LINK_LIST* lnklist, void del_func(_data*));

/* See the LIST_ITERATE macro to do typical iteration */

// iterate all elements in the list
#define LIST_ITERATE(lnklist, data, body) \
{ \
	ITEM* node = lnklist.head; \
	_data* data = NULL; \
	for( ; node != NULL; node = node->next_node) \
	{ \
		data = node->data_area; \
		body; \
	} \
}
/*-------------------------------------------------------------------------------*/

#endif   /*_LNK_LIST_H_*/
