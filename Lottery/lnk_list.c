#include <stdio.h>
#include <stdlib.h>
#include "lnk_list.h"

#ifdef DEBUG
#include <assert.h>
#endif   /*DEBUG*/


BOOL Insert_Node(NODE** head, NODE** pivot, void* data)
{
   NODE* pNode = (NODE*)calloc(1, sizeof(NODE));
   if(pNode == NULL)
   {
      perror("Fatal Error");
      return FALSE;
   }

   pNode->data_area = data;
   pNode->next_node = NULL;

   if(*head == NULL)
   {
      *head = pNode;
   }
   else
   {
   	#ifdef DEBUG
   	  assert(*pivot!=NULL);
   	#endif   /*DEBUG*/
   	
      (*pivot)->next_node = pNode;
   }
   *pivot = pNode;

   return TRUE;
}

void Parse_Node(const NODE* node, void* parsefunc(void*))
{
   if(node != NULL)
   {
      if(node->data_area != NULL)
      {
         parsefunc(node->data_area);
      }
   }
}

void Parse_All(NODE* head, void* parsefunc(void*))
{
   NODE* node = head;
   NODE* ptr = NULL;
   
   while(node != NULL)
   {
   	ptr = node->next_node;
   	Parse_Node(node, parsefunc);
   	node = ptr;
  }
}

void Delete_Node(NODE* node, BOOL deldata_flag, void* delfunc(void*))
{
   /*delete the current node optionally*/
   if(deldata_flag && node->data_area!=NULL)
   {
   	delfunc(node->data_area);
  }
  #ifdef DEBUG
   printf("Release Node_%x\n", node);
  #endif   /*DEBUG*/
  free(node);
}

void Delete_All(NODE** head, BOOL deldata_flag, void* delfunc(void*))
{
   NODE* node = *head;
   NODE* ptr = NULL;
   
   while(node != NULL)
   {
   	ptr = node->next_node;
   	Delete_Node(node, deldata_flag, delfunc);
   	node = ptr;
  }
  *head = NULL;
}
