#include<iostream>
#include<string>
#include"exeUnit.h"
#include"memory.h"

int main()
{	
	std::string inputBuffer = (char*)malloc(sizeof(char) * 40);
	std::string outputBuffer = (char*)malloc(sizeof(char) * 40);
	Memory mem;
	ExecutionUnit exu;
	std::cout << "Pls Enter the input cards " << std::endl;
	std::getline(std::cin, inputBuffer);
	mem.getData(inputBuffer);
}