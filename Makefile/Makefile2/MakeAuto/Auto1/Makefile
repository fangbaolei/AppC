#target
TARGET = main
#object
OBJECT=main.o test.o
#cross compile
CROSS_COMPILE = 
CC = $(CROSS_COMPILE)gcc
#flags
CFLAGS = -Wall
#install directory
INSTALL_DIR = Install
#source
SRC = *.c
#make
$(TARGET):$(SRC)
	$(CC) -o $(@) $(^) $(CFLAGS)
#clean
.PHONY:clean 
clean:
	-rm main
