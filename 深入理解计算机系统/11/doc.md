# 系统级I/O
```
输入输出(I/0)是主存(main memory) 和 外部设备(磁盘被,终端,和网络)之间的的数据拷贝过程

```
## Unix I/O
```
IO设备 网络 磁盘 终端 都被模型化为文件


1.打开文件
  返回一个非负数(文件描述符)

    <unistd.h>
    STDOUT_FILENO 1
    STDERR_FILENO 2
    STDIN_FILENO 0

2.改变文件位置
  open 文件 文件的偏移量 为
  seek 这只文件偏移量

2.读写文件
    读:从k为位置拷贝n个字节到存储器
       文件此时的位置是 n+k
    

     k 位置
     m 文件大小
     k+n>=m 
      程序读取的位置大于文件大小会触发EOF 条件
      note:程序结尾并没有EOF 符号
    


3.关闭条件
    访问完文件,关闭文件 通知内核释放文件打开时候创建的数据结构
    note:
        程序无论以何种原因终止都会关闭所有在该程序打开的文件
```
## 打开和关闭文件
```c
  #include <sys/types.h>
   #include <sys/stat.h>
   #include <fcntl.h>
   int open(const char *pathname, int flags, mode_t mode);

flags:
     O_RDONLY, 读
    O_WRONLY, 写
     O_RDWR 读写

    O_CREAT
      未能不存在创建一个空文件
    O_APPEND 每次写操作前把位置设置到文件结尾处
    O_TRUNC
     文件存在会这只该文件的长度为0



    mode:
       创建新文件 mode&~umask 创建文件的权限





#include <unistd.h>
int close(int fd);
```

## 读和写文件
```c 
#include <unistd.h>
ssize_t read(int fd, void *buf, size_t count);


return -1
    表示错误
return 0
   表示EOF

return 返回实际传送字节数

#include <unistd.h>
ssize_t write(int fd, const void *buf, size_t count);



显示的修改当前文件的位置
#include <sys/types.h>
#include <unistd.h>
off_t lseek(int fd, off_t offset, int whence);



ssize_t 和  size_t 
   size_t unsigned int
   ssize_t iht
     2^31 2 GB


note:
 在某些情况下,read 和 writ 传送的大小比应用程序要求的小
  出现上面说的这些情况有哪些可能
  1:
    file size 20 byte
    read count 50 会返回20

 2：
    读取终端的文本行(键盘或显示器)

3.
    读写网络套接字
    内核缓冲约束 和 网络延迟 会返回小于应用程序规定的大小
```

## RIO 包进行健壮性地读和写
```
1.无缓冲的输入输出函数
存储器和文件之间直接传送
2.代缓冲的输入函数
  缓冲 应用级缓冲 线程安全
   例如 prinf

```
### RIO 代缓冲的输入行
```c
文本行：
    文本结尾 '\n'
```
## 读取文件源数据
```

```
## 共享文件
```

```
