#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include"exeUnit.h"
#include"memory.h"
#include"memController.h"
int main()
{
	Memory memory;
	PageDirectory pageDirectory;
	MemoryController memController;
	std::vector< LTSTRUCT> LL_TL_container;
	int casevar{};
	int pageTableIndex{ -1 };
	int jobId;
	char a;
	std::string filepath;
	std::string inputBuffer;
	std::string outputBuffer;
	std::ifstream file;
	int timeLimit;
	int lineLimit;
	LTSTRUCT obj;
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
				std::cout << "The Memory is full " << std::endl;
			}
			std::cout << "Enter the file name :";
			while (filepath == "")
			{
				filepath.clear();
				std::getline(std::cin, filepath);
			}
			file.open(filepath);
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
			ptrToPageTable = pageDirectory.getPtrToPageDirectory(pageTableIndex);  // returns pointerToPageTable
			jobId = memController.getJobId(inputBuffer);
			memController.setJobId(jobId, pageTableIndex);
			timeLimit = memController.getTimeLimit(inputBuffer);
			lineLimit = memController.getLineLimit(inputBuffer);
			obj.jobId = jobId;
			obj.lineLimit = lineLimit;
			obj.timeLimit = timeLimit;
			LL_TL_container.push_back(obj);
			memController.generateFrames(pageDirectory, pageTableIndex);
			memController.pushInstructions(jobId, pageDirectory, memory, inputBuffer);			
			if (memController.outOfData(inputBuffer))
			{
				std::cout << "--------------------------------------------------------" << std::endl;
				std::cout << "Out of data error" << std::endl;
				break;
			}
			else
			{
				memController.pushData(jobId, pageDirectory, memory, inputBuffer);
				std::cout << std::endl;
			}		
			memController.printFrame(ptrToPageTable[0], memory);
			std::cout << std::endl;
			memController.printFrame(ptrToPageTable[1], memory);
			std::cout << std::endl;
			memController.printFrame(ptrToPageTable[2], memory);
			std::cout << std::endl;
			memController.printFrame(ptrToPageTable[3], memory);
			std::cout << std::endl;

			filepath.clear();
			inputBuffer.clear();
			break;
		case 2:
			std::cout << "Enter the job id :";
			std::cin >> jobId;
			std::cout << "--------------------OUTPUT---------------------------" << std::endl;
			pageTableIndex = memController.getPageTableIndex(jobId);
			ptrToPageTable = pageDirectory.getPtrToPageDirectory(pageTableIndex);
			ExecutionUnit exec(ptrToPageTable[0], ptrToPageTable[1], ptrToPageTable[2], ptrToPageTable[3], jobId, memory);
			for (LTSTRUCT element : LL_TL_container)
			{
				if (element.jobId == jobId)
				{
					timeLimit = element.timeLimit;
					lineLimit = element.lineLimit;
				}
			}
			char* IR = exec.getIR();
			int PC = exec.getPC();
			int time = 0;
			int line = 0;

			while (1)
			{
				exec.loadIR(exec);
				PC++;

				if (IR[0] == 'P' && IR[1] == 'D')
				{
					time++;
					line++;
					if (line > lineLimit)
					{
						std::cout << "Line limit exceeded" << std::endl;
						break;
					}
					if (exec.putData(outputBuffer) == 1)break;
					std::cout << outputBuffer;
					outputBuffer.clear();
					std::cout << std::endl;
				}
				else if (IR[0] == 'L' && IR[1] == 'R')
				{
					time++;
					if (exec.loadInReg() == 1)break;
				}
				else if (IR[0] == 'S' && IR[1] == 'R')
				{
					time += 2;
					if (exec.storeFromReg() == 1)break;
				}
				else if (IR[0] == 'C' && IR[1] == 'R')
				{
					time++;
					if (exec.compareWithReg() == 1)break;
				}
				else if (IR[0] == 'B' && IR[1] == 'T')
				{
					time++;
					exec.branch(exec);
				}
				else if (IR[0] == 'H')
				{
					time++;
					break;
				}
				// errors
				else {
					std::cout <<"Command: '" << IR[0] <<  IR[1] << "' Opcode error" << std::endl;
					break;
				}

				if (time > timeLimit) {
					std::cout << "Time limit exceeded" << std::endl;
					break;
				}

			}
			break;
		}
		std::cout << "--------------------------------------------------------" << std::endl;
	} while (casevar != -1);
}