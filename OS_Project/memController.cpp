#include"memController.h"
#include <string>
#include <random>
MemoryController::MemoryController()
{
	//Initialise an array of int to mark the position of the job into the page table 

	pageTableToJobMap = new int[5];
	for (int i = 0; i < 5; i++) {
		pageTableToJobMap[i] = -1;
	}

	//Initialize an Array to keep the track of the frames occupied.

	occupiedMemFrames = new int[20];
	for (int i = 0; i < 20; i++) {
		occupiedMemFrames[i] = 0;
	}
}

int MemoryController::getEmptyPageTable()
{
	for (int i = 0; i < 5; i++)
	{
		if (pageTableToJobMap[i] == -1)
		{
			return i;
		}
	}
	return -1;
}

int MemoryController::getJobId(std::string inputBuffer)
{
	int startOfProgram = inputBuffer.find("$AMJ");
	char buffer[5];
	int jobId{};
	for (int i = startOfProgram + 4; i < startOfProgram + 8; i++)
	{
		int bufferIndex = i - startOfProgram - 4;
		buffer[bufferIndex] = inputBuffer[i];
	}
	buffer[4] = 0;
	jobId = std::stoi(buffer);
	return jobId;
}



void MemoryController::setJobId(int jobId, int pageTableIndex)
{
	pageTableToJobMap[pageTableIndex] = jobId;
}

int random_integer_0_to_19() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 19);
	return dis(gen);
}


void MemoryController::generateFrames(PageDirectory& pageDir, int pageTableIndex)
{
	int randomInt{};
	int pageIndex{};
	int* ptrToPageTable = pageDir.ptrToPageDirectory + pageTableIndex * 4;
	for (int i = 0; i < 4; i++)
	{
		do
		{
			randomInt = random_integer_0_to_19();
		} while (occupiedMemFrames[randomInt] != 0);
		ptrToPageTable[pageIndex] = randomInt;
		pageIndex++;
	}
}

void MemoryController::pushInstructions(int jobId, PageDirectory& pageDir, Memory& memory, std::string inputBuffer)
{

	int pageTableIndex{};
	int programIndex{};
	char* ptrToFirstPage{ NULL };
	char* ptrToSecondPage{ NULL };
	for (int i = 0; i < 5; i++)
	{
		if (pageTableToJobMap[i] == jobId)
		{
			pageTableIndex = i;
			break;
		}
	}
	int* ptrToPageTable = pageDir.ptrToPageDirectory + pageTableIndex * 4;
	int instruction{ 1 };
	int label{ 1 };
	ptrToFirstPage = memory.ptrToMemory + ptrToPageTable[0] * 40;
	ptrToSecondPage = memory.ptrToMemory + ptrToPageTable[1] * 40;
	programIndex = inputBuffer.find('\n');
	while (inputBuffer[programIndex] != '*')
	{	
		programIndex++;
		if (inputBuffer[programIndex] == 'L' && std::isdigit(inputBuffer[programIndex + 1]))
		{
			// label
			std::string l_buffer;
			while (inputBuffer[programIndex] != '\n')
			{
				
				l_buffer += inputBuffer[programIndex];
				programIndex++;
				
			}
			l_buffer.erase(0, 2);
			for (int i = 0; i < l_buffer.length(); ++i) {
				if (l_buffer[i] == ',') {
					l_buffer.erase(i, 1); // Erase 1 character at position i
					--i; // Decrement i to account for the removed character
				}
			}
			for (int i = 0; i < l_buffer.size(); i++)
			{
				ptrToSecondPage[39 - label*4 + i] = l_buffer.at(i);
			}
			label++;
			
		}
		else
		{
			// Instruction
			std::string i_buffer;
			if (inputBuffer[programIndex] == '*')
			{
				break;
			}
			while (inputBuffer[programIndex] != '\n')
			{
				
				i_buffer += inputBuffer[programIndex];	
				programIndex++;
				
			}
			if (i_buffer == "H")
			{
				for (int i = 1; i < 4; i++)
				{
					i_buffer += ' ';
				}
			}
			else
			{
				for (size_t i = 0; i < i_buffer.length(); ++i) {
					if (i_buffer[i] == ' ') {
						i_buffer.erase(i, 1); // Erase 1 character at position i
						--i; // Decrement i to account for the removed space
					}
				}
			}
			if (instruction <= 10)
			{
				for (int i = 0; i < 4; i++)
				{
					ptrToFirstPage[i] = i_buffer.at(i);
				}
				ptrToFirstPage = ptrToFirstPage + 4;
				instruction++;
			}
			else
			{
				for (int i = 0; i < 4; i++)
				{
					ptrToSecondPage[i] = i_buffer.at(i);
				}
				ptrToSecondPage = ptrToSecondPage + 4;
				instruction++;
			}
			
		}
	}
}

