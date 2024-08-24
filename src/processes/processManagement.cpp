#include "processManagement.hpp"
#include<iostream>
#include<string>
#include<sys/mman.h>
#include<unistd.h>                                                                                      
#include<sys/mman.h>
#include<fcntl.h>                         //for file descriptor operations
#include "../encryptDecrypt/Cryption.hpp"
using namespace std; 
 
ProcessManagement::ProcessManagement(){

    //named semaphores are required for inter-process communication
    //here, between different child processes of the parent process

    //initially, the there is no task in the queue
    taskCountSemaphore=sem_open("/taskCount_semaphore", O_CREAT,0);

    //initially, the queue is empty
    emptySemaphore=sem_open("/empty_sempaphore",O_CREAT,10);

    //Opening or Creating shared memory object
    //Shared memory object handled by shared file descriptor
    sharedFd=shm_open(sharedMemName, O_CREAT | O_RDWR);
    //setting the size of sharedMemory object to  accomodate instance of sharedMemory structure
    ftruncate(sharedFd,sizeof(sharedMemory));
    //mapping the shared memory object into process's address space
    //allowing processes to read or write to shared memory
    sharedMem=static_cast<sharedMemory *>(mmap(nullptr,sizeof(sharedMemory),
    PROT_READ | PROT_WRITE, MAP_SHARED,sharedFd,0));
    sharedMem->front=0;
    sharedMem->rear=0;
    sharedMem->size.store(0);

};

bool ProcessManagement::submitToQueue(unique_ptr<Task> task){

    //before adding task to the queue, checking if its empty or not
    sem_wait(emptySemaphore);
    unique_lock<mutex>lock(queueLock);
    
    //ensure the queue is not full before adding the new task
    if(sharedMem->size.load()>=10){
        return false;
    }
    //copying the task string in the queue
    //sharedMem->rear points to the new slot where the string will be added in the tasks queue
    strcpy(sharedMem->tasks[sharedMem->rear], task->toString().c_str());
    sharedMem->rear=(sharedMem->rear+1)%10;
    sharedMem->size.fetch_add(1);

    lock.unlock();
    sem_post(taskCountSemaphore);

    int pid=fork();
    if(pid<0){
        return false;
    }else if(pid==0){
        executeTasks();
        exit(0);
    }
    return true;
}

void ProcessManagement::executeTasks(){
    
    //before executing tasks, check if there is a task in queue or not
    sem_wait(taskCountSemaphore);
    unique_lock<mutex>lock(queueLock);

    //char array to store the string present in the task at front of queue
    char taskStr[256];
    //copying the string in task to taskStr
    strcpy(taskStr,sharedMem->tasks[sharedMem->front]);
    //updating front & size of queue
    sharedMem->front=(sharedMem->front+1)%10;
    sharedMem->size.fetch_sub(1);

    lock.unlock();
    sem_post(emptySemaphore);

    executeCryption(taskStr);

}

ProcessManagement::~ProcessManagement(){

    //removing the shared region from the process's address space
    //to ensure resources are properly leaved
    munmap(sharedMem,sizeof(sharedMemory));

    //removing the name of shared memory object from the file system
    //shared memory object will be destroyed and its resources will be freed
    shm_unlink(sharedMemName);
}

/*shm_open() opens or creates the shared memory object with the specified name and access mode.
ftruncate() sets the size of this shared memory object to accommodate the sharedMemory structure.
The file descriptor sharedFd will be used later to map this memory object to the process's address space.
*/