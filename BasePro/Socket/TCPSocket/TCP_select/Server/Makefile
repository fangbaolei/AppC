TARGET = Server 
#cross compile
CROSS_COMPILE = 
CC = $(CROSS_COMPILE)gcc
#flags
CFLAGS = -Wall -pthread
#source
SRC = *.c 
#object
OBJECT=$(SRC:.c = .o)
$(TARGET):$(OBJECT)
	@$(CC) -o Server $(OBJECT) $(CFLAGS)
#clean
clean:
	@rm -f Server
