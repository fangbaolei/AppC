TARGET = pthread_join
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
	$(CC) -o pthread_join $(OBJECT) $(CFLAGS)
#clean
clean:
	rm -f pthread_join 
