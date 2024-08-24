#include<iostream>
#include<boost/filesystem.hpp>
#include<string>
#include<memory>
#include "./src/app/processes/processManagement.hpp"
#include "./src/app/processes/Task.hpp"
namespace fs = boost::filesystem;
using namespace std;

int main(int argc,char *argv[]){
    string directory;         
    string action;
    cout<<"Enter the directory path:";
    getline(cin,directory);

    cout<<"Enter the action (ENCRYPT/DECRYPT):";
    getline(cin,action);

    try{
       
        //Check if directory exists and is a valid directory
        if(fs::exists(directory) && fs::is_directory(directory)){
            
            //Creating instance of process management to handle task processing
            ProcessManagement ProcessManagement;
            
            //Iterating through all files in directory and its sub-directories
            for(const auto &entry: fs::recursive_directory_iterator(directory)){
                if(entry.is_regular_file()){
                    string filePath=entry.path().string();
                    IO io(filePath);
                    fstream f_stream=move(io.getFileStream());
                    if(f_stream.is_open()){
                        Action taskAction=(action=="ENCRYPT"?Action::ENCRYPT:Action::DECRYPT);
                        
                        //Creating a unique task object 
                        unique_ptr<Task> task(new Task(move(f_stream),taskAction,filePath));
                        
                        //Submitting the task to process management instance queue
                        ProcessManagement.submitToQueue(move(task));
                    }else{
                        cout<<"Unable to open the file:"<<filePath<<endl;
                    }
                }
            }
            ProcessManagement.executeTasks();
            cout<<action<<" process is completed.";
        }else{
            cout<<"Invalid directory path\n";
        }
    }catch(const fs::filesystem_error &ex){
        cout<<"Filesystem error:"<<ex.what()<<endl;
    }
    
    return 0;
}