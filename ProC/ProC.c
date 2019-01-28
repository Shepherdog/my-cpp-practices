
/* Result Sets Interface */
#ifndef SQL_CRSR
#  define SQL_CRSR
  struct sql_cursor
  {
    unsigned int curocn;
    void *ptr1;
    void *ptr2;
    unsigned long magic;
  };
  typedef struct sql_cursor sql_cursor;
  typedef struct sql_cursor SQL_CURSOR;
#endif /* SQL_CRSR */

/* Thread Safety */
typedef void * sql_context;
typedef void * SQL_CONTEXT;

/* Object support */
struct sqltvn
{
  unsigned char *tvnvsn; 
  unsigned short tvnvsnl; 
  unsigned char *tvnnm;
  unsigned short tvnnml; 
  unsigned char *tvnsnm;
  unsigned short tvnsnml;
};
typedef struct sqltvn sqltvn;

struct sqladts
{
  unsigned int adtvsn; 
  unsigned short adtmode; 
  unsigned short adtnum;  
  sqltvn adttvn[1];       
};
typedef struct sqladts sqladts;

static struct sqladts sqladt = {
  1,1,0,
};

/* Binding to PL/SQL Records */
struct sqltdss
{
  unsigned int tdsvsn; 
  unsigned short tdsnum; 
  unsigned char *tdsval[1]; 
};
typedef struct sqltdss sqltdss;
static struct sqltdss sqltds =
{
  1,
  0,
};

/* File name & Package Name */
struct sqlcxp
{
  unsigned short fillen;
           char  filnam[8];
};
static const struct sqlcxp sqlfpn =
{
    7,
    "ProC.pc"
};


static unsigned long sqlctx = 9955;


static struct sqlexd {
   unsigned int   sqlvsn;
   unsigned int   arrsiz;
   unsigned int   iters;
   unsigned int   offset;
   unsigned short selerr;
   unsigned short sqlety;
   unsigned int   occurs;
      const short *cud;
   unsigned char  *sqlest;
      const char  *stmt;
   sqladts *sqladtp;
   sqltdss *sqltdsp;
            void  **sqphsv;
   unsigned int   *sqphsl;
            int   *sqphss;
            void  **sqpind;
            int   *sqpins;
   unsigned int   *sqparm;
   unsigned int   **sqparc;
   unsigned short  *sqpadto;
   unsigned short  *sqptdso;
            void  *sqhstv[4];
   unsigned int   sqhstl[4];
            int   sqhsts[4];
            void  *sqindv[4];
            int   sqinds[4];
   unsigned int   sqharm[4];
   unsigned int   *sqharc[4];
   unsigned short  sqadto[4];
   unsigned short  sqtdso[4];
} sqlstm = {10,4};

/* SQLLIB Prototypes */
extern void sqlcxt (void **, unsigned long *,
                    struct sqlexd *, const struct sqlcxp *);
extern void sqlcx2t(void **, unsigned long *,
                    struct sqlexd *, const struct sqlcxp *);
extern void sqlbuft(void **, char *);
extern void sqlgs2t(void **, char *);
extern void sqlorat(void **, unsigned long *, void *);

/* Forms Interface */
static const int IAPSUCC = 0;
static const int IAPFAIL = 1403;
static const int IAPFTL  = 535;
extern void sqliem(char *, int *);

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

/* cud (compilation unit data) array */
static const short sqlcud0[] =
{10,4130,0,0,0,
5,0,0,1,0,0,27,25,0,0,4,4,0,1,0,1,97,0,0,1,97,0,0,1,10,0,0,1,10,0,0,
36,0,0,2,0,0,30,40,0,0,0,0,0,1,0,
51,0,0,3,0,0,32,44,0,0,0,0,0,1,0,
66,0,0,4,0,0,17,68,0,0,1,1,0,1,0,1,97,0,0,
85,0,0,4,0,0,45,79,0,0,0,0,0,1,0,
100,0,0,4,0,0,13,89,0,0,3,0,0,1,0,2,97,0,0,2,97,0,0,2,97,0,0,
127,0,0,4,0,0,15,102,0,0,0,0,0,1,0,
};


#line 1 "ProC.pc"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "code.h"

#include <sqlca.h>
/*#include <sqlcpr.h>*/

/*EXEC SQL INCLUDE sqlca;*/
/*EXEC SQL INCLUDE sqlcpr;*/

/* EXEC SQL WHENEVER NOTFOUND CONTINUE; */ 
#line 13 "ProC.pc"

