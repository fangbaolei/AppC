TARGET = EpollServer
#cross compile
CROSS_COMPILE = 
CC = $(CROSS_COMPILE)gcc
#flags
CFLAGS = -Wall
#source
SRC = *.c 
#object
OBJECT=$(SRC:.c = .o)
$(TARGET):$(OBJECT)
	$(CC) -o EpollServer $(OBJECT) $(CFLAGS)
#clean
clean:
	rm -f EpollServer 
