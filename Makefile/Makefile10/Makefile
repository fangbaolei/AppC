#target
TARGET = main
#object
OBJECT=main.o test.o test1.o
#cross compile
CROSS_COMPILE = 
CC = $(CROSS_COMPILE)gcc
#flags
CFLAGS = -Wall 
#install directory
INSTALL_DIR = Install

$(TARGET):$(OBJECT)
	$(CC) -o main $(OBJECT) $(CFLAGS)
%.d:%.c
	set -e; rm -f $@; \
        $(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
        sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
        rm -f $@.$$$$

.PHONY:clean
clean:
	-rm main *.o
