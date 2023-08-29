#pragma once

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

