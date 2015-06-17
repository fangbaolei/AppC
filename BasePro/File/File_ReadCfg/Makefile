TARGET = ReadCfgFile 
#cross compile
CROSS_COMPILE = 
CC = $(CROSS_COMPILE)gcc
#flags
CFLAGS = -Wall
#CFLAGS = 
#source
SRC = *.c 
#object
OBJECT=$(SRC:.c = .o)
$(TARGET):$(OBJECT)
	$(CC) -o ReadCfgFile $(OBJECT) $(CFLAGS)
#clean
clean:
	rm -f ReadCfgFile 
