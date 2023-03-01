#include <string> // for string class
#include <future>
#include <unistd.h>
#include <sys/stat.h>

#ifndef _FIFO_COMM_CLASS_
#define _FIFO_COMM_CLASS_
namespace fifocomm{
class FifoComm{

	public:
	
	FifoComm(const char* fifo_path_name);
	void SetOnReceiveCallback(std::function<void()> callback);
	void FifoStartReceive();
	void DataRead();
 			 
    private:
	const char* fifo_path_name_;
	int fd;
	std::future<void> rx_trhead_;
	char data_[100];
	std::function<void()> callback_;	
	
}; //FifoComm
} //namespace fifocomm
#endif //_FIFO_COMM_CLASS_
