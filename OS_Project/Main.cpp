#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include"exeUnit.h"
#include"memory.h"
#include"memController.h"

typedef struct {
	char* pg0;
	char* pg1;
	char* pg2;
	char* pg3;
	int jobID;
}SJOB;


int main()
{	
	Memory memory;
	PageDirectory pageDirectory;
	MemoryController memController;
	int casevar{};
	int pageTableIndex{ -1 };
	int jobId;
	std::string filepath;
	std::string inputBuffer;
	std::string outputBuffer;
	std::ifstream file;
	int* ptrToPageTable{ NULL };
	char c{};
	int fileCount{};
	do
	{
		std::cout << "Enter the code for the operation you have to perform :";
		std::cin >> casevar;
		switch (casevar)
		{
		case 1:
			// Insert a Job1

			pageTableIndex = memController.getEmptyPageTable();
			if (pageTableIndex == -1)
			{
				std::cout << "The Memoey is full " << std::endl;
			}
			//std::getline(std::cin, "Sample.");
			file.open("sample.txt");
			if (file.fail() == true)
			{
				std::cout << "Error opening the file " << std::endl;
				break;
			}
			while (file.get(c))
			{
				inputBuffer += c;
				fileCount++;
			}
			inputBuffer += '\0';
			file.close();
			ptrToPageTable = pageDirectory.getPtrToPageDirectory(pageTableIndex);
			jobId = memController.getJobId(inputBuffer);
			memController.setJobId(jobId, pageTableIndex);
			memController.generateFrames(pageDirectory, pageTableIndex);
			memController.pushInstructions(jobId, pageDirectory, memory, inputBuffer);
			memController.pushData(jobId, pageDirectory, memory, inputBuffer);

			std::cout << std::endl;		
			memController.printFrame(ptrToPageTable[0], memory);
			std::cout << std::endl;
			memController.printFrame(ptrToPageTable[1], memory);
			std::cout << std::endl;
			memController.printFrame(ptrToPageTable[2], memory);
			std::cout << std::endl;
			memController.printFrame(ptrToPageTable[3], memory);
			std::cout << std::endl;
			break;
		case 2:
			// Execute a Job
			break;
		case 3:
			// Delete a Job
		default:
			std::cout << "Invalid Input ";
			break;
		}
	} while (casevar != -1);
}