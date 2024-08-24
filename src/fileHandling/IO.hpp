#ifndef IO_HPP
#define IO_HPP

#include<fstream>
#include<string>
#include<iostream>
using namespace std;

//IO class declaration -- Responsible for managing file operations
class IO{
    private:
        //file stream object to handle file reading/writing
        fstream file_stream;                
    public:
         //Constructor: opens the file specified by filePath
        IO(const string &file_path);  

         //Destructor: closes the file when IO object is destroyed -- ensure resources are released after use     
        ~IO();      

         //Getter function to access the file stream             
        fstream getFileStream();  
};         
#endif

