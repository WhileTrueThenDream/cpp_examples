//build with $ g++ main.cpp communication.cpp -lpthread
//Draft

#include "communication.hpp"

const char* fifo_path{"/tmp/my_fifo"};
using namespace fifocomm;

void PrintReceivedData()
{
	printf("Event: 'a' received...some action .... \n");
}

int main()
{
	FifoComm fifo_1(fifo_path);
	fifo_1.SetOnReceiveCallback([](){PrintReceivedData();});
	fifo_1.FifoStartReceive();
	
	while(1)
	{
		sleep(2);
		printf("main is busy with another stuff \n");
	}
}


