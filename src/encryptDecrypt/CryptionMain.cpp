#include<iostream>
#include "Cryption.hpp"
using namespace std;

// To perform encryption or decryption of a specified file
// based on a command-line argument. 

int main(int argc, char* argv[]){
    if(argc!=2){
        cerr<<"Usage ./cryption <task_data>"<<endl;
        return 1;
    }
    // argv[1] is the command-line argument passed by the user
    executeCryption(argv[1]);
    return 0;
}

// Sample Input:
// To run the program, use the following command-line format:
// ./cryption "example.txt,ENCRYPT"