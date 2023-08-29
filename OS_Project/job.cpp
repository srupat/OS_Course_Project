#include"job.h"
#include<iostream>
#include<string>
#include<vector>
Job::Job()
{
	//default constructor
}
void Job::setJobIndex(int Index)
{
	memIndex = Index;
}
void Job::setJobId(std::string inputBuffer)
{
	int t = inputBuffer.find("$AMJ");
	char str_Id[4];
	for (int i = 0; i < 4; i++)
	{
		str_Id[i] = inputBuffer[i + t + 4];
	}
	jobId = std::stoi(str_Id);
}

void Job::getData(std::string inputBuffer, int index, char* startMemAddress)
{
	int t = inputBuffer.find("$DTA");
	int dataIndex = t + 4;
	int i = 0;
	startMemAddress = startMemAddress + 200 + index * 40;
	ptrToData = startMemAddress;
	while (inputBuffer[dataIndex] != '$' && i != 39)
	{	
		char c = inputBuffer[dataIndex];
		ptrToData[i] = inputBuffer[dataIndex];
		dataIndex++;
		i++;
	}
	ptrToData[i] = '\0';
	std::cout << "";

}


//char* Job::getPtrToData(int jobId)
//{
//
//}
//char* Job::getPtrToProg(int jobId)
//{
//
//}