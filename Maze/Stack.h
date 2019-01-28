
#ifndef _STACK_H_
#define _STACK_H_

#include "Maze.h"

static const int STACK_SIZE = 1024;


class Stack
{
public:
	Stack()
	{
		Initialize();
	}
	//~Stack();
	bool Initialize();
	bool Push(Node);
	Node Pop();
	bool IsEmpty();
private:
	Node stack[STACK_SIZE];
	int front;
	bool empty;
};

bool Stack::Initialize()
{
#ifdef DEBUG
	cout<< "Initialize the stack." <<endl;
#endif
	front = 0;
	empty = true;
	return true;
}

bool Stack::Push(Node node)
{
	if(front < STACK_SIZE-1)
	{
		stack[++front] = node;
		empty = false;
		return true;
	}
	else
	{
#ifdef DEBUG
		cout<< "Stack is full now." <<endl;
#endif
		return false;
	}
}

Node Stack::Pop()
{
	if(front > -1)
	{
		Node node = stack[front--];
		return node;
	}
	else
	{
#ifdef DEBUG
		cout<< "Stack is empty now." <<endl;
#endif
		empty = true;
	}
}

bool Stack::IsEmpty()
{
	return empty;
}

#endif   //_STACK_H_