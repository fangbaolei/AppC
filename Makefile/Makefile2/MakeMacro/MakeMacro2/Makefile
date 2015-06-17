#target
TARGET = main
#cross compile
CROSS_COMPILE = 
CC = $(CROSS_COMPILE)gcc
#flags
CFLAGS = -Wall
#install directory
INSTALL_DIR = Install
#source
SRC = *.c
#object
OBJECT=$(SRC:.c = .o)
$(TARGET):$(OBJECT)
	$(CC) -o main $(OBJECT) $(CFLAGS)

install:
	cp -vf *.o $(INSTALL_DIR)

clean:
	-rm main 
