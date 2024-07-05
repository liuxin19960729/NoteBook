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


O_DIRECTORY:
    note:
      open(name,O_DIRECTORY,mode)
      name 不是目录会调用失败
      O_DIRECTORY 位的设置内部会调用opendir()


O_EXCL:
     O_EXCL| O_CREAT
     name 文件存在会调至调用open 失败 EEXIST.

     用于创建文件的时候出现竞争的情况

     note:
         不和O_CREAT 一起使用没有任何含义


O_LARGEFILE:
    O_LARGEFILE 打开恶意支持大于2GB的文件
    note:64bit OS 默认使用这个参数


O_NOATIME:(since Linux 2.6.8)
    在读取文件的时候不会更新文件的最后访问的时间

    应用场景: 备份,索引,及类似读取系统上的所有文件程序，避免为了更新文件索引节点(inode)而造成大量的写操作(向inode 写入access time)。


O_NOCTTY:
     open(name,O_NOCTTY) name 指向终端(/dev/tty),
     终端设备不会成为该进程的控制终端


O_NOFOLLOW:
     open(name,O_NOFOLLOW)
     name 指向一个符号链接文件open 会失败


    note:

    /etc/ship/plank.txt plant.txt 是符号链接
    open("/etc/ship/plank.txt",O_NOFOLLOW) 执行失败

    如果 /etc/ship/ 是符号链接目录  plant.txt 不是符号链接则open会执行成功



O_NONBLOCK or O_NDELAY
    以非阻塞的方式打开
    note:
      这种情况只适用FIFO
      



O_SYNC:
    open(name,O_SYNC)
    以同步的方式打开文件。
    write() 在数据未写入的磁盘之前 write()不会返回

    POSIX 定义了另外两个标志 OS_DSYNC 和 O_RSYNC  ,在 linux 中  OS_DSYNC 和 O_RSYNC 和 O_SYNC 意思一样



O_TRUNC:
   文件存在,并且是普通文件,并且有些的权限。该标志会把文件长度截断为0。

   note:
      FIFO 和 终端设备O_TRUNC 该标志无效
      要想trunc 文件,必须要有些的权限。否则标志无效

examples:
    /home/teach/pear

    open(name,O_TRUNC|O_WRONLY)

    file exits 并且有写的权限则文件的长度截断为0

    note:
       没有O_CREAT ,file no exits 会失败返回

```

### 2.1.2 新建文件的所有者
```
uid 
创建文件的uid == process 创建的uid

gid
新创建文件的gid
  1.默认: 使用创建进程的有效gid
    System V 通过上面的这种方式
    Linux 很多行为都是以System V 为模型
  
  2.BSD 采用自己的行为方式
    新建立的文件的gid 设置成父目录的gid 


    Linux 实现上面的这种方式
      挂载选项设置


   
为了兼容System V 和 BSD 的这两种行为 使用fchown() 手动设置(第八章)

```


### 2.1.3 新建文件的权限
```c

int open(const char *pathname, int flags, mode_t mode);

flags 指定  O_CREAT 否则 忽略 mode


mode:
    使用POSIX定义的宏可以弥补不同OS的移植性

S_IRWXU：
   文件的所有者读写和执行的权限
    ...

S_IRWXG:
    组用户的读写执行权限
    ...

S_IRWXO:
  任何用户都有读写和执行权限
  ....


note:
    实际对文件权限的设置是 

        umask:进程属性
        umask(mask) 对进程umask值进行修改
            #include <sys/types.h>
            #include <sys/stat.h>
            mode_t umask(mode_t mask);
        
        umask: 
            如果需要哪些权限为用户创建文件设置不了 就需要把
            权限为设置为1



// 权限的设置公式 
mode= mode&(~umask)



权限计算例子:
  (because 0666 & ~022 = 0644; i.e., rw-r--r--).
    0110   6
    &
    1101  ~2
    0100   4  r



```
### 2.3.2 Append(追加)模式
```
Append 模式 
   保证文件位置总是指向文件末尾(即使多个进程向同一文件写入数据)

    Append 模式可以理解为每次写请求之前的文件位置更新是原子操作的

应用场景:
  日志更新

```

## 2.5 直接IO (O_DIRECT)
```
open(name,O_DIRECT)
IO 操作会忽略也缓存机制,直接对用户看看你关键爱你换从去和设备进行初始化,
所有的IO操作都是同步的,在操作完成之间不会返回


note:
  O_DIRECT 指定了之后
  请求长度,缓冲区对齐,和文件偏移量都必须是设备区大小(note:通常是512byte的整数倍)
  
  linux kernel 2.6 以前,更加严格
  所有的操作都必须和文件系统的逻辑块大小对齐(4k),为了保持兼容,应用需要对齐到更大逻辑块的大小(增加了操作难度)

```