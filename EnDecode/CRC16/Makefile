TARGET = Crc16
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
	$(CC) -o Crc16 $(OBJECT) $(CFLAGS)
#clean
clean:
	rm -f Crc16 
