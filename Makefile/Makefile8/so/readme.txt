1. Makefile的静态模式:
<target>:<target-pattem>:<prereq-patterns>
	<commands>
2. +=符号
此Makefile使用的静态模式是：$(OBJECT)%.o:%.c
也可以不使用静态变量,改为使用以下的一些方法：
方法一：将编译内容中的
$(TARGET):$(OBJECT)
$(OBJECT):%.o:%.c
    $(CC) -c $(CFLAGS) $< -o $@
合并为一句：
$(TARGET):$(OBJECT)
    $(CC) $(CFLAGS)-c $(OBJECT) -o $(TARGET)
方法二：.o.c
.c.o:
    $(CC) -c $(CFLAGS) $<
$(TARGET):$(OBJECT)
    $(CC) $(OBJECT) -o $(TARGET)

