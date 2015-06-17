步骤：
1. 编写add.h，它的作用主要是生成其他的文件。
2. 执行：soapcpp2 -c add.h
3. 将gsoap-2.8/gsoap目录下的stdsoap2.c和stdsoap2.h拷贝到当前目录。
4. 编写其他文件，
5. 编译：make
6. 执行:./addserver
