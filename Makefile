CXX = clang++
CXXFLAGS= -std=c++11 -g -Wall  -I src/app/encryptDecrypt -I src/app/fileHandling -I src/app/processes
BOOST_LIBS = -lboost_filesystem -lboost_system

MAIN_TARGET = encrypt_decrypt
CRYPTION_TARGET= cryption

MAIN_SRC= main.cpp \
		  src/app/processes/processManagement.cpp \
		  src/app/fileHandling/IO.cpp \
		  src/app/fileHandling/ReadEnv.cpp \
		  src/app/encryptDecrypt/Cryption.cpp 
		
CRYPTION_SRC = src/app/encryptDecrypt/CryptionMain.cpp \
				src/app/encryptDecrypt/Cryption.cpp \
				src/app/fileHandling/IO.cpp \
				src/app/fileHandling/ReadEnv.cpp
			
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)
CRYPTION_OBJ = $(CRYPTION_SRC:.cpp=.o)

all: $(MAIN_TARGET) $(CRYPTION_TARGET)

$(MAIN_TARGET): $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $(MAIN_OBJ) $(BOOST_LIBS) -o $(MAIN_TARGET)

$(CRYPTION_TARGET) : $(CRYPTION_OBJ)
	$(CXX) $(CXXFLAGS) $(CRYPTION_OBJ) $(BOOST_LIBS) -o $(CRYPTION_TARGET) 

%.o: %.cpp 
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean: 
	rm -f $(MAIN_OBJ) $(CRYPTION_OBJ) $(MAIN_TARGET) $(CRYPTION_TARGET) 

.PHONY: clean all	