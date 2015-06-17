TARGET = MsgSndTest

CFLAGS := -Wall -g -O2 -fPIC

INCLUDE_PATH := -I../Src

LIB_PATH = ../Src/

LIB_FILE := $(LIB_PATH)Msg.a

all:
	$(CC) $(CFLAGS) -o $(TARGET) MsgSndTest.c $(INCLUDE_PATH) $(LIB_FILE) 
	@cp MsgSndTest ../bin 
clean:
	rm  -rf  $(TARGET) *.o 
