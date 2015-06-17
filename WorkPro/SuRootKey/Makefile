TARGET = SuRootKey
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
	@$(CC) -o SuRootKey $(OBJECT) $(CFLAGS)
#clean
clean:
	@rm -f SuRootKey
