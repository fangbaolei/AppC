TARGET = pthread_pool
#cross compile
CROSS_COMPILE = 
CC = $(CROSS_COMPILE)gcc
#flags
CFLAGS = -Wall -lpthread
#source
SRC = *.c 
#object
OBJECT=$(SRC:.c = .o)
$(TARGET):$(OBJECT)
	$(CC) -o pthread_pool $(OBJECT) $(CFLAGS)
#clean
clean:
	rm -f pthread_pool 
