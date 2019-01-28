
#define MAX_NODE 28   //Hash散列表中Slot的数量
#define MAX_WORD 70


typedef struct
{
	char value[16];
	struct ValueNode *next;
}ValueNode;

typedef struct
{
	char index;
	struct ValueNode *valuenode;
}HashNode;


HashNode hashnode[MAX_NODE];   //存储Hash散列表
char word[MAX_WORD][30];

int retrieve_data(void);
void create_hash(void);         //构造Hash散列表
int query_hash(char*, char*);   //查询Hash散列表