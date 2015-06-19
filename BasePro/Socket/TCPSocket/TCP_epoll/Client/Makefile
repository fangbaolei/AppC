TARGET = Client 

CFLAGS := -Wall -g -O2 -fPIC 

#INCLUDE_PATH := -I../Src

#LIB_PATH = ../Src/

#LIB_FILE := $(LIB_PATH)Msg.a

all:
	#$(CC) $(CFLAGS) -o $(TARGET) TCPClient.c $(INCLUDE_PATH) $(LIB_FILE) 
	$(CC) $(CFLAGS) -o $(TARGET) TCPClient.c 
	@mv Client ../bin 
clean:
	rm  -rf  $(TARGET) *.o 
