#ifndef EXE_UNIT_H
#define EXE_UNIT_H

#include<iostream>
class ExecutionUnit
{
	char* GPR;
	char* IR;
	char* PC;
	int lineCount;
	int controlFlag;
public:
	ExecutionUnit();
};

#endif