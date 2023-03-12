//build with $ g++ main.cpp communication.cpp -lpthread -o ExampleCallBack

// Example to understand how to register a callback and when it is triggered.
// This program will create a named pipe (fifo) 
// This program will read the fifo
// When the fifo reads a char 'a' it will be triggered a callback
// The receiving methode runs ansyncrhonously and does not block main


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
    fifo_1.StartReceive();
    
    while(1)
    {
        sleep(1);
        printf("main is busy with another stuff \n");
    }
}
