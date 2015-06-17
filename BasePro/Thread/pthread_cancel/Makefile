TARGET = pthread_cancel
#cross compile
CROSS_COMPILE = 
CC = $(CROSS_COMPILE)gcc
#flags
CFLAGS = -Wall -lpthread -g
#source
SRC = *.c 
#object
OBJECT=$(SRC:.c = .o)
$(TARGET):$(OBJECT)
	$(CC) -o pthread_cancel $(OBJECT) $(CFLAGS)
#clean
clean:
	rm -f pthread_cancel 
