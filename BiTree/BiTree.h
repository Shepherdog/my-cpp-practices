/*
 * �������ṹ
 * */
typedef struct node
{
   int data;
   struct node *lchild, *rchild;
}
bnode, *bitree;


int createbitree(bitree);
void disposenode(bnode);          //����ڵ�
void pretraver(bitree, void*);    //ǰ�����
void intraver(bitree, void*);     //�������
void posttraver(bitree, void*);   //�������
void insertnode(bitree, int);     //����ڵ�
void deletenode(bitree, int);     //ɾ���ڵ�
