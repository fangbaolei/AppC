GSOAP_ROOT = /home/gsoap-2.8/gsoap
WSNAME = add
CC = g++ -g -DWITH_NONAMESPACES
INCLUDE = -I$(GSOAP_ROOT)
SERVER_OBJS = soapC.o stdsoap2.o soapServer.o $(WSNAME)server.o 
CLIENT_OBJS = soapC.o stdsoap2.o soapClient.o $(WSNAME)client.o $(WSNAME)test.o

all: server client
server: $(SERVER_OBJS) 
	$(CC) $(INCLUDE) -o $(WSNAME)server $(SERVER_OBJS) 

client: $(CLIENT_OBJS) 
	$(CC) $(INCLUDE) -o $(WSNAME)test $(CLIENT_OBJS)

clean:
	rm -f *.o  $(WSNAME)server $(WSNAME)test