/* EXEC SQL WHENEVER SQLERROR CONTINUE; */ 
#line 14 "ProC.pc"


int db_connect(const char* usr, const char* pwd)
{
	char username[USR_LEN];
	char password[PWD_LEN];

	strcpy(username, usr);
	strcpy(password, pwd);

	/*Connect to database*/
	/* EXEC SQL CONNECT :username IDENTIFIED BY :password; */ 
#line 25 "ProC.pc"

{
#line 25 "ProC.pc"
 struct sqlexd sqlstm;
#line 25 "ProC.pc"
 sqlstm.sqlvsn = 10;
#line 25 "ProC.pc"
 sqlstm.arrsiz = 4;
#line 25 "ProC.pc"
 sqlstm.sqladtp = &sqladt;
#line 25 "ProC.pc"
 sqlstm.sqltdsp = &sqltds;
#line 25 "ProC.pc"
 sqlstm.iters = (unsigned int  )10;
#line 25 "ProC.pc"
 sqlstm.offset = (unsigned int  )5;
#line 25 "ProC.pc"
 sqlstm.cud = sqlcud0;
#line 25 "ProC.pc"
 sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 25 "ProC.pc"
 sqlstm.sqlety = (unsigned short)256;
#line 25 "ProC.pc"
 sqlstm.occurs = (unsigned int  )0;
#line 25 "ProC.pc"
 sqlstm.sqhstv[0] = (         void  *)username;
#line 25 "ProC.pc"
 sqlstm.sqhstl[0] = (unsigned int  )20;
#line 25 "ProC.pc"
 sqlstm.sqhsts[0] = (         int  )20;
#line 25 "ProC.pc"
 sqlstm.sqindv[0] = (         void  *)0;
#line 25 "ProC.pc"
 sqlstm.sqinds[0] = (         int  )0;
#line 25 "ProC.pc"
 sqlstm.sqharm[0] = (unsigned int  )0;
#line 25 "ProC.pc"
 sqlstm.sqadto[0] = (unsigned short )0;
#line 25 "ProC.pc"
 sqlstm.sqtdso[0] = (unsigned short )0;
#line 25 "ProC.pc"
 sqlstm.sqhstv[1] = (         void  *)password;
#line 25 "ProC.pc"
 sqlstm.sqhstl[1] = (unsigned int  )40;
#line 25 "ProC.pc"
 sqlstm.sqhsts[1] = (         int  )40;
#line 25 "ProC.pc"
 sqlstm.sqindv[1] = (         void  *)0;
#line 25 "ProC.pc"
 sqlstm.sqinds[1] = (         int  )0;
#line 25 "ProC.pc"
 sqlstm.sqharm[1] = (unsigned int  )0;
#line 25 "ProC.pc"
 sqlstm.sqadto[1] = (unsigned short )0;
#line 25 "ProC.pc"
 sqlstm.sqtdso[1] = (unsigned short )0;
#line 25 "ProC.pc"
 sqlstm.sqphsv = sqlstm.sqhstv;
#line 25 "ProC.pc"
 sqlstm.sqphsl = sqlstm.sqhstl;
#line 25 "ProC.pc"
 sqlstm.sqphss = sqlstm.sqhsts;
#line 25 "ProC.pc"
 sqlstm.sqpind = sqlstm.sqindv;
#line 25 "ProC.pc"
 sqlstm.sqpins = sqlstm.sqinds;
#line 25 "ProC.pc"
 sqlstm.sqparm = sqlstm.sqharm;
#line 25 "ProC.pc"
 sqlstm.sqparc = sqlstm.sqharc;
#line 25 "ProC.pc"
 sqlstm.sqpadto = sqlstm.sqadto;
#line 25 "ProC.pc"
 sqlstm.sqptdso = sqlstm.sqtdso;
#line 25 "ProC.pc"
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 25 "ProC.pc"
}

#line 25 "ProC.pc"

	if(sqlca.sqlcode != DB_ERR)
	{
		printf("\nERROR-%s\n", sqlca.sqlerrm.sqlerrmc);
		/*exit(-1);*/
		return 0;
	}

	return 1;
}

