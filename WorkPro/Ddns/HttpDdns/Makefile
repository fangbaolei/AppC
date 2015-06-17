TARGET = GetExtIp
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
	@$(CC) -o GetExtIp $(OBJECT) $(CFLAGS)
#clean
clean:
	@rm -f GetExtIp
