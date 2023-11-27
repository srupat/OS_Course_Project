#pragma once

class Memory
{	
		char* ptrToMemory;
		friend class MemoryController;
	public:
		Memory();
		char* getPtrToMem();
};

class PageDirectory
{
	int* ptrToPageDirectory;
	friend class MemoryController;
public:
	PageDirectory();
	int* getPtrToPageDirectory(int pageTableIndex);
};

