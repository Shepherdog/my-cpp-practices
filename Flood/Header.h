
/***************************************************************************************
�����Ϸ������ݰ��Ĺ����ж���(��ICMP_FLOOD, ��Ƭ������)������һ�־�������TCPЭ����������
�Ĺ���(SYN_FLOOD)��

TCP���ӵ���������:
1.������A,B��̨����������B��SERVER��A��CLIENT��
2.����A������һ������SYN���(����ʼ���к�)�����ݱ���B��
3.Ȼ��B���գ�Ȼ����һ��ACK+SYN(��B������ʼ���кź�A��ȷ�Ϻ�)��A��
4.���A�ٷ���һ�������кź�ȷ�Ϻŵ����ݱ���B��
5.��ʱ���ӽ�����ɡ�

�������ԭ�����A���ڵ�һ��αװ���������ڵĻ�������B���ʹ�����SYN������ôB����Ϊ�к�
��Ϸ��Ļ����������ӣ�Ȼ��һһ��Ӧ��Ȼ��ȴ�������ȷ�Ͻ������ӡ���ô�����ȴ����ӵ�����
��������ջ�С�һ��������ȴ�2���ӻ�û�ȵ����������֣���ô�ͻ�ӵȴ����ӵ�ջ��ɾ������
�������A��SYN���͵��㹻�죬�Ϸ��û����Ӳ��ϣ���ô������Ҳ�Ứ�Ѵ�������Դ��ά��ջ��
�Ӷ��ճ�D.o.S������ͨ��RAW_SOCKET���Ϳ���α��IP��TCPͷ���������Դ��ַ��SYN����
***************************************************************************************/

//����IP�ײ�
typedef struct ip_head
{
	unsigned char   h_verlen;         //4λ�ײ�����,4λIP�汾��
	unsigned char   tos;              //8λ��������TOS
	unsigned short  total_len;        //16λ�ܳ���(�ֽ�)
	unsigned short  ident;            //16λ��ʶ
	unsigned short  frag_and_flags;   //3λ��־λ(��SYN,ACK��)
	unsigned char   ttl;              //8λ����ʱ�� TTL
	unsigned char   proto;            //8λЭ��(��ICMP��TCP��)
	unsigned short  checksum;         //16λIP�ײ�У���
	unsigned int    sourceIP;         //32λԴIP��ַ
	unsigned int    destIP;           //32λĿ��IP��ַ
}IPHEADER;

//����TCP�ײ�
typedef struct tcp_head
{
	USHORT        th_sport;     //16λԴ�˿�
	USHORT        th_dport;     //16λĿ�Ķ˿�
	unsigned int  th_seq;       //32λ���к�
	unsigned int  th_ack;       //32λȷ�Ϻ�
	unsigned char th_lenres;    //4λ�ײ�����/6λ������
	unsigned char th_flag;      //6λ��־λ
	USHORT        th_win;       //16λ���ڴ�С
	USHORT        th_sum;       //16λУ���
	USHORT        th_urp;       //16λ��������ƫ����
}TCPHEADER;

//����TCPα�ײ�
typedef struct tsd_head
{
	unsigned long  saddr;      //Դ��ַ
	unsigned long  daddr;      //Ŀ�ĵ�ַ
	char           mbz;
	char           ptcl;       //Э������
	unsigned short tcpl;       //TCP����
}PSDHEADER;