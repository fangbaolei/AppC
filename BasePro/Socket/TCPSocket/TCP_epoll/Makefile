# 子目录
SUBDIRS := Client
SUBDIRS += Server_epoll 

#-C:切换编译的目录 
#但下面的语句，首先会执行$(SUBDIRS):，即切换到子目录(SUBDIRS)appLib中，执行里面的Makefile,然后再切换返回
all: $(SUBDIRS)

$(SUBDIRS):  
	@make -C $@ > /dev/NULL    # > /dev/NULL:表示不输出编译的打印过程(未验证)

#foreach:这里的含义是遍历$(SUBDIRS)中的目录，并执行make clean 操作。
clean:
	@$(foreach SUBDIR, $(SUBDIRS), make clean -C $(SUBDIR) clean > /dev/NULL ;)
	@make -C Client clean > /dev/NULL
	@make -C Server_epoll clean > /dev/NULL
.PHONY: clean $(SUBDIRS)
