#target
TARLIB = main
#object
OBJECTS=main.o test.o
OBJECTS+=hello.o
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
$(TARLIB).so:$(OBJECTS)
	$(CC) -shared -o $(TARLIB).so $(OBJECTS)
#install
install:
	cp *.o $(INSTALL_DIR) 
#clean
.PHONY:clean
clean:
	-rm main.so $(OBJECTS)
