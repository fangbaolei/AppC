TARGET=P2P_FreeIp 
LINKS= -L./ #这一行表示所需要的动态库得要放在root的lib下面。当然这一行你可以改变路径改成自己想要的路径。
P2P_FreeIp_objs = P2P_FreeIp.o


all: $(TARGET)

clean:
	rm -f *.o
	rm -f $(TARGET)


CFLAGS  =  -c -g0 $(COMPILER_FLAGS)  -Wall -O2
DFLAGS  =  -DVERSION=\"$(VERSION)\"
LFLAGS = -lpthread libserversdk.a -lsqlite3
#LFLAGS = -lpthread -lsqlite3
DEP_INCS =

P2P_FreeIp.o:         P2P_FreeIp.c   $(DEP_INCS)
#	arm-hisiv100nptl-linux-gcc $(CFLAGS) $(INCS) $(DFLAGS)   $^
	arm-hisiv200-linux-gcc $(CFLAGS) $(INCS) $(DFLAGS)   $^
#	arm-none-linux-gnueabi-gcc $(CFLAGS) $(INCS) $(DFLAGS)   $^


#########################################################

P2P_FreeIp: $(P2P_FreeIp_objs)
#	arm-hisiv100nptl-linux-gcc  $(LINKS) $(P2P_FreeIp_objs)  -o  P2P_FreeIp $(LFLAGS)
	arm-hisiv200-linux-g++  $(LINKS) $(P2P_FreeIp_objs)  -o  P2P_FreeIp $(LFLAGS)
#	arm-none-linux-gnueabi-gcc  $(LINKS) $(P2P_FreeIp_objs)  -o  P2P_FreeIp $(LFLAGS)
rebuild: clean all
