#include"memory.h"
#include"memController.h"
#include<string>
Memory::Memory() //constructor
{

	ptrToMemory = (char*)malloc(sizeof(char) * 800);
	
}

char* Memory::getPtrToMem()
{
	return ptrToMemory;
}

PageDirectory::PageDirectory()
{
	ptrToPageDirectory = new int[20];
	for (int i = 0; i < 20; i++) {
		ptrToPageDirectory[i] = -1;
	}
}

int* PageDirectory::getPtrToPageDirectory(int pageTableIndex)
{
	int* ptrToPageTable = ptrToPageDirectory + pageTableIndex * 4;
	return ptrToPageTable;
}