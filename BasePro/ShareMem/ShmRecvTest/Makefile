TARGET = ShmRcvTest


CFLAGS := -Wall -g -O2 -fPIC

INCLUDE_PATH += -I../Src

LIB_PATH = ../Src/

LIB_FILE := $(LIB_PATH)Shm.a

all:
	$(CC) $(CFLAGS) -o $(TARGET) ShmRcvTest.c $(INCLUDE_PATH) $(LIB_FILE) 
	@cp ShmRcvTest ../bin 
clean:
	rm  -rf  $(TARGET) *.o 
