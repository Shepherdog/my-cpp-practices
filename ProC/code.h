
#define USR_LEN 20
#define PWD_LEN 40

#define MAX_STR 60
#define MAX_SQL 1024

#define DB_ERR  0
#define REC_END 1403

typedef struct
{
	char id[MAX_STR];
	char name[MAX_STR];
	char major[MAX_STR];
} CODE;

/*This line must be blank, or the C preprocessor will meet an fatal error*/
