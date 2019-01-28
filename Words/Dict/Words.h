
#define MAX_NODE 28   //Hashɢ�б���Slot������
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


HashNode hashnode[MAX_NODE];   //�洢Hashɢ�б�
char word[MAX_WORD][30];

int retrieve_data(void);
void create_hash(void);         //����Hashɢ�б�
int query_hash(char*, char*);   //��ѯHashɢ�б