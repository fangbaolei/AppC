TARGET = pthread_mutex_t
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
	@$(CC) -o pthread_mutex_t $(OBJECT) $(CFLAGS)
#clean
clean:
	@rm -f pthread_mutex_t
