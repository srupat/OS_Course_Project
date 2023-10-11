#pragma once
#include<iostream>
#include<vector>
#include"memory.h"

class MemoryController
{
	int* pageTableToJobMap;
	int* occupiedMemFrames;
public:
	MemoryController();
	int getEmptyPageTable();
	int getJobId(std::string inputBuffer);
	void setJobId(int jobId, int pageTableIndex);
	void generateFrames(PageDirectory& pageDir, int pageTableIndex);
	void pushInstructions(int jobId, PageDirectory& pageDir, Memory& memory, std::string inputBuffer );
	void printFrame(int frame, Memory& memory);
	void pushData(int jobId, PageDirectory& pageDir, Memory& memory, std::string inputBuffer);
};
