#include "Cryption.hpp"
#include "../processes/Task.hpp"
#include "../fileHandling/ReadEnv.cpp"
#include<string>
#include<iostream>
using namespace std;

int executeCryption(const string &taskData){

    //Creating task object from string representation
    Task task=Task::fromString(taskData);

    //Instance of ReadEnv to read env file
    ReadEnv env;
    
    string envKey=env.getEnv();  
    int key=stoi(envKey);

      
    //Check the action to determine whether to perform Encryption or Decryption
    if(task.action==Action::ENCRYPT){
        char ch;
        //Process each character in file
        while(task.f_stream.get(ch)){
            ch = (ch + key) % 256;
            task.f_stream.seekp(-1,ios::cur);
            task.f_stream.put(ch);          
        }
        task.f_stream.close();
    }else{
        char ch;
        while(task.f_stream.get(ch)){
            ch=(ch-key+256)%256;
            task.f_stream.seekp(-1,ios::cur);
            task.f_stream.put(ch);
        }
        task.f_stream.close();
    }
   
    return 0;
}