void MemoryController::printFrame(int frame, Memory& memory)
{
	int wordCount{ 10 };
	char* framePtr = memory.ptrToMemory + frame * 40;
	while (wordCount != 0)
	{
		for (int i = 0; i < 4; i++)
		{
			std::cout << " " << framePtr[i] << " ";
		}
		framePtr = framePtr + 4;
		std::cout << std::endl;
		wordCount--;
	}
}

void MemoryController::pushData(int jobId, PageDirectory& pageDir, Memory& memory, std::string inputBuffer)
{

	int pageTableIndex{};
	int dataIndex{};
	char* ptrToThirdPage{ NULL };
	char* ptrToFourthPage{ NULL };
	for (int i = 0; i < 5; i++)
	{
		if (pageTableToJobMap[i] == jobId)
		{
			pageTableIndex = i;
			break;
		}
	}
	int* ptrToPageTable = pageDir.ptrToPageDirectory + pageTableIndex * 4;
	int dataCount{};
	ptrToThirdPage = memory.ptrToMemory + ptrToPageTable[2] * 40;
	ptrToFourthPage = memory.ptrToMemory + ptrToPageTable[3] * 40;
	dataIndex = inputBuffer.find("$DTA") + 5;
	while (inputBuffer[dataIndex + dataCount] != '*' )
	{
		if (inputBuffer[dataIndex + dataCount] != '\n')
		{
			char c = inputBuffer[dataIndex + dataCount];
			if (dataCount <= 40)
				ptrToThirdPage[dataCount] = inputBuffer[dataIndex + dataCount];

			else
				ptrToFourthPage[dataCount] = inputBuffer[dataIndex + dataCount];
			dataCount++;
		}
		else
		{
			dataIndex++;
		}
	}
	
}

int MemoryController::getPageTableIndex(int jobId)
{
	for (int i = 0; i < 5; i++)
	{
		if (pageTableToJobMap[i] == jobId)
		{
			return i;
		}
	}
	return -1;
}

int MemoryController::getLineLimit(std::string inputBuffer)
{
	
	int start = inputBuffer.find("$AMJ");
	char buffer[5];
	int lineLimit{};
	for (int i = start + 12; i < start + 16; i++)
	{
		int bufferIndex = i - start - 12;
		buffer[bufferIndex] = inputBuffer[i];
	}
	buffer[4] = 0;
	lineLimit = std::stoi(buffer);
	return lineLimit;
}

int MemoryController::getTimeLimit(std::string inputBuffer)
{
	
	int start = inputBuffer.find("$AMJ");
	char buffer[5];
	int timeLimit{};
	for (int i = start + 8; i < start + 12; i++)
	{
		int bufferIndex = i - start - 8;
		buffer[bufferIndex] = inputBuffer[i];
	}
	buffer[4] = 0;
	timeLimit = std::stoi(buffer);
	return timeLimit;
}
int MemoryController::outOfData(std::string inputBuffer)
{
	int dataPos = inputBuffer.find("$DTA");
	
	if (inputBuffer[dataPos + 4] == '$') return 1;
	else return 0;
}