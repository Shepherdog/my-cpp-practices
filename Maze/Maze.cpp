
#include <iostream.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include "Stack.h"

/*
 * A*Ѱ·�㷨
 * */
void MakeMap(int[MAP_X][MAP_Y]);   //������ͼ
bool IsValid(Pos);                 //�жϵ�ǰλ���Ƿ���Ч
bool IsDest(Pos, Pos);             //�ж��Ƿ񵽴��յ�
void MarkIt(Pos);                  //��̽�����λ�����ñ�־
void StepTo(Pos);                  //����һ��λ��
void PushPos(Pos, Stack&);         //����ǰ���е�λ��ѹ�뵽��ջ
bool FindPath(Pos, Pos);           //Ѱ�����ŵ�·��
void ShowMap(void);                //��ʾ��ͼ

void MakeMap(int bit[MAP_X][MAP_Y])
{
	for(int i=0; i<MAP_X; i++)
	{
		for(int j=0; j<MAP_Y; j++)
		{
			if(bit[i][j] == 0)
			{
				map[i][j] = CAN_STEP;
			}
			else
			{
				map[i][j] = NOT_STEP;
			}
		}
	}
}

void ShowMap(void)
{
	Sleep(300);
	system("cls");
	for(int i=0; i<MAP_X; i++)
	{
		for(int j=0; j<MAP_Y; j++)
		{
			cout<< " ";
			switch(map[i][j])
			{
			case 0:
				cout<< " ";
				break;
			case 1:
				cout<< "#";
				break;
			case 2:
				cout<< "@";
				break;
			case 3:
				cout<< " ";
				break;
			default:
				break;
			}
		}
		cout<<endl;
	}
}

bool IsValid(Pos pos)
{
	return (pos.x>=0)&&(pos.x<MAP_X)&&(pos.y>=0)&&(pos.y<MAP_Y);
}

bool IsDest(Pos pos, Pos dest)
{
	return (dest.x==pos.x)&&(dest.y==pos.y);
}

void MarkIt(Pos pos)
{
	map[pos.x][pos.y] = SET_MARK;
}

void StepTo(Pos pos)
{
	map[pos.x][pos.y] = HAS_STEP;
}

void PushPos(Pos pos, Pos dest, Stack& stack)
{
	Vect vect[4];                       //��������4����������
	vect[0].dx = 0;  vect[0].dy = 1;    //vect[0] = {0, 1};
	vect[1].dx = 1;  vect[1].dy = 0;    //vect[1] = {1, 0};
	vect[2].dx = -1; vect[2].dy = 0;    //vect[2] = {-1, 0};
	vect[3].dx = 0;  vect[3].dy = -1;   //vect[3] = {0, -1};

	//�ж�����4�������������ļ������Բ���
	Judge* head = NULL;
	Judge* ptr = NULL;
	Judge* tmp = NULL;
	Pos current;
	int cost;
	for(int i=0; i<4; i++)
	{
		current.x = pos.x + vect[i].dx;
		current.y = pos.y + vect[i].dy;
		//��⵱ǰλ���Ƿ�Խ���ҿɲ���
		if(IsValid(current))
		if(map[current.x][current.y]==CAN_STEP)
		{
			//�Ե�ǰ�ڵ��������
			//���ۺ���: f(n)=g(n)+h(n)
			//
			cost = abs(current.x-dest.x) + abs(current.y-dest.y);
			//cost = (current.x-dest.x)*(current.x-dest.x) + (current.y-dest.y)*(current.y-dest.y);

			Judge* judge = new Judge();
			judge->node.pare = pos;
			judge->node.self = current;
			judge->node.cost = cost;
			judge->next = NULL;
			if(head == NULL)
			{
				//��һ���ڵ�����ͷ
				head = judge;
			}
			else
			{
				//�����ǰλ�õ��յ�ľ����������Ϊ�±�ͷ
				if(judge->node.cost >= head->node.cost)
				{
					judge->next = head;
					head = judge;
				}
				else
				{
					//�����ǰλ�õ��յ�ľ��벻���������뵽���еĺ���λ��
					bool inserted = false;
					ptr = head;
					while(ptr != NULL)
					{
						if(judge->node.cost >= ptr->node.cost)
						{
							judge->next = ptr;
							tmp->next = judge;
							inserted = true;
						}
						tmp = ptr;
						ptr = ptr->next;
					}
					//�����ǰλ�õ��յ�ľ�����С����뵽��β
					if(!inserted)
					{
						tmp->next = judge;
					}
				}
			}
		}
	}

	//�����д洢��λ����Ϣѹ���ջ
	ptr = head;
	while(ptr != NULL)
	{
		stack.Push(ptr->node);
		tmp = ptr;
		//delete tmp;
		ptr = ptr->next;
	}
}

bool FindPath(Pos sour, Pos dest)
{
	Pos record[MAP_X][MAP_Y];
	Stack stack;
	Node node;
	node.self = sour;
	stack.Push(node);

	//�жϴ���㵽�յ�֮���Ƿ���ͨ·
	Node temp;
	while(true)
	{
		if(!stack.IsEmpty())
		{
			temp = stack.Pop();
		}
		else
		{
			return false;
		}
		if(IsDest(temp.self, dest))
		{
			if(IsValid(temp.self))
			{
				MarkIt(temp.self);
				record[temp.self.x][temp.self.y] = temp.pare;
			}
			break;
		}
		else
		{
			if(IsValid(temp.self))
			{
				MarkIt(temp.self);
				record[temp.self.x][temp.self.y] = temp.pare;
				PushPos(temp.self, dest, stack);
			}
		}
	}

	//�����ͨ·��Ѱ�Һ��ʵ�·��
	Pos parent = dest;
	bool success = false;
	while(IsValid(parent) && !success)
	{
		StepTo(parent);
		ShowMap();
		MarkIt(parent);
		parent = record[parent.x][parent.y];
		if(parent.x==sour.x && parent.y==sour.y)
		{
			success = true;
		}
	}

	return true;
}


////////////////////////////////////////////////////////////////////////////////////////

void main()
{
	//������ͼ
	int map_matrix[MAP_X][MAP_Y] = {
	 // 0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
		1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,  //0
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,  //1
		1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1,  //2
		1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1,  //3
		1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0,  //4
		1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1,  //5
		1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1,  //6
		1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1,  //7
		1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1,  //8
		0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,  //9
		1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1,  //a
		1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1,  //b
		1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1,  //c
		1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1,  //d
		0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0,  //e
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,  //f
	};
	Pos source = {0x1, 0x0};   //���
	Pos destin = {0xe, 0xf};   //�յ�
	MakeMap(map_matrix);

	//Ѱ��·��
	cout<< "The sprite is running to the castle..." <<endl;
	Sleep(1000);
	bool found = false;
	found = FindPath(destin, source);
	if(found)
	{
		cout<< "Wow!!! The sprite has reached the castle." <<endl;
	}
	else
	{
		cout<< "Oops!!! The sprite has been lost in forest." <<endl;
	}

	//��ӡ��ͼ
	//ShowMap();
}