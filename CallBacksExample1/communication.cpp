#include "communication.hpp"
#include <unistd.h>
#include <fcntl.h>
namespace fifocomm{
	FifoComm::FifoComm(const char* fifo_path_name):fifo_path_name_{fifo_path_name} 
	{}; 
	
	void FifoComm::SetOnReceiveCallback(std::function<void()> callback)
	{
	  callback_ = callback; 	
	}
	
	void FifoComm::FifoStartReceive()
	{
	    mkfifo(fifo_path_name_, 0666);
		fd = open(fifo_path_name_,O_RDWR);
		rx_trhead_ = std::async(std::launch::async, [this](){DataRead();});
		
	}
	
	void FifoComm::DataRead()
	{
		while(1)
		{
			read(fd,&data_[0], 100);
			if(data_[0] == 'a')
			{
				callback_();
			}					
		}
	}
}