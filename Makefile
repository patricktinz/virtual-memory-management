# author Janik und Patrick Tinz
CC = g++

OBJ = Page.o PageTable.o  Statistics.o VirtualMemoryManager.o main.o

# Name des Programms
TARGET = vmm

FLAGS = -g -std=c++11 -Wall -MMD -fmessage-length=0

all: $(TARGET)

#special - "make clean" löscht alle *.o Dateien
clean:
	rm -fv $(OBJ)

%.o : %.cpp
	$(CC) -c $(FLAGS) -o $@ $<

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LIBS)