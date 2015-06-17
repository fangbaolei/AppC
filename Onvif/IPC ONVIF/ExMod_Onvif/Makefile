####################################################################################
#   makefile
####################################################################################

include 	../../config.local

LIBSO		:=libOnvif.so
LIB             :=libOnvif.a
LIBUUID := ../../$(LIBDIR)/Lib_Uuid.a

SRCS= \
	OVF_Discovery_Client.c\
	OVF_Core.c\
	OVF_DeviceManager_Io.c\
	OVF_DeviceManager_NetWork.c\
	OVF_DeviceManager_OvfInfo.c\
	OVF_DeviceManager_Security.c\
	OVF_DeviceManager_System.c\
	OVF_DeviceManager_User.c\
	OVF_Discovery.c\
	OVF_Imaging.c\
	OVF_Media.c\
	OVF_Ptz.c\
	soapC_1.c\
	soapC_2.c\
	soapC_3.c\
	soapC_4.c\
	soapServer.c\
	soapClient.c\
	stdsoap2.c

OBJS = $(addsuffix .o,$(basename $(SRCS)))
ifeq ($(ISMAKE_ONVIF), yes)
all:$(LIBSO) $(LIB)
else
all:
	@echo -e "\033[31mISMAKE_ONVIF is not yes\033[0m"
endif
$(LIBSO):$(OBJS)
	$(CC) -shared -fPIC  $(OBJS) $(LIBUUID) -o $(LIBSO)
	cp $(LIBSO) ../../$(LIBDIR)/LibSo/
#	cp $(LIBSO) /work/nfs_root/ -rf
$(LIB) :$(OBJS)
	$(AR) -rc $(LIB) $(OBJS)




%.o : %.c
	$(CC) -DWITH_NONAMESPACES -I$(LSP_INCLUDE_DIR) -I./  -c $<
	
clean: 
	rm -rf *.o
	rm -rf ../../$(LIBDIR)/$(LIBSO)
	rm -rf ../../$(LIBDIR)/$(LIB)
	
