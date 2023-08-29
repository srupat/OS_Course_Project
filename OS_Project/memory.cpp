#include"memory.h"
#include"job.h"
#include<string>
Memory::Memory() //constructor
{
	ptrToMemory = (char*)malloc(sizeof(char) * 400);
	for (int i = 0; i < 5; i++)
	{
		freeIndexArray[i] = 0;
	}
	// vector<vector<char>> Memory(100,vector<char>(4,0))
}


char* Memory::getPtrToMemory()
{
	return ptrToMemory;
}

void Memory::setIndex(int Index)
{
	freeIndexArray[Index] = 1;
}

int Memory::getIndex()
{
	int index = -1;
	for (int i = 0; i < 5; i++)
	{
		if (freeIndexArray[i] == 0)
		{
			index =  i;
			break;
		}
	}
	return index;
}