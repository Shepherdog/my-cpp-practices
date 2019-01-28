
#define ICMP_ECHO       8        //类型8，回显请求
#define ICMP_ECHOREPLY  0        //类型0，回显应答
#define ICMP_MIN        8

#define DEF_PACKET_SIZE  32
#define MAX_PACKET       1024

#define STATUS_FAILED  0xFFFF

#define xmalloc(s)  HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,(s))
#define xfree(p)    HeapFree (GetProcessHeap(),0,(p))


//IP报头
typedef struct iphdr
{
	unsigned int    h_len:4;           //length of the header
	unsigned int    version:4;         //Version of IP
	unsigned char   tos;               //Type of service
	unsigned short  total_len;         //total length of the packet
	unsigned short  ident;             //unique identifier
	unsigned short  frag_and_flags;    //flags
	unsigned char   ttl;
	unsigned char   proto;             //protocol (TCP, UDP etc)
	unsigned short  checksum;          //IP checksum
	unsigned int    sourceIP;
	unsigned int    destIP;
}IpHeader;

//ICMP报头
typedef struct _ihdr
{
	BYTE    i_type;
	BYTE    i_code;       //type sub code
	USHORT  i_cksum;
	USHORT  i_id;
	USHORT  i_seq;        //This is not the std header, but we reserve space for time
	ULONG   timestamp;
}IcmpHeader;


USHORT checksum(USHORT*, int);
void fill_icmp_data(char*, int);   //填充ICMP包
void decode_resp(char*, int, struct sockaddr_in *);   //解析应答包