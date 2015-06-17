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

$(TARGET):$(OBJECT)
$(OBJECT):%.o:%.c
	$(CC) -c $(CFLAGS) $(^) -o $(@)

.PHONY:clean 
clean:
	rm -f main *.o
