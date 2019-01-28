
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

#pragma comment(lib, "WS2_32.lib")


USHORT checksum(USHORT* buffer, int size)
{
	unsigned long cksum = 0;
	while(size > 1)
	{
		cksum += *buffer++;
		size -= sizeof(USHORT);
	}
	if(size)
	{
		cksum += *(UCHAR*)buffer;
	}
	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >> 16);
	return (USHORT)(~cksum);
}

void fill_icmp_data(char* icmp_data, int datasize)
{
	IcmpHeader* icmp_hdr;
	char* datapart;
	
	icmp_hdr = (IcmpHeader*)icmp_data;
	icmp_hdr->i_type = ICMP_ECHO;
	icmp_hdr->i_code = 0;   //回显请求应答包的代码字段都为0
	icmp_hdr->i_id = (USHORT)GetCurrentProcessId();
	icmp_hdr->i_cksum = 0;
	icmp_hdr->i_seq = 0;
	
	datapart = icmp_data + sizeof(IcmpHeader);   //Place some junk in the buffer
	memset(&datapart, 'E', datasize-sizeof(IcmpHeader));
}

void decode_resp(char* buf, int bytes, struct sockaddr_in *from)
{
	IpHeader* iphdr;
	IcmpHeader* icmphdr;
	unsigned short iphdrlen;
	
	iphdr = (IpHeader*)buf;
	iphdrlen = iphdr->h_len * 4;   //number of 32-bit words *4 = bytes
	if(bytes < iphdrlen+ICMP_MIN)
	{
		//接收到的数据包太小
		printf("Too few bytes from %s\n", inet_ntoa(from->sin_addr));
	}
	
	icmphdr = (IcmpHeader*)(buf+iphdrlen);
	if(icmphdr->i_type != ICMP_ECHOREPLY)
	{
		//接收到未应答的ICMP包
		fprintf(stderr, "non-echo type %d recvd\n", icmphdr->i_type);
		return;
	}
	
	if(icmphdr->i_id != (USHORT)GetCurrentProcessId())
	{
		//其它的ICMP包
		fprintf(stderr, "someone else's packet!\n");
		return ;
	}
	
	//打印接收到的ICMP应答包信息
	printf("%d bytes from %s:", bytes, inet_ntoa(from->sin_addr));
	printf(" icmp_seq = %d. ", icmphdr->i_seq);
	printf(" time: %d ms ", GetTickCount()-icmphdr->timestamp);
	printf("\n");
}

void Usage(char* progname)
{
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "%s <host> [data_size]\n", progname);
	fprintf(stderr, "datasize can be up to 1Kb\n");
	ExitProcess(STATUS_FAILED);
}


int main(int argc, char** argv)
{
	WSADATA wsaData;
	SOCKET sockRaw;
	struct sockaddr_in from, dest;
	struct hostent *hp;
	int datasize;
	int fromlen = sizeof(from);
	int timeout = 1000;
	int bwrote, bread;
	char* dest_ip;
	char* icmp_data;
	char* recvbuf;
	unsigned int addr = 0;
	USHORT seq_no = 0;
	
	if(WSAStartup(MAKEWORD(2,1), &wsaData) != 0)
	{
		fprintf(stderr, "WSAStartup failed: %d\n", GetLastError());
		ExitProcess(STATUS_FAILED);
	}
	if(argc < 2)
	{
		Usage(argv[0]);
	}
	
	sockRaw = WSASocket(AF_INET, SOCK_RAW, IPPROTO_ICMP, NULL, 0, 0);
	if(sockRaw == INVALID_SOCKET)
	{
		fprintf(stderr, "WSASocket() failed: %d\n", WSAGetLastError());
		ExitProcess(STATUS_FAILED);
	}
	
	//设置套接口的接收超时
	bread = setsockopt(sockRaw, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
	if(bread == SOCKET_ERROR)
	{
		fprintf(stderr, "failed to set recv timeout: %d\n", WSAGetLastError());
		ExitProcess(STATUS_FAILED);
	}
	
	//设置套接口的发送超时
	bread = setsockopt(sockRaw, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, sizeof(timeout));
	if(bread == SOCKET_ERROR)
	{
		fprintf(stderr, "failed to set send timeout: %d\n", WSAGetLastError());
		ExitProcess(STATUS_FAILED);
	}
	
	//进行域名解析并填充地址结构
	memset(&dest, 0, sizeof(dest));
	hp = gethostbyname(argv[1]);
	if(!hp)
	{
		addr = inet_addr(argv[1]);
	}
	if((!hp) && (addr==INADDR_NONE))
	{
		fprintf(stderr, "Unable to resolve %s\n", argv[1]);
		ExitProcess(STATUS_FAILED);
	}
	if(hp != NULL)
	{
		memcpy(&(dest.sin_addr), hp->h_addr, hp->h_length);
	}
	else
	{
		dest.sin_addr.s_addr = addr;
	}
	if(hp)
	{
		dest.sin_family = hp->h_addrtype;
	}
	else
	{
		dest.sin_family = AF_INET;
	}
	dest_ip = inet_ntoa(dest.sin_addr);
	if(argc > 2)
	{
		datasize = atoi(argv[2]);
		if(datasize == 0)
		{
			datasize = DEF_PACKET_SIZE;
		}
	}
	else
	{
		datasize = DEF_PACKET_SIZE;
	}
	
	//初始化ICMP请求包
	datasize += sizeof(IcmpHeader);
	icmp_data = (char*)xmalloc(MAX_PACKET);
	recvbuf = (char*)xmalloc(MAX_PACKET);
	if(!icmp_data)
	{
		fprintf(stderr, "HeapAlloc failed %d\n", GetLastError());
		ExitProcess(STATUS_FAILED);
	}
	memset(icmp_data, 0, MAX_PACKET);
	fill_icmp_data(icmp_data, datasize);
	
	while(1)
	{
		//构造ICMP请求包
		((IcmpHeader*)icmp_data)->timestamp = GetTickCount();
		((IcmpHeader*)icmp_data)->i_seq = seq_no++;
		((IcmpHeader*)icmp_data)->i_cksum = checksum((USHORT*)icmp_data, datasize);
		
		//发送ICMP请求包
		bwrote = sendto(sockRaw, icmp_data, datasize, 0, (struct sockaddr *)&dest, sizeof(dest));
		if(bwrote == SOCKET_ERROR)
		{
			if(WSAGetLastError() == WSAETIMEDOUT)
			{
				printf("timed out\n");
				continue;
			}
			fprintf(stderr, "sendto failed: %d\n", WSAGetLastError());
			ExitProcess(STATUS_FAILED);
		}
		if(bwrote < datasize)
		{
			fprintf(stdout, "Wrote %d bytes\n", bwrote);
		}
		
		//接收ICMP应答包
		bread = recvfrom(sockRaw, recvbuf, MAX_PACKET, 0, (struct sockaddr *)&from, &fromlen);
		if(bread == SOCKET_ERROR)
		{
			if(WSAGetLastError() == WSAETIMEDOUT)
			{
				printf("timed out\n");
				continue;
			}
			fprintf(stderr, "recvfrom failed: %d\n", WSAGetLastError());
			ExitProcess(STATUS_FAILED);
		}
		
		//解析ICMP应答包
		decode_resp(recvbuf, bread, &from);
		Sleep(1000);
	}
	return 0;
}