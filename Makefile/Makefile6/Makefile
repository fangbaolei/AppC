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

vpath %.c Src
vpath %.h Header

$(TARGET):$(OBJECT)
	cc -o main $(OBJECT)
$(OBJECT):test.h

install:
	cp *.o Install
.PHONY:clean
clean:
	-rm main $(OBJECT)
