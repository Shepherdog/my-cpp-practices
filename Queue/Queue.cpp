
#include <iostream.h>

/*
* 队列结构
* */
const static int QUEUE_SIZE = 13;

class Queue
{
public:
	Queue(void)
	{
		Construct();
	}
	virtual bool Construct(void);
	bool In(int);
	int  Out(void);
	bool IsEmpty(void) const;
	bool IsFull(void) const;
	virtual ~Queue();
private:
	int* queue;
	int  rear, front;
	bool empty, full;
};

bool Queue::Construct()
{
	queue = new int[QUEUE_SIZE];
	rear = front = 0;
	empty = true;
	full = false;
	return true;
}

bool Queue::In(int val)
{
	if((rear+1)%QUEUE_SIZE == front)
	{
		full = true;
		return false;
	}
	else
	{
		empty = false;
		queue[(rear++)%QUEUE_SIZE] = val;
		return true;
	}
}

int Queue::Out()
{
	if(front == rear)
	{
		empty = true;
		return -1;
	}
	else
	{
		full = false;
		int	val = queue[(front++)%QUEUE_SIZE];
		return val;
	}
}

bool Queue::IsEmpty() const
{
	return empty;
}

bool Queue::IsFull() const
{
	return full;
}

Queue::~Queue()
{
	delete[] queue;
}


////////////////////////////////////////////////////////////////////////////////////////

void main()
{
	Queue* queue = new Queue();
	
	int i = 0;
	while(!queue->IsFull() && i<7)
	{
		queue->In(i);
		cout<< "Enqueue: " << i <<endl;
		i++;
	}
	
	int val = 0;
	while(!queue->IsEmpty())
	{
		val = queue->Out();
		if(val != -1)
		{
			cout<< "Dequeue: " << val <<endl;
		}
	}
}