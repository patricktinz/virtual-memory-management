# author Janik und Patrick Tinz
CC = g++

OBJ = Page.o PageTable.o  Statistics.o VirtualMemoryManager.o main.o

# program name
TARGET = vmm

FLAGS = -g -std=c++14 -Wall -MMD -fmessage-length=0

all: $(TARGET)

# "make clean" delete all *.o files
clean:
	rm vmm $(OBJ)

%.o : %.cpp
	$(CC) -c $(FLAGS) -o $@ $<

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)