int db_commit(int mode)
{
	if(mode == 1)
	{
		/* EXEC SQL COMMIT WORK RELEASE; */ 
#line 40 "ProC.pc"

{
#line 40 "ProC.pc"
  struct sqlexd sqlstm;
#line 40 "ProC.pc"
  sqlstm.sqlvsn = 10;
#line 40 "ProC.pc"
  sqlstm.arrsiz = 4;
#line 40 "ProC.pc"
  sqlstm.sqladtp = &sqladt;
#line 40 "ProC.pc"
  sqlstm.sqltdsp = &sqltds;
#line 40 "ProC.pc"
  sqlstm.iters = (unsigned int  )1;
#line 40 "ProC.pc"
  sqlstm.offset = (unsigned int  )36;
#line 40 "ProC.pc"
  sqlstm.cud = sqlcud0;
#line 40 "ProC.pc"
  sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 40 "ProC.pc"
  sqlstm.sqlety = (unsigned short)256;
#line 40 "ProC.pc"
  sqlstm.occurs = (unsigned int  )0;
#line 40 "ProC.pc"
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 40 "ProC.pc"
}

#line 40 "ProC.pc"

	}
	if(mode == 0)
	{
		/* EXEC SQL ROLLBACK WORK RELEASE; */ 
#line 44 "ProC.pc"

{
#line 44 "ProC.pc"
  struct sqlexd sqlstm;
#line 44 "ProC.pc"
  sqlstm.sqlvsn = 10;
#line 44 "ProC.pc"
  sqlstm.arrsiz = 4;
#line 44 "ProC.pc"
  sqlstm.sqladtp = &sqladt;
#line 44 "ProC.pc"
  sqlstm.sqltdsp = &sqltds;
#line 44 "ProC.pc"
  sqlstm.iters = (unsigned int  )1;
#line 44 "ProC.pc"
  sqlstm.offset = (unsigned int  )51;
#line 44 "ProC.pc"
  sqlstm.cud = sqlcud0;
#line 44 "ProC.pc"
  sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 44 "ProC.pc"
  sqlstm.sqlety = (unsigned short)256;
#line 44 "ProC.pc"
  sqlstm.occurs = (unsigned int  )0;
#line 44 "ProC.pc"
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 44 "ProC.pc"
}

#line 44 "ProC.pc"

	}

	if(sqlca.sqlcode != DB_ERR)
	{
		printf("\nERROR-%s\n", sqlca.sqlerrm.sqlerrmc);
		return 0;
	}

	return 1;
}

