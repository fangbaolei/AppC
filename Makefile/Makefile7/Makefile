#target
TARGET = main
#object
OBJECT=main.o test.o
OBJECT+=hello.o
#cross compile
CROSS_COMPILE = 
CC = $(CROSS_COMPILE)gcc
#flags
CFLAGS = -Wall
#install directory
INSTALL_DIR = Install
#path
vpath %.c Src
vpath %.h Header
#make
$(TARGET):$(OBJECT)
$(OBJECT):%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@
#install
install:
	cp *.o $(INSTALL_DIR) 
#clean
.PHONY:clean
clean:
	-rm main $(OBJECT)
