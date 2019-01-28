
#include <iostream.h>
#include <fstream.h>
#include <string.h>

#define MAX_WORD 70


int write_data(void)
{
	char* word[MAX_WORD] = //数据列表
	{"monday", "tuesday", "wednesday", "thursday", "friday", 
	"fast", "saturday", "sunday", "abort", "aspect", 
	"busy", "bull", "baby", "best","cash", 
	"dash", "disk", "dumb", "enable", "efficient", 
	"explorer", "echo", "flush", "football", "gang", 
	"gas", "glance", "high", "Hello", "hard",
	"iterator", "jerk", "jump", "kick", "kill", 
	"linger", "light", "less", "monster", "master", 
	"now", "love", "nothing", "nonsense", "objective", 
	"october", "patch", "pitch", "piss", "query", 
	"question", "rise", "rice", "right", "soft", 
	"teach", "touch", "ultimate", "unlike", "vain", 
	"vanish", "victory", "wrong", "wolf", "water", 
	"you", "x", "yard", "zone", "zebra"};
	
	ofstream outFile("words.dat");
	if(!outFile.fail())
	{
		for(int w=0; w<MAX_WORD; w++)
		{
			outFile<< word[w] << '/' <<endl;
		}
	}
	else
	{
		cerr<< "An error occured when create file." <<endl;
	}
	outFile.close();
	return 1;
}

int read_data(void)
{
	char word[MAX_WORD][30];
	char temp[30];
	ifstream inFile;
	
	try
	{
		inFile.open("words.dat");
		if(!inFile.fail())
		{
			for(int w=0; w<MAX_WORD; w++)
			{
				if(!inFile.eof())
				{
					memset(temp, 0, sizeof(temp));
					inFile>> temp;
					//word[w] = temp;
					strcpy(word[w], temp);
				}
			}
			/*
			for(int t=0; t<MAX_WORD; t++)
			{
				cout<< "Load " << t+1 << " - " << word[t] <<endl;
			}
			*/
		}
		inFile.close();
	}
	catch(...)
	{
		cerr<< "An error occured when open file." <<endl;
		inFile.close();
		return 0;
	}
	return 1;
}

void main()
{
	if(write_data())
	{
		cout<< "Write data to file completely." <<endl;
	}
}