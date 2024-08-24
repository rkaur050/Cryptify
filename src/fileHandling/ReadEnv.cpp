#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include "IO.hpp"
using namespace std;


//Class responsible for reading content of .env file
class ReadEnv{
    public:

        //Method to read the contents of .env file and return it as a  string
        string getEnv(){
            string env_path=".env";

            //IO object to handle file operations on env file
            IO io(env_path);

            //Get the file stream by moving it from IO object 
            fstream f_stream=io.getFileStream();
            
            //buffer to read the entire content of file stream
            stringstream buffer;
            buffer<<f_stream.rdbuf();

            //convert buffer content to string
            string content=buffer.str();
            return  content;
        }
};