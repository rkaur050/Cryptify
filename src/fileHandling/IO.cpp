#include "IO.hpp"

//IO class constructor
IO::IO(const string &file_path){

    //opens the file in input, output and binary mode
    file_stream.open(file_path,ios::in | ios::out | ios::binary);
    
    //Check if the file was successfully opened
    if(!file_stream.is_open()){
        cout<<"Unable to open the file:"<<file_path<<endl;
    }
}

//getFileStream method
//Returns the file stream object by moving it, transfering ownership
fstream IO::getFileStream(){
    return move(file_stream);
}

//IO class destructor
//Ensure that the file stream is properly closed before attempting to close it.
IO::~IO(){
    
    //Check if the file stream is still opened -- close it to release resources
    if(file_stream.is_open()){
        file_stream.close();               
    }
}