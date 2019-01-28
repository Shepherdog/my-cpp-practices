/*
 * 二叉树结构
 * */
typedef struct node
{
   int data;
   struct node *lchild, *rchild;
}
bnode, *bitree;


int createbitree(bitree);
void disposenode(bnode);          //处理节点
void pretraver(bitree, void*);    //前序遍历
void intraver(bitree, void*);     //中序遍历
void posttraver(bitree, void*);   //后序遍历
void insertnode(bitree, int);     //插入节点
void deletenode(bitree, int);     //删除节点
