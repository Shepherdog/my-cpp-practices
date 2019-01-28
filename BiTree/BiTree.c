
#include <stdio.h>
#include <stdlib.h>
#include "bitree.h"


int createbitree(bitree *T)
{
	int e;
	scanf("%d ", &e);
	if(e == 0)
	{
		*T = NULL;
	}
	else
	{
		if(! ((*T)=(bitree)calloc(1, sizeof(bnode))))
		{
			return 0;
		}
		(*T)->data = e;
		createbitree(&((*T)->lchild));
		createbitree(&((*T)->rchild));
	}
	return 1;
}

void disposenode(bnode* p)
{
	printf("%d ", p->data);
}

void pretraver(bitree T, void(*Visit)(bnode* p))
{
	if(T)
	{
		Visit(T);
		pretraver(T->lchild, Visit);
		pretraver(T->rchild, Visit);
	}
}

void intraver(bitree T, void(*Visit)(bnode* p))
{
	if(T)
	{
		intraver(T->lchild, Visit);
		Visit(T);
		intraver(T->rchild, Visit);
	}
}

void posttraver(bitree T, void(*Visit)(bnode* p))
{
	if(T)
	{
		posttraver(T->lchild, Visit);
		posttraver(T->rchild, Visit);
		Visit(T);
	}
}

void insertnode(bitree T, int e)
{
	int found = 0;
	bnode *q, *p=T;
	while((!found) && (p!=NULL))
	{
		q = p;
		if(e == p->data)
		{
			found = 1;
		}
		else
			if(e < p->data)
			{
				p = p->lchild;
			}
			else
			{
				p = p->rchild;
			}
	}
	if(!found)
	{
		p = (bnode*)calloc(1, sizeof(bnode));
		p->lchild = NULL;
		p->rchild = NULL;
		p->data = e;
		if(T)
		{
			if(e < q->data)
			{
				q->lchild = p;
			}
			else
			{
				q->rchild = p;
			}
		}
		else
		{
			T = p;
		}
	}
}

void deletenode(bitree T, int e)
{
	bnode* p = T;
	int found = 0;
	int locate;
	while((!found) && (p!=NULL))
	{
		if((e==p->lchild->data) || (e==p->rchild->data))
		{
			found = 1;
			if(e == p->lchild->data)
			{
				locate = 1;
			}
			if(e == p->rchild->data)
			{
				locate = 2;
			}
		}
		else
			if(e < p->data)
			{
				p = p->lchild;
			}
			else
			{
				p = p->rchild;
			}
	}
	if(found)
	{
		if(locate == 1)
		{
			if(p->lchild->lchild != NULL)
			{
				p->lchild = p->lchild->lchild;
			}
			else
			{
				p->lchild = p->lchild->rchild;
			}
		}
		if(locate == 2)
		{
			if(p->rchild->lchild != NULL)
			{
				p->rchild = p->rchild->lchild;
			}
			else
			{
				p->rchild = p->rchild->rchild;
			}
		}
	}
	else
	{
#ifdef DEBUG
		printf("No match found.");
#endif
	}
}


////////////////////////////////////////////////////////////////////////////////////////

void main()
{
	bitree t;
	printf("Input bitree's nodes:\n");
	if(createbitree(&t))
	{
		printf("\nOutput bitree's nodes:");
		//pretraver1(t, printnode);
		//insertnode(t, 80);
		//deletenode(t, 5);
		printf("\nPre-Traver:\n");
		pretraver(t, disposenode);
		printf("\nInt-Traver:\n");
		intraver(t, disposenode);
		printf("\nPos-Traver:\n");
		posttraver(t, disposenode);
	}
	else
	{
		printf("Failed to build.");
	}
}