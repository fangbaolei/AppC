TARGET = fftest

CC = gcc
CFLAGS := -Wall -g -O2 -fPIC

LIBDIR = -Llib
INCDIR = -Iinclude

LIB_FILE := -lavcodec
LIB_FILE += -lavformat
LIB_FILE += -lavutil

all:
	$(CC) $(CFLAGS) -o $(TARGET) fftest.c $(INCDIR) $(LIBDIR) $(LIB_FILE)
clean:
	rm  -rf $(TARGET) *.o

