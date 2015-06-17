#target
TARGET = main
#objects
#找出当前目录下所有的.c文件
CSOURCE:=$(shell find . -type f -name "*.c")
#生成.c文件对应的.o文件
OBJECT:=$(subst .c,.o,$(CSOURCE))

#cross compile
CROSS_COMPILE = 
CC = $(CROSS_COMPILE)gcc
#flags
CFLAGS = -Wall 
#install directory
INSTALL_DIR = Install

$(TARGET):$(OBJECT)
	$(CC) -o main $(OBJECT) $(CFLAGS)
main.o:test.h

.PHONY:clean
clean:
	-rm main *.o
