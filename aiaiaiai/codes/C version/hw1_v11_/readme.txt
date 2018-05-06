Windows用户请在new_exec.cpp文件里添加
#include <WINDOWS.H>
头文件
并在new_exec.cpp文件main函数结尾返回前添加
system("pause");
编译指令：
Linux:
g++ -g -Wall new_exec.cpp -o new_exec
Windows:
g++ -g -Wall new_exec.cpp -o new_exec.exe
