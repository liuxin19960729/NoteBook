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

    O_RDONLY 只读模式(该模式下不能对文件进行写操作)
    O_WRONLY 
    O_RDWR

```
