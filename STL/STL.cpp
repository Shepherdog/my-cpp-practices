
#include <iostream.h>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <utility>
#include <map>
#include <algorithm>
#include <numeric>
#include <functional>


using namespace std;

void printScore(int val)
{
	cout<< val <<endl;
}

bool perfectScore(int num)
{
	return(num >= 2);
}

void printCondition(bool cond)
{
	if(cond)
	{
		cout<< "Yes" <<endl;
	}
	else
	{
		cout<< "No" <<endl;
	}
}

void main()
{
	////////////////////////////////////////////////////////////////////////////////////
	vector<int> myVector;
	vector<int> myVector1;
	vector<int>::iterator vIterator;

	myVector1.push_back(2);
	myVector1.push_back(3);
	myVector1.push_back(1);
	myVector1.insert(myVector1.begin()+myVector1.size(), 4);
	
	int score[] = {4, 7, 6, 5};
	vector<int> myVector2(score, score+4);

	myVector.resize(myVector1.size());
	copy(myVector1.begin(), myVector1.end(), myVector.begin());
	myVector.resize(myVector1.size()+myVector2.size());
	copy(myVector2.begin(), myVector2.end(), myVector.begin()+myVector1.size());

	//myVector.erase(myVector.begin(), myVector.end());
	//myVector.erase(myVector.begin()+4, myVector.begin()+5);

	myVector.resize(myVector1.size()+myVector2.size());
	merge(myVector1.begin(), myVector1.end(), myVector2.begin(), myVector2.end(), 
		myVector.begin());
	
	sort(myVector.begin(), myVector.end());

	transform(myVector.begin(), myVector.end(), myVector.begin(), 
		bind2nd(plus<int>(), 1));

	cout<< "All scores in the vector:" <<endl;
	for_each(myVector.begin(), myVector.end(), printScore);

	cout<< "The max score is:";
	vIterator = max_element(myVector.begin(), myVector.end());
	cout<< *vIterator <<endl;

	cout<< "Found 8:";
	bool found = binary_search(myVector.begin(), myVector.end(), 8);
	printCondition(found);

	cout<< "Found [3, 4, 5]:";
	int temp[] = {3, 4, 5};
	vIterator = search(myVector.begin(), myVector.end(), temp, temp+3);
	printCondition(vIterator != myVector.end());

	cout<< "Is set1 a subset of set:";
	set_union(myVector1.begin(), myVector1.end(), myVector2.begin(), myVector2.end(), 
		myVector.begin());
	sort(myVector.begin(), myVector.end());
	bool isSub = includes(myVector1.begin(), myVector1.end(), 
		myVector.begin(), myVector.end());
	printCondition(isSub);

	cout<< "Perfect scores are:" <<endl;
	vector<int>::iterator ptr;
	vector<int>::iterator tmp;
	for(vIterator=myVector.begin(); vIterator<myVector.end(); vIterator++)
	{
		tmp = ptr;
		//ptr = find_if(vIterator, myVector.end(), perfectScore);
		ptr = find_if(vIterator, myVector.end(), bind2nd(greater_equal<int>(), 4));
		if(tmp!=ptr && ptr!=myVector.end())
		{
			cout<< *ptr <<endl;
		}
	}

	cout<< "The sum of scores:";
	int sum = accumulate(myVector.begin(), myVector.end(), 0, plus<int>());
	cout<< sum <<endl;

	////////////////////////////////////////////////////////////////////////////////////
	list<char*> myList;
	list<char*>::iterator lIterator;

	myList.push_back("Hello");
	myList.push_back("the");
	myList.push_back("world");
	myList.push_back("world");
	myList.unique();
	myList.sort();

	cout<< "All words in the list:" <<endl;
	//int i;
	//for(i=0,lIterator=myList.begin(); i<4; i++,lIterator++)
	//{
	//	cout<< *lIterator <<endl;
	//}
	//There is something wrong, but I had not found it.
	for(lIterator=myList.begin(); lIterator!=myList.end(); lIterator++)
	{
		cout<< *lIterator <<endl;
	}
	//Now, I has found it "lIterator!=myList.end()".
	//Because the addresses of list in memory is not linear.

	////////////////////////////////////////////////////////////////////////////////////
	queue<int> myQueue;

	myQueue.push(1);
	myQueue.push(2);
	myQueue.push(3);

	cout<< "All numbers in the queue:" <<endl;
	//for(int k=0; k<=myQueue.size()+1; k++)
	while(!myQueue.empty())
	{
		cout<< myQueue.front() <<endl;
		myQueue.pop();
	}

	////////////////////////////////////////////////////////////////////////////////////
	stack<int> myStack;

	myStack.push(1);
	myStack.push(2);
	myStack.push(3);

	cout<< "All items in the stack:" <<endl;
	for(int m=0; m<=myStack.size()+1; m++)
	{
		cout<< myStack.top() <<endl;
		myStack.pop();
	}

	////////////////////////////////////////////////////////////////////////////////////
	pair<int, char> myPair;

	myPair = make_pair(1, 'A');

	cout<< "All contents in the pair:" <<endl;
	cout<< myPair.first << "-" << myPair.second <<endl;

	////////////////////////////////////////////////////////////////////////////////////
	map<int, char> myMap;
	map<int, char>::iterator mIterator;

	//myMap[1] = 'A';
	//myMap[2] = 'B';
	//myMap[3] = 'C';
	myMap.insert(make_pair(1, 'A'));
	myMap.insert(make_pair(2, 'B'));
	myMap.insert(make_pair(3, 'C'));
	//myMap.erase(1);
	//myMap.erase(2);
	//myMap.erase(3);

	cout<< "All pairs in the map:" <<endl;
	//Pay attention to "mIterator!=myMap.end()",
	//because the iterator of map is not linear.
	for(mIterator=myMap.begin(); mIterator!=myMap.end(); mIterator++)
	{
		cout<< mIterator->first << "-" << mIterator->second <<endl;
	}

	cout<< "Find a element whose index is 2:" <<endl;
	mIterator = myMap.find(2);
	cout<< mIterator->first << "-" << mIterator->second <<endl;

	////////////////////////////////////////////////////////////////////////////////////
	multimap<int, char> myMultimap;
	multimap<int, char>::iterator start;
	multimap<int, char>::iterator end;
	pair<multimap<int, char>::iterator, multimap<int, char>::iterator> range;

	myMultimap.insert(make_pair(1, 'A'));
	myMultimap.insert(make_pair(1, 'B'));
	myMultimap.insert(make_pair(2, 'C'));

	range = myMultimap.equal_range(1);
	start = range.first;
	//start = myMultimap.lower_bound(1);
	end = range.second;
	//end = myMultimap.upper_bound(1);
	cout<< "Find a element whose index is 1:" <<endl;
	for(; start!=end; start++)
	{
		cout<< (*start).first << "-" << (*start).second <<endl;
	}
}