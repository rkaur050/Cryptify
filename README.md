# Cryptify - File Encryption/Decryption System

## Project Overview

**Cryptify** is a C++ application that provides a robust solution for encrypting and decrypting files. It utilizes character-wise transformation for encryption and decryption, and incorporates process synchronization with semaphores and shared memory to efficiently manage multiple file operations concurrently.

## Features

- **File Handling**: Efficient file operations using a custom `IO` class.
- **Concurrent Task Management**: Uses shared memory and semaphores to handle multiple encryption/decryption tasks simultaneously.
- **Encryption/Decryption**: Supports character-wise encryption and decryption based on a key read from an environment file.
- **Recursive Directory Processing**: Traverses directories and processes all files within them.


## How It Works

1. **User Input**:
   - The user is prompted to provide a directory path and an action (ENCRYPT or DECRYPT).

2. **Directory Traversal**:
   - The application recursively scans the provided directory and its sub-directories for files.

3. **Task Creation**:
   - For each file, a task is created with the specified action and file path. The task is submitted to the process queue.

4. **Task Processing**:
   - Tasks are processed concurrently using shared memory and semaphores. Each task is handled by a separate process.

5. **File Encryption/Decryption**:
   - The `Cryption` class performs the actual encryption or decryption based on the action specified.


## Dependencies
1. **Boost Filesystem Library**: For directory traversal.
2. **Clang++**: For compiling the C++ code.


## Classes and Files
1. **IO Class**: 
    - Manages file input/output operations.
2. **ReadEnv Class**: 
    - Reads the .env file to retrieve the encryption/decryption key.
3. **Task Class**: 
    - Represents a task for file encryption or decryption.
4. **ProcessManagement Class**: H
    - Handles task submission and execution using shared memory and semaphores.
5. **Cryption Functions**: 
    - Performs the actual encryption and decryption operations.
6. **Environment File**:
    - The .env file should contain a single integer value representing the encryption/decryption key.


# Python Script
The makeFiles.py script generates a set of test files in a specified directory.

## How to Run

1. Clone the repository
2. Navigate to the project directory
3. Compile the project with command - **make**
4. Run the main application with command - **./encrypt_decrypt**
5. Provide Inputs:
    - Enter the directory path where the files to be processed are located.
    - Enter the action (ENCRYPT or DECRYPT) based on the desired operation.
6. Run the Cryption Executable (for single files): **./cryption "file_path,ENCRYPT"**
    - Replace file_path with the path of the file you want to process.
    - Replace ENCRYPT with DECRYPT if you want to perform decryption.


