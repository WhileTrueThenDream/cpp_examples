#include <string> // for string class
#include <future>
#include <unistd.h>
#include <sys/stat.h>

#ifndef _FIFO_COMM_CLASS_
#define _FIFO_COMM_CLASS_

namespace fifocomm{

 constexpr unsigned char num_bytes = 100;

class FifoComm{

	public:
	
	FifoComm(const char* fifo_path_name);
	~FifoComm();
	void SetOnReceiveCallback(std::function<void()> callback);
	void StartReceive();
	void DataRead();
 			 
    private:

	const char* fifo_path_name_;
	int fd;
	std::future<void> rx_trhead_;
	char data_[num_bytes];
	std::function<void()> callback_;	
	bool continue_reading_;
	
}; //FifoComm
} //namespace fifocomm
#endif //_FIFO_COMM_CLASS_
