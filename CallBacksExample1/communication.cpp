#include "communication.hpp"
#include <unistd.h>
#include <fcntl.h>
#include <functional>

namespace fifocomm{
    FifoComm::FifoComm(const char* fifo_path_name):fifo_path_name_{fifo_path_name} ,continue_reading_{true}
    {
        mkfifo(fifo_path_name_, 0666);
        fd = open(fifo_path_name_,O_RDWR);    
    } 

    FifoComm::~FifoComm()
    {
       close(fd);
       remove(fifo_path_name_);
       continue_reading_ = false; //thread must finish so destructor destroys object. 

       printf("Destructor called \n");
    } 
    
    void FifoComm::SetOnReceiveCallback(std::function<void()> callback)
    {
      callback_ = callback; //TODO: check not null ptr. 
    }
    
    // The reception is asyncrhonous to not block main programm execution
    void FifoComm::StartReceive()
    {
        rx_trhead_ = std::async(std::launch::async, [this](){DataRead();}); //TODO: catch exceptions
        
    }
    
    //The callback will be triggered when an 'a' is received. 
    void FifoComm::DataRead()
    {
        while(continue_reading_)
        {
            read(fd,&data_[0], num_bytes); //this operation is blocking 
            if(data_[0] == 'a')
            {
                callback_();
            }                    
        }
    }
}
