#pragma once
#include<iostream>
#include<vector>
#include"memory.h"
typedef struct line_TimeLimitContainer
{
	int jobId;
	int lineLimit;
	int timeLimit;
}LTSTRUCT;
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
	int getTimeLimit(std::string inputBuffer);
	int getLineLimit(std::string inputBuffer);
	int outOfData(std::string inputBuffer);
	int getPageTableIndex(int jobId);
};
