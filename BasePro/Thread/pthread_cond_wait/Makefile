TARGET = pthread_cond_wait
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
	$(CC) -o pthread_cond_wait $(OBJECT) $(CFLAGS)
#clean
clean:
	rm -f pthread_cond_wait 
