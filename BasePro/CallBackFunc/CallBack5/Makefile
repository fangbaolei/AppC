TARGET = CallBack5
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
	$(CC) -o CallBack5 $(OBJECT) $(CFLAGS)
#clean
clean:
	rm -f CallBack5 
