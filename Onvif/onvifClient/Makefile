#Target
TAR_CLN = myClient
TAR_CLN_LIB = myClient.a
#your gsoap install directory
GSOAP_DIR=/home/gsoap-2.8
INSTALL_DIR=/home/onvif
#compiler
CORSS_COMPILER = 
G++ :=$(CORSS_COMPILER)g++
AR = ar
#flags
LIBS = -lpthread -lm
INCS = -I ./ -I $(GSOAP_DIR)/gsoap -I$(GSOAP_DIR)/gsoap/plugin -I$(GSOAP_DIR)/gsoap/import
CFLAGS = -O2 -Wall -Wno-deprecated-declarations -g
      
CLN_SRCS = soapC.cpp stdsoap2.cpp soapClient.cpp $(TAR_CLN).cpp
CLN_BOJS = $(CLN_SRCS:.cpp=.o)
CLN_LIB_SRCS = soapC.cpp stdsoap2.cpp soapClient.cpp $(TAR_CLN_LIB:.a=.cpp)
CLN_LIB_BOJS = $(CLN_LIB_SRCS:.cpp=.o)
#MAKE
.PHONY: all
all: $(TAR_CLN)

$(TAR_CLN) : $(CLN_BOJS)
	$(G++) -o $@ $^ $(LIBS)
$(TAR_CLN_LIB): $(CLN_LIB_BOJS)
	$(AR) -rv $@ $^
%.o:%.cpp
	$(G++) -c -o $@ $(INCS) $(CFLAGS) $(filter %.cpp,$^) 

ifeq (,$(MAKECMDGOALS))
sinclude $(CLN_BOJS:%.o=%.d)
endif
ifeq ($(TAR_CLN),$(MAKECMDGOALS))
sinclude $(CLN_BOJS:%.o=%.d)
endif
ifeq ($(TAR_CLN),$(MAKECMDGOALS))
sinclude $(CLN_LIB_BOJS:%.o=%.d)
endif

%.d: %.cpp
	@echo "create depend" $@ : $< ......................
	@$(G++) -MM $(INCS) $< >$@.$$$$;  sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@;  $(RM) $@.$$$$

stdsoap2.cpp: $(GSOAP_DIR)/gsoap/stdsoap2.cpp
	cp $(GSOAP_DIR)/gsoap/stdsoap2.cpp ./ -f

#gsoap
WSDL_SOURCE = $(wildcard *.wsdl)
TYPEMAP = $(GSOAP_DIR)/gsoap/typemap.dat
WSDL_OUTPUT_FILE = onvif.h
GSOAP_OUTPUT_FILES = soapClient.cpp soapServer.cpp soapC.cpp soapH.h soapStub.h

$(WSDL_OUTPUT_FILE) : $(WSDL_SOURCE)
	wsdl2h -P -j -t $(TYPEMAP) $(WSDL_SOURCE) -o $(WSDL_OUTPUT_FILE)
$(GSOAP_OUTPUT_FILES) : $(WSDL_OUTPUT_FILE)
	soapcpp2 -x -L $(INCS) $(WSDL_OUTPUT_FILE)

#install
install:
	@cp -vf $(TAR_CLN_LIB) $(TAR_CLN_LIB:.a=.h) $(INSTALL_DIR)

#clean
clean:
	@rm -rfv *.o *~ *Proxy.h *Object.h $(TAR_SRV) $(TAR_CLN) $(TAR_CLN_LIB)
deepClean:
	@rm -rfv *.o *~ *Proxy.h *Object.h *.d $(TAR_SRV) $(TAR_CLN) $(TAR_CLN_LIB) $(GSOAP_OUTPUT_FILES) $(WSDL_OUTPUT_FILE) *.nsmap stdsoap2.cpp
