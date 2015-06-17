TARGET = DbBackup
#cross compile
#CROSS_COMPILE = arm-hisiv200-linux- 
#CC = $(CROSS_COMPILE)gcc
CC = arm-hisiv200-linux-gcc
#flags
CFLAGS = -Wall -lsqlite3
#source
SRC = *.c 
#object
OBJECT=$(SRC:.c = .o)
$(TARGET):$(OBJECT)
	@$(CC) -o DbBackup $(OBJECT) $(CFLAGS)
#clean
clean:
	@rm -f DbBackup 
