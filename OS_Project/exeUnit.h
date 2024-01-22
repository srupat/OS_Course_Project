#pragma once
#include"memory.h"
#include<iostream>

typedef struct {
	char* pg0;
	char* pg1;
	char* pg2;
	char* pg3;
	int jobID;
}SJOB;

class ExecutionUnit
{
	std::string GPR;
	char* IR;
	int PC;
	int lineCount;
	int controlFlag;
	char* temp;
	SJOB job;
public:
	char* getIR()
	{
		return IR;
	}
	int getPC()
	{
		return PC;
	}
	ExecutionUnit(int ptrToPage1, int ptrToPage2, int ptrToPage3, int ptrToPage4, int jobId, Memory& memory);
	void loadIR(ExecutionUnit& exec);
	int putData(std::string& outputBuffer);
	int loadInReg();
	int storeFromReg();
	int compareWithReg();
	void branch(ExecutionUnit& exec);	
	int operandError(int labelNo);
};

