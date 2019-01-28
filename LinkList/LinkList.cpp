
#include <iostream.h>

/*
* Á´±í½á¹¹
* */
struct Node
{
	int   data;
	Node* next;
};


class LinkList
{
public:
	LinkList()
	{
		Construct();
	}
	virtual bool Construct(void);
	bool AddTo(int);
	bool Display(void) const;
	//bool Insert();
	bool Delete(int);
	bool Destroy(void);
	const Node* GetHead(void) const;
	virtual ~LinkList()
	{}
private:
	Node* head;
};

bool LinkList::Construct()
{
	Node* ptr = new Node;
	if(ptr != NULL)
	{
		ptr->data = 0;
		ptr->next = NULL;
		head = ptr;
		cout<< "Add item 0" << " @ " << head << " - " << head->next <<endl; 
		return true;
	}
	return false;
}

bool LinkList::AddTo(int value)
{
	Node* ptr = new Node;
	if(ptr != NULL)
	{
		ptr->data = value;
		ptr->next = head;
		head = ptr;
		cout<< "Add item " << value << " @ " << ptr << " - " << ptr->next <<endl;
		return true;
	}
	return false;
}

bool LinkList::Display() const
{
	Node* ptr = new Node;
	if(head != NULL)
	{
		ptr = head;
		try
		{
			while(ptr != NULL)
			{
				cout<< "See item " << ptr->data << " @ " << ptr << " - " << ptr->next <<endl;
				ptr = ptr->next;
			}
		}
		catch(...)
		{
			cout<< "\nAn error occured!" <<endl;
			return false;
		}
		return true;
	}
	return false;
}

bool LinkList::Delete(int value)
{
	Node* ptr = new Node;
	if(head != NULL)
	{
		if(head->data == value)
		{
			head = head->next;
		}
		ptr = head;
		try
		{
			while(ptr != NULL)
			{
				if(ptr->next->data == value)
				{
					ptr->next = ptr->next->next;
					break;
				}
				else
				{
					ptr = ptr->next;
				}
			}
		}
		catch(...)
		{
			cout<< "\nAn error occured!" <<endl;
			return false;
		}
		return true;
	}
	return false;
}

const Node* LinkList::GetHead() const
{
	return head;
}


////////////////////////////////////////////////////////////////////////////////////////

void main()
{
	int a[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	LinkList* lnklst = new LinkList();
	if(lnklst->GetHead() != NULL)
	{
		for(int i=0; i<9; i++)
		{
			lnklst->AddTo(a[i]);
		}
	}
	cout<< "------------------------------------" <<endl;
	lnklst->Delete(0);
	lnklst->Display();
}