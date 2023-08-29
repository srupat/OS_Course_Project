#include"memory.h"
#include<string>
Memory::Memory() //constructor
{
	ptrToMemory = (char*)malloc(sizeof(char) * 400);
	ptrToData = ptrToMemory + 40;
	ptrToProgram = ptrToMemory;
	// vector<vector<char>> Memory(100,vector<char>(4,0))
}
char* Memory::getData(std::string inputBuffer)
{
	int t = inputBuffer.find("$DTA");
	int Index = t + 5;
	int i = 0;

	while (inputBuffer[Index] != '$' && i != 39) {

		char c = inputBuffer[Index];
		ptrToData[i] = inputBuffer[Index];
		Index++;
		i++;
	}
	ptrToData[i] = '\0';
}

//char* Memory::getProgram()
//{
//
//}