#target
TARLIB = main
#object
OBJECTS=main.o test.o
OBJECTS+=hello.o
#cross compile
CROSS_COMPILE = 
CC = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar
#flags
CFLAGS = -Wall
#install directory
INSTALL_DIR = Install
#path
vpath %.c Src
vpath %.h Header
#make
$(TARLIB).a:$(OBJECTS)
	@$(AR) -r $@ $(OBJECTS)
#install
install:
	cp *.o $(INSTALL_DIR) 
#clean
.PHONY:clean
clean:
	@rm -f main.a $(OBJECTS)
