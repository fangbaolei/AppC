# 编译生成动态库
all: $(LIB_NAME).a 
# -shared :编译动态库 
#生成动态库
$(LIB_NAME).a:$(COBJS) 
	$(AR) -rc -o $(LIB_NAME).a $(COBJS)
#清除
clean:
	rm *.o *.d  $(LIB_NAME).a -f
