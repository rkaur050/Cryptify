#ifndef PROCESS_MANAGEMENT_HPP
#define PROCESS_MANAGEMENT_HPP

#include"Task.hpp"
#include<memory>
#include<atomic>
#include<semaphore.h>
#include<mutex>

class ProcessManagement{
    private:
       
       //for synchronization between threads
       sem_t *taskCountSemaphore;
       sem_t *emptySemaphore;
       mutex queueLock;

       //sharedMemory to store the task queue
       struct sharedMemory{

            //atomic to avoid race conditions
            atomic<int>size;
            
            //a queue to store 10 tasks(files) each of 256 bytes
            char tasks[10][256];
            int front;
            int rear;
       };

        //pointer to point to an instance of sharedMemory
        sharedMemory *sharedMem;
        //shared file descriptor for the shared object
        int sharedFd;
        //sharedMemory object name
        const char *sharedMemName="task_queue";
        
    public:
        ProcessManagement();
        ~ProcessManagement();

        //Method to submit task to queue by taking ownership of task
        bool submitToQueue(unique_ptr<Task>task);
    
        void executeTasks();
};


#endif