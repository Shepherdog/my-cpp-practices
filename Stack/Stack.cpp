
#include <iostream.h>
#include <stdlib.h>

/*
* ¶ÑÕ»½á¹¹
* */
const static int STACK_SIZE = 64;

class Stack
{
public:
	Stack()
	{
		Construct();
	}
	virtual bool Construct(void);
	bool Push(int);
	bool Pop(void);
	virtual ~Stack();
private:
	int* stack;
	int* front;
};

bool Stack::Construct()
{
	stack = new int[STACK_SIZE];
	//for(int i=0; i<STACK_SIZE; i++)
	//	stack[i] = 0;
	front = stack;
	cout<< "S @ " << front <<endl; 
	cout<< "--------------"<<endl;
	return true;
}

bool Stack::Push(int val)
{
	if(++front <= stack+STACK_SIZE-1)
	{
		*front = val;
		cout<< val << " @ " << front <<endl;
		return true;
	}
	else
	{
		front--;
		cout<< "The stack has been full." <<endl;
		return false;
	}
}

bool Stack::Pop()
{
	if(front != stack)
	{
		int val = *front;
		cout<< val << " @ " << front <<endl;
		front--;
		return true;
	}
	else
	{
		cout<< "The stack has been empty."<<endl;
		return false;
	}
}

Stack::~Stack()
{
	delete[] stack;
}


////////////////////////////////////////////////////////////////////////////////////////

void main()
{
	Stack* stack = new Stack();

	stack->Push(1);
	stack->Push(2);
	stack->Push(3);
	stack->Push(4);
	stack->Push(5);
	stack->Push(6);
	stack->Push(7);
	cout<< "--------------" <<endl;
	stack->Pop();
	stack->Pop();
	stack->Pop();
	stack->Pop();
	stack->Pop();
	stack->Pop();
	stack->Pop();

	/*
	while(true)
	{
		int num;
		cin>> num;
		if(stack.Push(num) == false)
			break;
	}
	while(true)
	{
		int val;
		if(stack.Pop(val) == true)
			cout<< val <<endl;
		else
			break;
	}
	*/
}