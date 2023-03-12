#include <string> // for string class
#include <future>
#include <unistd.h>
#include <sys/stat.h>
#include <functional>

#ifndef _FIFO_COMM_CLASS_H_
#define _FIFO_COMM_CLASS_H_

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
    std::function<void()> callback_;    
    bool continue_reading_;
    
}; //FifoComm
} //namespace fifocomm
#endif //_FIFO_COMM_CLASS_H_
