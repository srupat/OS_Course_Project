#include<iostream>
#include<string>
#include"exeUnit.h"
#include"memory.h"
#include"job.h"

int main()
{	
	std::string inputBuffer = (char*)malloc(sizeof(char) * 40);
	std::string outputBuffer = (char*)malloc(sizeof(char) * 40);
	int caseVar{};
	int jobId{};
	int index{};
	Memory mem;
	ExecutionUnit exu;
	char* startAddOfMem = mem.getPtrToMemory();
	std::vector<Job> jobs{};
	for (int i = 0; i < 5; i++)
	{
		Job job;
		job.setJobIndex(i);
		jobs.push_back(job);
	}
	while (1)
	{
		std::cout << "Enter " << std::endl
			<< "1 -> To Insert a Job " << std::endl
			<< "2 -> To Execute a Job " << std::endl;
		std::cin >> caseVar;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		switch (caseVar)
		{
		case 1:
			index = mem.getIndex();
			if (index == -1)
			{
				std::cout << "Memory is full :( " << std::endl;
				break;
			}			
			std::cout << "Pls Enter the input cards ";
			std::getline(std::cin, inputBuffer);			
			jobs.at(index).setJobId(inputBuffer);
			jobs.at(index).setJobIndex(index);
			mem.setIndex(index);
			jobs.at(index).getData(inputBuffer, index, startAddOfMem);
			break; 
		case 2:
			// Execute a JOB
			std::cout << "Enter the Job Id : ";
			std::cin >> jobId;
			break;
		case 3:
			std::cout << "Enter valied command !" << std::endl;
		}
	}
}