
#define xmalloc(s)   HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, (s))
#define xfree(p)     HeapFree(GetProcessHeap(), 0, (p))

typedef struct 
{
	unsigned char ver_hlen;
	unsigned char tos;
	unsigned short total_len;
	unsigned short ident;
	unsigned short frag_and_flags;
	unsigned char ttl;
	unsigned char proto;
	unsigned short checksum;
	unsigned int sourceip;
	unsigned int destinip;
}IPHdr;