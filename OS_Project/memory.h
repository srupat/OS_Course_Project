#pragma once
#include<iostream>
#include<vector>

class Memory
{	
		char* ptrToMemory;
		int freeIndexArray[5];
	public:
		Memory();
		char* getData(std::string , int );
		char* getProgram();	
		char* getPtrToMemory();
		int getIndex();
		void setIndex(int );
};
