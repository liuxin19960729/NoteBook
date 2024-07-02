# 2.文件IO
```
每个Linux 打开文件是由上限的
每个进程启动都会默认打开0(stdin),1(stdout),2(stderr) 文件描述符


文件描述符可以表示打开:
    1.普通文件
    2.设备
    3.管道
    4.FIFO(先进先出缓冲区)
    5.套接字(sokcet)
    ....
    Unix/Linux 遵循一切皆文件的理念
```
## 2.1 打开文件
```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);


return -1 error, success new file descriptor (>0)



flags:
    File access mode(三种模式): 

    note:
        打开一个文件 指定文件的模式必须要看该文件对该进程是否支持该模式的指定
        下面的的flags 文件的访问模式不能进行按位进行运算
        
    O_RDONLY 只读模式(该模式下不能对文件进行写操作)
    O_WRONLY 
    O_RDWR




可以按位运算的flags
O_APPEND:(2.3.2 节详细)
    追加模式打开,每次写入文件文件位置指针都会指向文件末尾
    note:
       即使有另一个进程在写入文件,当当前进程写入数据的时候也是从文件末尾的位置开始写


O_ASYNC:
    指定文件为 O_RDWR(可读可写),会生成一个信号(默认是SIGIO)
    note:
       O_ASYNC 只使用与FIFO,管道,socket和终端,不适用于普通文件

O_CLOEXEC:(since Linux 2.6.23)
    在执行新进程时,文件会自动关闭
    fcntl(2) F_SETFD operations to set the FD_CLOEXEC flag.


O_CREAT:
    pathname 文件不存在内核会自动创建。
    如果文件存在,除非指定O_EXCL,否则O_CREAT 标志位无效

O_DIRECT:(2.5 节详细)
    
```


### 2.3.2 Append(追加)模式
```
Append 模式 
   保证文件位置总是指向文件末尾(即使多个进程向同一文件写入数据)

    Append 模式可以理解为每次写请求之前的文件位置更新是原子操作的

应用场景:
  日志更新

```

## 2.5 直接IO
```

```