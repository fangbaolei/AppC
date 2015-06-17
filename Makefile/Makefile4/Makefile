#target
TARGET = main
#object
OBJECT=main.o test.o hello.o
#cross compile
CROSS_COMPILE = 
CC = $(CROSS_COMPILE)gcc
#flags
CFLAGS = -Wall
#install directory
INSTALL_DIR = Install

$(TARGET):$(OBJECT)
	$(CC) -o main $(OBJECT)
$(OBJECT):test.h

.PHONY:clean
clean:
	-rm main $(OBJECT)
