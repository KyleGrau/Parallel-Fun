#include <windows.h>
#include <synchapi.h>
#include <iostream>

struct stuff {
	unsigned int myCounter;
};

DWORD WINAPI myThread(LPVOID lpParameter)
{
	stuff* data = (stuff*)lpParameter;


	while (data->myCounter < 0xFFFFFFFF)
	{
		++data->myCounter;
		if (data->myCounter == 10000)
		{
			std::cout << "Worker thread reached 10,000" << std::endl;;
		}
		else if (data->myCounter == 100000)
		{
			std::cout << "Worker thread reached 100,000" << std::endl;
		}
		else if (data->myCounter == 1000000)
		{
			std::cout << "Worker thread reached 1,000,000" << std::endl;
		}
	}

	std::cout << "Done counting in worker thread..." << std::endl;
	return 0;
}

int main(int argc, char* argv[])
{
	using namespace std;

	//unsigned int myCounter = 0;
	stuff data = {
		0
	};

	
	DWORD myThreadID;
	HANDLE myHandle = CreateThread(0, 0, myThread, &data, 0, &myThreadID);

	if (myHandle == 0)
	{
		cout << "Failed to create thread...";
		return -1;
	}

	unsigned int count = 0;
	unsigned int n = 1;

	while (count <= 3000000000)
	{
		if (count == 1000000)
		{
			cout << "Reached 1,000,000" << endl;
		}
		else if (count == 10000000)
		{
			cout << "Reached 10,000,000" << endl;
		}
		else if (count == 100000000)
		{
			cout << "Reached 100,000,000" << endl;
		}

		++count;
	}

	cout << "Done counting in main thread." << endl;
	WaitForSingleObject(myHandle, INFINITE);

	TerminateThread(myHandle, 0);
	CloseHandle(myHandle);
	return 0;
}