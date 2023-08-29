#pragma once
#include"memory.h"
#include<iostream>

class Job
{
	int memIndex;
	int jobId;
	char* ptrToData;
	char* ptrToProgram;
public:
	Job();
	void setJobId(std::string);
	void setJobIndex(int );
	void getData(std::string, int, char* );
	char* getPtrToData(int);
	char* getPtrToProg(int);
};