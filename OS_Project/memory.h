#pragma once
#include<iostream>
#include<vector>

class Memory
{	
		char* ptrToMemory;
		char* ptrToData;
		char* ptrToProgram;
	public:
		Memory();
		char* getData(std::string inputBuffer);
		char* getProgram();	
};
