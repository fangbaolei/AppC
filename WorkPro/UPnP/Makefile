#object
TARGET = upnp
OBJECT=UPnP.o 
#cross compile
CROSS_COMPILE = 
CC = $(CROSS_COMPILE)gcc
#flags
CFLAGS = -Wall 
#install directory
INSTALL_DIR = Install

$(TARGET):$(OBJECT)
	$(CC) -o upnp $(OBJECT) $(CFLAGS)

.PHONY:clean
clean:
	-rm upnp *.o
