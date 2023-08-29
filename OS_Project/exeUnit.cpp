#include"exeUnit.h"

ExecutionUnit::ExecutionUnit()
{
	lineCount = 0;
	GPR = (char*)malloc(sizeof(char) * 4);
	IR = (char*)malloc(sizeof(char) * 4);
	PC = (char*)malloc(sizeof(char) * 2);
	
	controlFlag = 0;
}