int get_result()
{
	char s_sqls[MAX_SQL];
	CODE* t_code = (CODE*)calloc(1, sizeof(CODE));

	memset(s_sqls, '\0', MAX_SQL);
	sprintf(s_sqls, "select STUDENT_ID, \
			                    NAME, \
			                    MAJOR \
			             from scott.student");

	/*printf("%s\n", s_sqls);*/
	/* EXEC SQL PREPARE STATEMENT FROM :s_sqls; */ 
#line 68 "ProC.pc"

{
#line 68 "ProC.pc"
 struct sqlexd sqlstm;
#line 68 "ProC.pc"
 sqlstm.sqlvsn = 10;
#line 68 "ProC.pc"
 sqlstm.arrsiz = 4;
#line 68 "ProC.pc"
 sqlstm.sqladtp = &sqladt;
#line 68 "ProC.pc"
 sqlstm.sqltdsp = &sqltds;
#line 68 "ProC.pc"
 sqlstm.stmt = "";
#line 68 "ProC.pc"
 sqlstm.iters = (unsigned int  )1;
#line 68 "ProC.pc"
 sqlstm.offset = (unsigned int  )66;
#line 68 "ProC.pc"
 sqlstm.cud = sqlcud0;
#line 68 "ProC.pc"
 sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 68 "ProC.pc"
 sqlstm.sqlety = (unsigned short)256;
#line 68 "ProC.pc"
 sqlstm.occurs = (unsigned int  )0;
#line 68 "ProC.pc"
 sqlstm.sqhstv[0] = (         void  *)s_sqls;
#line 68 "ProC.pc"
 sqlstm.sqhstl[0] = (unsigned int  )1024;
#line 68 "ProC.pc"
 sqlstm.sqhsts[0] = (         int  )0;
#line 68 "ProC.pc"
 sqlstm.sqindv[0] = (         void  *)0;
#line 68 "ProC.pc"
 sqlstm.sqinds[0] = (         int  )0;
#line 68 "ProC.pc"
 sqlstm.sqharm[0] = (unsigned int  )0;
#line 68 "ProC.pc"
 sqlstm.sqadto[0] = (unsigned short )0;
#line 68 "ProC.pc"
 sqlstm.sqtdso[0] = (unsigned short )0;
#line 68 "ProC.pc"
 sqlstm.sqphsv = sqlstm.sqhstv;
#line 68 "ProC.pc"
 sqlstm.sqphsl = sqlstm.sqhstl;
#line 68 "ProC.pc"
 sqlstm.sqphss = sqlstm.sqhsts;
#line 68 "ProC.pc"
 sqlstm.sqpind = sqlstm.sqindv;
#line 68 "ProC.pc"
 sqlstm.sqpins = sqlstm.sqinds;
#line 68 "ProC.pc"
 sqlstm.sqparm = sqlstm.sqharm;
#line 68 "ProC.pc"
 sqlstm.sqparc = sqlstm.sqharc;
#line 68 "ProC.pc"
 sqlstm.sqpadto = sqlstm.sqadto;
#line 68 "ProC.pc"
 sqlstm.sqptdso = sqlstm.sqtdso;
#line 68 "ProC.pc"
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 68 "ProC.pc"
}

#line 68 "ProC.pc"


	/*Allocate cursor*/
	/* EXEC SQL DECLARE cursor CURSOR for STATEMENT; */ 
#line 71 "ProC.pc"

	if(sqlca.sqlcode != DB_ERR)
	{
		printf("\nERROR-%s\n", sqlca.sqlerrm.sqlerrmc);
		return 0;
	}

	/*Open cursor*/
	/* EXEC SQL OPEN cursor; */ 
#line 79 "ProC.pc"

{
#line 79 "ProC.pc"
 struct sqlexd sqlstm;
#line 79 "ProC.pc"
 sqlstm.sqlvsn = 10;
#line 79 "ProC.pc"
 sqlstm.arrsiz = 4;
#line 79 "ProC.pc"
 sqlstm.sqladtp = &sqladt;
#line 79 "ProC.pc"
 sqlstm.sqltdsp = &sqltds;
#line 79 "ProC.pc"
 sqlstm.stmt = "";
#line 79 "ProC.pc"
 sqlstm.iters = (unsigned int  )1;
#line 79 "ProC.pc"
 sqlstm.offset = (unsigned int  )85;
#line 79 "ProC.pc"
 sqlstm.selerr = (unsigned short)1;
#line 79 "ProC.pc"
 sqlstm.cud = sqlcud0;
#line 79 "ProC.pc"
 sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 79 "ProC.pc"
 sqlstm.sqlety = (unsigned short)256;
#line 79 "ProC.pc"
 sqlstm.occurs = (unsigned int  )0;
#line 79 "ProC.pc"
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 79 "ProC.pc"
}

#line 79 "ProC.pc"

	if(sqlca.sqlcode != DB_ERR)
	{
		printf("\nERROR-%s\n", sqlca.sqlerrm.sqlerrmc);
		return 0;
	}

	/*Fetch data*/
	while(1)
	{
		/* EXEC SQL FETCH cursor INTO :t_code->id, \
				                       :t_code->name, \
				                       :t_code->major; */ 
#line 91 "ProC.pc"

{
#line 89 "ProC.pc"
  struct sqlexd sqlstm;
#line 89 "ProC.pc"
  sqlstm.sqlvsn = 10;
#line 89 "ProC.pc"
  sqlstm.arrsiz = 4;
#line 89 "ProC.pc"
  sqlstm.sqladtp = &sqladt;
#line 89 "ProC.pc"
  sqlstm.sqltdsp = &sqltds;
#line 89 "ProC.pc"
  sqlstm.iters = (unsigned int  )1;
#line 89 "ProC.pc"
  sqlstm.offset = (unsigned int  )100;
#line 89 "ProC.pc"
  sqlstm.cud = sqlcud0;
#line 89 "ProC.pc"
  sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 89 "ProC.pc"
  sqlstm.sqlety = (unsigned short)256;
#line 89 "ProC.pc"
  sqlstm.occurs = (unsigned int  )0;
#line 89 "ProC.pc"
  sqlstm.sqhstv[0] = (         void  *)(t_code->id);
#line 89 "ProC.pc"
  sqlstm.sqhstl[0] = (unsigned int  )60;
#line 89 "ProC.pc"
  sqlstm.sqhsts[0] = (         int  )0;
#line 89 "ProC.pc"
  sqlstm.sqindv[0] = (         void  *)0;
#line 89 "ProC.pc"
  sqlstm.sqinds[0] = (         int  )0;
#line 89 "ProC.pc"
  sqlstm.sqharm[0] = (unsigned int  )0;
#line 89 "ProC.pc"
  sqlstm.sqadto[0] = (unsigned short )0;
#line 89 "ProC.pc"
  sqlstm.sqtdso[0] = (unsigned short )0;
#line 89 "ProC.pc"
  sqlstm.sqhstv[1] = (         void  *)(t_code->name);
#line 89 "ProC.pc"
  sqlstm.sqhstl[1] = (unsigned int  )60;
#line 89 "ProC.pc"
  sqlstm.sqhsts[1] = (         int  )0;
#line 89 "ProC.pc"
  sqlstm.sqindv[1] = (         void  *)0;
#line 89 "ProC.pc"
  sqlstm.sqinds[1] = (         int  )0;
#line 89 "ProC.pc"
  sqlstm.sqharm[1] = (unsigned int  )0;
#line 89 "ProC.pc"
  sqlstm.sqadto[1] = (unsigned short )0;
#line 89 "ProC.pc"
  sqlstm.sqtdso[1] = (unsigned short )0;
#line 89 "ProC.pc"
  sqlstm.sqhstv[2] = (         void  *)(t_code->major);
#line 89 "ProC.pc"
  sqlstm.sqhstl[2] = (unsigned int  )60;
#line 89 "ProC.pc"
  sqlstm.sqhsts[2] = (         int  )0;
#line 89 "ProC.pc"
  sqlstm.sqindv[2] = (         void  *)0;
#line 89 "ProC.pc"
  sqlstm.sqinds[2] = (         int  )0;
#line 89 "ProC.pc"
  sqlstm.sqharm[2] = (unsigned int  )0;
#line 89 "ProC.pc"
  sqlstm.sqadto[2] = (unsigned short )0;
#line 89 "ProC.pc"
  sqlstm.sqtdso[2] = (unsigned short )0;
#line 89 "ProC.pc"
  sqlstm.sqphsv = sqlstm.sqhstv;
#line 89 "ProC.pc"
  sqlstm.sqphsl = sqlstm.sqhstl;
#line 89 "ProC.pc"
  sqlstm.sqphss = sqlstm.sqhsts;
#line 89 "ProC.pc"
  sqlstm.sqpind = sqlstm.sqindv;
#line 89 "ProC.pc"
  sqlstm.sqpins = sqlstm.sqinds;
#line 89 "ProC.pc"
  sqlstm.sqparm = sqlstm.sqharm;
#line 89 "ProC.pc"
  sqlstm.sqparc = sqlstm.sqharc;
#line 89 "ProC.pc"
  sqlstm.sqpadto = sqlstm.sqadto;
#line 89 "ProC.pc"
  sqlstm.sqptdso = sqlstm.sqtdso;
#line 89 "ProC.pc"
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 89 "ProC.pc"
}

#line 91 "ProC.pc"


		if(sqlca.sqlcode == REC_END)
		{
			break;
		}

		printf("ID:%s NAME:%s MAJOR:%s", t_code->id, t_code->name, t_code->major);
	}

	/*Close cursor*/
	/* EXEC SQL CLOSE cursor; */ 
#line 102 "ProC.pc"

{
#line 102 "ProC.pc"
 struct sqlexd sqlstm;
#line 102 "ProC.pc"
 sqlstm.sqlvsn = 10;
#line 102 "ProC.pc"
 sqlstm.arrsiz = 4;
#line 102 "ProC.pc"
 sqlstm.sqladtp = &sqladt;
#line 102 "ProC.pc"
 sqlstm.sqltdsp = &sqltds;
#line 102 "ProC.pc"
 sqlstm.iters = (unsigned int  )1;
#line 102 "ProC.pc"
 sqlstm.offset = (unsigned int  )127;
#line 102 "ProC.pc"
 sqlstm.cud = sqlcud0;
#line 102 "ProC.pc"
 sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 102 "ProC.pc"
 sqlstm.sqlety = (unsigned short)256;
#line 102 "ProC.pc"
 sqlstm.occurs = (unsigned int  )0;
#line 102 "ProC.pc"
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 102 "ProC.pc"
}

#line 102 "ProC.pc"

	if(sqlca.sqlcode != DB_ERR)
	{
		printf("\nERROR-%s\n", sqlca.sqlerrm.sqlerrmc);
		return 0;
	}

	return 1;
}

int main(void)
{
	char username[USR_LEN];
	char password[PWD_LEN];

	int connected;

	/*printf("\n---------[TEST MODE V3.0]---------\n\n");*/

	strcpy(username, "system");
	strcpy(password, "manager");

	connected = db_connect(username, password);
	if(connected)
	{
		printf("\n用户[%s]连接数据库成功.\n", username);
	}
	else
	{
	  printf("\n用户[%s]连接数据库失败.\n", username);
	  return 0;
	}

	get_result();

	return 1;
}
