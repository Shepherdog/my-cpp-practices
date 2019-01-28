#ifndef _LNK_LIST_H_
#define _LNK_LIST_H_

#include "def_type.h"

typedef struct
{
   void* data_area;
   struct NODE* next_node;
}NODE;

/*------------------------------------------------------------*/
BOOL Insert_Node(NODE** head, NODE** pivot, void* data);

void Parse_Node(const NODE* node, void* parsefunc(void*));

void Parse_All(NODE* head, void* parsefunc(void*));

void Delete_Node(NODE* node, BOOL deldata_flag, void* delfunc(void*));

void Delete_All(NODE** head, BOOL deldata_flag, void* delfunc(void*));
/*------------------------------------------------------------*/

#endif   /*_LNK_LIST_H_*/
