# Cryptify - File Encryption/Decryption System

## Project Overview

**Cryptify** is a C++ application that provides a robust solution for encrypting and decrypting files. It utilizes character-wise transformation for encryption and decryption, and incorporates process synchronization with semaphores and shared memory to efficiently manage multiple file operations concurrently.

## Features

- **File Handling**: Efficient file operations using a custom `IO` class.
- **Concurrent Task Management**: Uses shared memory and semaphores to handle multiple encryption/decryption tasks simultaneously.
- **Encryption/Decryption**: Supports character-wise encryption and decryption based on a key read from an environment file.
- **Recursive Directory Processing**: Traverses directories and processes all files within them.

## Project Structure

├── src
│   ├── encryptDecrypt
│   |   ├── Cryption.cpp
│   │   └── CryptionMain.cpp
│   ├── fileHandling
│   │   ├── IO.cpp
│   │   └── ReadEnv.cpp
│   └── processes
│       ├── ProcessManagement.cpp
│       └── Task.cpp
├── main.cpp
├── .gitignore
├── makeFiles.py
├── Makefile
└── README.md

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




