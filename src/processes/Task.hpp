#ifndef TASK_HPP
#define TASK_HPP

#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include "../fileHandling/IO.hpp"


//enum class to define actions that can be performed on file
enum class Action{
    ENCRYPT,
    DECRYPT
};


//Used to define the operation that is to be performed on file
struct Task{
    std::string filePath;
    std::fstream f_stream;
    Action action;

    //SERIALIZATION
    //Constructor - Initializes the task with the file Path , file stream and action
    Task(std::fstream &&stream,Action act,std::string filePath){
        f_stream=std::move(stream);
        action=act;
        this->filePath=filePath;
    }

    //Method to create string representation of Task object
    std::string toString(){   

        //Adding file Path and action to ostringstream          
        std::ostringstream oss;
        oss<<filePath<<","<<(action==Action::ENCRYPT?"ENCRYPT":"DECRYPT");
        
        //Returning final string from ostringstream
        // filePath -> test.txt & action = encrypt  --> return "test.txt,enrcypt"
        return oss.str();
    }
    
    //DESERIALIZATION
    //Method to create task object from string representation
    //Static Method as no instance specific job is not being done - can be called on class itself
    static Task fromString(const std::string &taskData){
        
        //iss object to parse string
        std::istringstream iss(taskData);       
        std::string filePath;
        std::string actionStr;

        //parsing file path and action from the string
        if(getline(iss,filePath, ',') && getline(iss,actionStr)){
            Action action=(actionStr=="ENCRYPT"?Action::ENCRYPT:Action::DECRYPT);
            
            //Creating IO object to manage file operations
            IO io(filePath);
            std::fstream f_stream=std::move(io.getFileStream());

            //If file opened create and return Task object
            if(f_stream.is_open()){
                return Task(std::move(f_stream),action,filePath);
            }else{
                throw std::runtime_error("Faild to open file:"+filePath);
            }
        }else{
            throw std::runtime_error("Invalid task data format");
        }
    }

};

#endif