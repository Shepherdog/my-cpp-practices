
#include <windows.h>
#include <iostream.h>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

/*
* XPath½âÎöÆ÷
* */
using namespace std;

class XmlDom
{
public:
	XmlDom()
	{}
	virtual void loadDocument(const string&);
	virtual bool initParser(void);
	virtual vector<string>& getNodeValue(const string&);
	virtual void showParser(void);
	static void printNode(const string&);
	virtual ~XmlDom()
	{}
private:
	string xmlDoc;
	vector<string> xmlParser;
};

void XmlDom::loadDocument(const string& strDoc)
{
	xmlDoc = strDoc;
}

bool XmlDom::initParser(void)
{
	queue<int> index;
	for(int i=0; i<xmlDoc.length(); i++)
	{
		if(xmlDoc[i]=='<' || xmlDoc[i]=='>')
		{
			index.push(i);
		}
	}
	
	//Load XML document to the parser
	int t = 0;
	int j = 0;
	string node = "";
	while(!index.empty())
	{
		j = index.front();
		index.pop();
		if(t!=j && (t+1)!=j)
		{
			//cout<< t << "-" << j <<endl;
			if(xmlDoc[t]=='<' && xmlDoc[j]=='>')
			{
				node.resize(j-t+1);
				copy(xmlDoc.begin()+t, xmlDoc.begin()+j+1, node.begin());
			}
			if(xmlDoc[t]=='>' && xmlDoc[j]=='<')
			{
				node.resize(j-t-1);
				copy(xmlDoc.begin()+t+1, xmlDoc.begin()+j, node.begin());
			}
			xmlParser.push_back(node);
		}
		t = j;
	}
	return true;
}

vector<string>& XmlDom::getNodeValue(const string& path)
{
	//Get steps
	queue<int> index;
	for(int i=0; i<path.length(); i++)
	{
		if(path[i] == '/')
		{
			index.push(i);
		}
	}
	index.push(path.length());
	
	vector<string> scope;
	int t = -1;
	int j = -1;
	string route = "";
	while(!index.empty())
	{
		j = index.front();
		index.pop();
		route.resize(j-t+1);
		copy(path.begin()+t+1, path.begin()+j, route.begin());
		scope.push_back(route);
		t = j;
	}
	
	//Locate it
	vector<string>::iterator it;
	vector<string>::iterator pointer;
	vector<string>::iterator pointer1;
	vector<string>::iterator pointer2;
	vector<string>::iterator start;
	vector<string>::iterator stop;
	vector<string>::iterator scan;
	vector<string>::iterator tmp1;
	vector<string>::iterator tmp2;
	map<vector<string>::iterator, vector<string>::iterator> container[2];
	map<vector<string>::iterator, vector<string>::iterator>* last;
	map<vector<string>::iterator, vector<string>::iterator>::iterator range;
	
	//Retrieve the tag and save it
	string tag = "";
	it = scope.end();
	tag = *(it-1);
	scope.pop_back();
	
	//Get the right place by routes
	string ptr = "";
	string ptr1 = "";
	string ptr2 = "";
	int n = 0;
	container[0].insert(make_pair(xmlParser.begin(), xmlParser.end()));
	
	for(it=scope.begin(); it!=scope.end(); it++)
	{
		//Swap the container
		int i = n % 2;
		int j = (++n) % 2;
		
		ptr = *it;
		//Make <ptr>
		ptr1.resize(ptr.length());
		ptr1[0] = '<';
		for(int m=0; m<ptr.length(); m++)
		{
			ptr1[m+1] = ptr[m];
		}
		ptr1[ptr.length()-1] = '>';
		//Make </ptr>
		ptr2.resize(ptr.length()+1);
		ptr2[0] = '<';
		ptr2[1] = '/';
		for(int n=0; n<ptr.length(); n++)
		{
			ptr2[n+2] = ptr[n];
		}
		ptr2[ptr.length()] = '>';
		
		//int i = n % 2;
		//int j = (++n) % 2;
		
		for(range=container[i].begin(); range!=container[i].end(); range++)
		{
			start = (*range).first;
			stop = (*range).second;
			//!!!container1.erase(start);
			
			//Start searching...
			scan = start;
			while(scan != stop)
			{
				//Find <ptr>
				pointer1 = find(scan, stop, ptr1);
				if(tmp1!=pointer1 && pointer1!=stop)
				{
					//cout<< "Parse ";
					//printNode(ptr1);
					scan = pointer1;
					tmp1 = pointer1;
				}
				else
				{
					break;
				}
				//Find </ptr>
				pointer2 = find(scan, stop, ptr2);
				if(tmp2!=pointer2 && pointer2!=stop)
				{
					scan = pointer2;
					tmp2 = pointer2;
				}
				else
				{
					break;
				}
				
				//if(pointer1!=stop && pointer2!=stop)
				//{
					container[j].insert(make_pair(pointer1+1, pointer2));
				//}
			}
		}
		container[i].clear();
	}
	
	//Make <tag>
	ptr.resize(tag.length());
	ptr[0] = '<';
	for(int m=0; m<tag.length(); m++)
	{
		ptr[m+1] = tag[m];
	}
	ptr[tag.length()-1] = '>';
	
	last = &((container[0].empty()) ? container[1] : container[0]);
	//Get value by tag name
	vector<string> result;
	string value = "";
	cout<< "Found " << (*last).size() << " ";
	printNode(ptr);
	for(range=(*last).begin(); range!=(*last).end(); range++)
	{
		start = (*range).first;
		stop = (*range).second;
		pointer = find(start, stop, ptr);
		if(pointer != stop)
		{
			value = *(pointer+1);
			printNode(value);
			result.push_back(value);
		}
	}
	return result;
}

void XmlDom::printNode(const string& node)
{
	//static const int LEN = 1024;
	int LEN = node.size()+1;
	char* content = new char[LEN];
	memset(content, 0, LEN);
	for(int i=0; i<node.length(); i++)
	{
		content[i] = node[i];
	}
	cout<< content <<endl;
	delete[] content;
}

void XmlDom::showParser(void)
{
	vector<string>::iterator it;
	for(it=xmlParser.begin(); it!=xmlParser.end(); it++)
	{
		printNode(*it);
	}
}


////////////////////////////////////////////////////////////////////////////////////////

void main()
{
	XmlDom dom;
	string xmlDoc = "<?xml version=\"1.0\"?><word><head><text><value>Hello</value></text></head><body><text><value>The</value><style>big</style></text><text><value>World</value><style>small</style></text></body></word>";
	char* input = "word/body/text/value";
	//string xmlDoc = "<Order><Manifest><Item><ID>101</ID><NAME>All about DOM.</NAME><PRICE>$39</PRICE></Item><Item><ID>102</ID><NAME>The story about ...</NAME><PRICE>$29</PRICE></Item><Item><ID>103</ID><NAME>Wnen to use a DOM.</NAME><PRICE>$49</PRICE></Item><Item><ID>104</ID><NAME>Java 2.</NAME><PRICE>$59</PRICE></Item></Manifest></Order>";
	//char* input = "Order/Manifest/Item/ID";
	string str(input);
	long before = ::GetTickCount();
	dom.loadDocument(xmlDoc);
	if(dom.initParser())
	{
		cout<< "Load XML/HTML document to parser completely." <<endl;
		dom.showParser();
		cout<< "Parsing " << input <<endl;
		cout<< "____________________________________________" <<endl;
		dom.getNodeValue(str);
		cout<< "____________________________________________" <<endl;
	}
	long current = ::GetTickCount();
	cout<< "Elapsed time: " << (current-before) << "ms" <<endl;
}