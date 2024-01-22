#include"exeUnit.h"
#include <string>


ExecutionUnit::ExecutionUnit(int Page0, int Page1, int Page2, int Page3, int jobId, Memory& memory)
{
	char* ptrToMem = memory.getPtrToMem();
	lineCount = 0;
	GPR = (char*)malloc(sizeof(char) * 4);
	IR = (char*)malloc(sizeof(char) * 4);
	PC = 0;
	controlFlag = 0;
	job.jobID = jobId;
	job.pg0 = ptrToMem + 40 * Page0;
	job.pg2 = ptrToMem + 40 * Page2;
	job.pg1 = ptrToMem + 40 * Page1;
	job.pg3 = ptrToMem + 40 * Page3;
	temp = job.pg0;
}



void ExecutionUnit::loadIR(ExecutionUnit& exec)
{
	for (int i = 0; i<4;i++)
	{
		char c = exec.temp[i];
		IR[i] = exec.temp[i];
	}
	IR[4] = '\0';
	exec.temp = exec.temp + 4;
}

int ExecutionUnit::putData(std::string& outputBuffer)
{
	int labelNo = IR[3] - 48; // ir is in char
	if (operandError(labelNo)) {
		std::cout << "operand error";
		return 1;
	}
	int labelStartIndex = 40;
	labelStartIndex = 40 - (labelNo + 1) * 4;
	char* temp = job.pg1;
	temp = temp + labelStartIndex;
	std::string buffer;
	for (int i = 0; i < 2; i++)
	{
		buffer += temp[i];
	}
	int tillData = std::stoi(buffer);
	buffer.clear();
	for (int i = 2; i < 4; i++)
	{
		buffer += temp[i];
	}
	int length = std::stoi(buffer);

		int dataIndex = tillData;
		if (dataIndex < 39)
		{
			// page 2 
			while (length > 0)
			{
				char c = job.pg2[dataIndex];
				outputBuffer += job.pg2[dataIndex];
				length--;
				dataIndex++;
			}
		}

		else if (dataIndex > 41)
		{
			while (length > 0)
			{
				// page 3
				outputBuffer += job.pg3[dataIndex];
				length--;
				dataIndex++;
			}
		}
		return 0;
		// to handle the else part where the data lies in between the 2 pages
}

int ExecutionUnit::loadInReg()
{
	int labelNo = IR[3] - 48; // ir is in char
	if (operandError(labelNo)) {
		std::cout << "operand error : label " << labelNo << " not found " << std::endl;
		return 1;
	}
	int labelStartIndex = 40;
	int dataCount{ 4 };
	labelStartIndex = 40 - (labelNo+1) * 4;
	char* temp = job.pg1;
	temp = temp + labelStartIndex;
	std::string buffer;
	for (int i = 0; i < 2; i++)
	{
		buffer += temp[i];
	}
	int tillData = std::stoi(buffer);
	buffer.clear();
	for (int i = 2; i < 4; i++)
	{
		buffer += temp[i];
	}
	int length = std::stoi(buffer);
	GPR.clear();

	int dataIndex = tillData;
	if (dataIndex < 39)
	{
		// page 2 
		while (length > 0)
		{
			if (dataCount > 0)
			{
				char c = job.pg2[dataIndex];
				GPR += job.pg2[dataIndex];
				length--;
				dataIndex++;
				dataCount--;
			}
			else
				return 0;
		}
	}
	else if (dataIndex > 41)
	{
		while (length > 0)
		{
			// page 3
			if (dataCount > 0)
			{
				char c = job.pg3[dataIndex];
				GPR += job.pg2[dataIndex];
				length--;
				dataIndex++;
			}
			else
				return 0;
		}
	}
	return 0;
}

int ExecutionUnit::storeFromReg()
{
	int labelNo = IR[3] - 48; // ir is in char
	if (operandError(labelNo)) {
		std::cout << "operand error";
		return 1;
	}
	int labelStartIndex = 40;
	int dataCount{ 4 };
	int count{};
	labelStartIndex = 40 - (labelNo + 1) * 4;
	char* temp = job.pg1;
	temp = temp + labelStartIndex;
	std::string buffer;
	for (int i = 0; i < 2; i++)
	{
		buffer += temp[i];
	}
	int tillData = std::stoi(buffer);
	buffer.clear();
	for (int i = 2; i < 4; i++)
	{
		buffer += temp[i];
	}
	int length = std::stoi(buffer);
	//GPR.clear();

	int dataIndex = tillData;
	if (dataIndex < 39)
	{
		// page 2 
		while (length > 0)
		{
			if (dataCount > 0)
			{
				char c = GPR[count];
				job.pg2[dataIndex] = c;
				length--;
				dataIndex++;
				dataCount--;
				count++;
			}
			else
				return 0;
		}
	}
	else if (dataIndex > 41)
	{
		while (length > 0)
		{
			// page 3
			if (dataCount >= 0)
			{
				char c = GPR[count];
				job.pg2[dataIndex] = c;
				length--;
				dataIndex++;
			}
			else
				return 0;
		}
	}
	
}


int ExecutionUnit::compareWithReg()
{
	int labelNo = IR[3] - 48; // ir is in char
	if (operandError(labelNo)) {
		std::cout << "operand error";
		return 2;
	}
	int labelStartIndex = 40;
	labelStartIndex = 40 - (labelNo + 1) * 4;
	char* temp = job.pg1;
	temp = temp + labelStartIndex;
	std::string buffer;
	std::string cmpBuffer;
	for (int i = 0; i < 2; i++)
	{
		buffer += temp[i];
	}
	int tillData = std::stoi(buffer);
	buffer.clear();
	for (int i = 2; i < 4; i++)
	{
		buffer += temp[i];
	}
	int length = std::stoi(buffer);
	for (int i = 0; i < 39; i++) // 39 coz last char is some special character
	{
		int dataIndex = tillData + i;
		if (dataIndex < 39)
		{
			// page 2 
			while (length > 0)
			{
				char c = job.pg2[dataIndex];
				cmpBuffer += job.pg2[dataIndex];
				length--;
				dataIndex++;
			}
		}
		else if (dataIndex > 41)
		{
			while (length >= 0)
			{
				// page 3
				cmpBuffer += job.pg3[dataIndex];
				length--;
				dataIndex++;
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (GPR[i] != cmpBuffer.at(i))
		{
			controlFlag = 0;
			return controlFlag;
		}
		else
		{
			controlFlag = 1;
		}
	}
	return controlFlag;
}

void ExecutionUnit::branch(ExecutionUnit& exec)
{
	// this instruction will jump labels
	// ir is in char
	if (exec.controlFlag == 1)
	{
		std::string buffer;
		for (int i = 2; i < 4; i++)
		{
			buffer += IR[i];
		}
		int instructionNo = std::stoi(buffer);
		exec.temp = job.pg0 + instructionNo * 4;
	}
}





int ExecutionUnit::operandError(int labelNo)
{
	int flag = 0;
	int var = IR[3] - 48;


	int dataLimit = 40;
	for (int i = 39; i > 0; i--)
	{
		if (! std::isdigit(job.pg1[i])) break;
		dataLimit--;
	}

	dataLimit = 10 - (dataLimit / 4);
	if (dataLimit < labelNo)
	{
		return 1;
	}
	if (IR[2] != 'L')
	{
		if (var < 49 || var>57)
		{
			flag = 1;
		}
	}
	int num = IR[3] - 48;
	if (num < 0 || num>dataLimit) flag = 1; // if we want valid numeric value, just add num>9
	return flag;
}
