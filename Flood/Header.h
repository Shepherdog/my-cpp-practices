
/***************************************************************************************
网络上发送数据包的攻击有多种(如ICMP_FLOOD, 碎片攻击等)其中有一种就是利用TCP协议三次握手
的攻击(SYN_FLOOD)。

TCP连接的三次握手:
1.现在有A,B两台机器，其中B是SERVER，A是CLIENT。
2.首先A发送送一个带有SYN标记(带起始序列号)的数据报给B。
3.然后B接收，然后发送一个ACK+SYN(带B机的起始序列号和A的确认号)给A。
4.最后A再发送一个带序列号和确认号的数据报给B。
5.此时连接建立完成。

利用这个原理，如果A机在第一步伪装大量不存在的机器，给B发送大量的SYN包，那么B会以为有很
多合法的机器请求连接，然后一一回应。然后等待第三次确认建立连接。那么大量等待连接的请求
被保留在栈中。一般服务器等待2分钟还没等到第三次握手，那么就会从等待连接的栈中删除连接
请求。如果A的SYN发送得足够快，合法用户连接不上，那么服务器也会花费大量的资源来维护栈。
从而照成D.o.S攻击。通过RAW_SOCKET，就可以伪造IP和TCP头部，发虚假源地址的SYN请求。
***************************************************************************************/

//定义IP首部
typedef struct ip_head
{
	unsigned char   h_verlen;         //4位首部长度,4位IP版本号
	unsigned char   tos;              //8位服务类型TOS
	unsigned short  total_len;        //16位总长度(字节)
	unsigned short  ident;            //16位标识
	unsigned short  frag_and_flags;   //3位标志位(如SYN,ACK等)
	unsigned char   ttl;              //8位生存时间 TTL
	unsigned char   proto;            //8位协议(如ICMP，TCP等)
	unsigned short  checksum;         //16位IP首部校验和
	unsigned int    sourceIP;         //32位源IP地址
	unsigned int    destIP;           //32位目的IP地址
}IPHEADER;

//定义TCP首部
typedef struct tcp_head
{
	USHORT        th_sport;     //16位源端口
	USHORT        th_dport;     //16位目的端口
	unsigned int  th_seq;       //32位序列号
	unsigned int  th_ack;       //32位确认号
	unsigned char th_lenres;    //4位首部长度/6位保留字
	unsigned char th_flag;      //6位标志位
	USHORT        th_win;       //16位窗口大小
	USHORT        th_sum;       //16位校验和
	USHORT        th_urp;       //16位紧急数据偏移量
}TCPHEADER;

//定义TCP伪首部
typedef struct tsd_head
{
	unsigned long  saddr;      //源地址
	unsigned long  daddr;      //目的地址
	char           mbz;
	char           ptcl;       //协议类型
	unsigned short tcpl;       //TCP长度
}PSDHEADER;