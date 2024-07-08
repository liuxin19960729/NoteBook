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
### 2.1.4 creat() 函数
```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int creat(const char *pathname, mode_t mode);

相当于

open(const char *pathname,O_CREAT|O_WRONLY|O_TRUNC,mode)


note:
   在大多数Linux 架构中creat() 是一个系统调用
```
### 2.1.5 返回值和错误码
```
错误  返回 -1  并把  errno 设置成相应的错误值

```
## 2.2 通过read() 读取文件
```c
#include <unistd.h>
ssize_t read(int fd, void *buf, size_t count);


return -1 error,EOF 读取完毕 or 当前读取到的字节数



// code1:
nr=read(fd,&buf,sizeof(buf));

if(nr==-1){
    // error
}


code1 存在两个问题
   未读取到count 个数返回，产生某些可操作的错误
   
   没有对上面的情况检查和处理



```
### 2.2.1 返回值
```c
nr=read(fd,&buf,sizeof(buf));

A:
0< nr < count 有哪些原因
1.读取过程中信号中断
2.读取数据过程中出现错误
   管道fd--管道被破坏
3.可读取的数据  大于 0 小于 sizeof(buf)



B:
nr==0
  fd offset 到达文件结尾

  note:
  socket or  device fd 阻塞模式读取 如果当前没有数据可读,使用的是阻塞模式打开,read() 会等待到有数据读取并返回读取的数据

C：
nr==-1
  可恢复的错误
    1.未读取到任何数据被信号打断 此时errno 被设置成EINTR

      解决方式:
       从新读取去读取数据 
    2.非阻塞模式
       当前没有数据可以使用,errno EAGAIN
        请求稍后去重新读取数据

 
 不可恢复的错误
    errno 非 EINTR 和  非EAGAIN
    这种情况下就没有必要再重新去读取数据因为仍然会返回错误
  

D:
  nr==sizeof(buf)
    buf 存取的个数是预期的数据

```
### 2.2.2 读入所有字节
```c
ssize_t ret;
// len!=0 判断是否读取指定的长度
while(len !=0&&(ret=read(fd,buf,len))!=EOF){
    if(ret==-1){
        // 可恢复的错误
       if(errno==EINTR){// 信号中断
           continue;
       }
       perror("read"); //不可恢复错误
       break;
    }

    len-=ret;//读取长度更新
    buf+=ret;//缓冲区指针更新
}
```

### 2.2.3 非阻塞读
```c
使用非阻塞读取的原因:
   1.不希望再读取数据的时候没有可读数据的时候阻塞(socket or devicd等)
     并且希望在没有可读数据的时候立即返回

   2.读取多个文件,当前没有可读数据立即返回,可以去读取其他文件数据。



  fd=open(name,O_NONBLOCK)

  char buf[BUFSIZ];
  ssize_t nr;
  nr=read(fd,buf,len);

  if(nr==-1){
      if(errno==EAGAIN){
         //resubmit later
      }else if(errno==EINTR){
        goto start;
      }else{
         // 不可恢复错误
      }
  }

```
### 2.2.4  其他错误
```c
read() errno 可能会出现的错误
EBADF:文件描述符非法,或者fd不是可读模式
EFAULT:buf 缓冲区指针不在进程可使用内
EINVAL:文件描述符指向的对象不允许读
EIO:底层错误

```
### 2.2.5 read()调用的大小限制
```c
#include <unistd.h>
ssize_t read(int fd, void *buf, size_t count);

ssize_t  size_t 是由POSIX 确定的
32 os  
     c语言通常的类型是
     int  or  unsigned int

note:
   上面代码需要做以下判定

   if(len> SSIZE_MAX){
    len=SSIZE_MAX;
   }
```

## 2.3 调用write()写
```c
#include <unistd.h>
ssize_t write(int fd, const void *buf, size_t count);

count: buf 中最多写入的个数

write 会从当前文件的pos开始写入
note:
  字符设备不允许 seek pos 总是从起始位置开始写入



return 
1.返回写入的byte 个数
2.-1 写入错误 并且 设置 errno
3. 0表示写入0个字节,并没有特殊的意义

```
### 2.3.1部分写入
```c
1.和 read() 相比 write 不太会可能写入部分数据
2.不存在EOF 场景
3.write() 调用保证 除非发生错误，write 会写入整个请求
   note: 只在写入普通文件保证



普通文件
   不需要循环写操作


其他类型文件
   socket
   需要循环保证写入所有请求数据
  


ssize_t ret;
// len!=0 表示写入只写入部分数据到kernel 缓冲区
while(len !=0&&(ret=write(sockfd,buf,len))!=EOF){
    if(ret==-1){
        // 可恢复的错误
       if(errno==EINTR){// 信号中断
           continue;
       }
       perror("read"); //不可恢复错误
       break;
    }



    len-=ret;//写入长度更新
    buf+=ret;//缓冲区指针更新
}
```

### 2.3.2 Append(追加)模式
```c

fd=open(name,O_APPEND);
每次写入数据都是从文件末尾开始写入数据

当多个进程 线程同时向同一个文件并且都指定O_APPEND 的模式开始写入数据
这样就能保证每次任何一个进程向文件写入数据都在最后写入
  
  O_APPEND 没次开始写入写入和更新pos 都是原子的



应用场景:
  日志更新

```
### 2.3.3 非阻塞写入
```c
fd=open(name,O_NONBLOCK);

write(fd,buf,len) return -1 errono EAGAIN 
可恢复错误 过一会儿重新写

note:
   对弈普通文件一般不会 return -1 errono EAGAIN 
```
### 2.3.4 其他错误码
```c
EBADF:文件描述符非法,或者fd不是写读模式
EFAULT:buf 缓冲区指针不在进程可使用内
EFBIG:写入数据超过进程最大文件限制或内部设置限制
EINVAL:文件描述符指向的对象不允许写
EIO:底层错误

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
## 2.6 关闭文件
```c
#include <unistd.h>
int close(int fd);

close() kernel 会取消fd与关联文件之间的映射
fd 不在有效, fd 值会被内核重新利用


retrun -1 error 


note:
 1.
  close(fd) 并不意味着内容已经被存入到磁盘


  fsync(fd);//or fdatasync(fd)  sync()

  if(close(fd)==-1){
    perror("close");
    return;
  }

  //此时才能保证数据已经写入到磁盘



  2.
    文件/文件夹删除
    
    1.close() 2.inode 没有引用数量
    2.os将会处理inode,
    3.这个时候才会真正的删除
```
**错误码**
```
note:
  close() 的 errno 不会出现EINTR
```
## 2.7 用 lseek() 查找
```c
#include <sys/types.h>
#include <unistd.h>
off_t lseek(int fd, off_t offset, int whence);

return 
   -1 error
   or cur offest


whence:
  SEEK_SET:
      相对于文件开始的位置 设置 offset
      
  SEEK_CUR:
     cur offest + offset
     offset 可以是 <0  ==0  >0
     
  SEEK_END:
     file length + offset
        offset 可以是 <0  ==0  >0

      

例如
1.设置 offset 文件 1825
off_t ret;

ret =lseek(fd,1825,SEEK_SET);

if(fd==(off_t)-1){
  perror("lseek")
  return;
}


2.将offset 设置当前文件的末尾

off_t ret;
ret =lseek(fd,0,SEEK_END);


if(fd==(off_t)-1){
  perror("lseek")
  return;
}




note:
  获取当前位置

off_t pos;
ret =lseek(fd,0,SEEK_CUR);


if(fd==(off_t)-1){
  perror("lseek")
  return;
}

//pos 就是当前文件的位子

```
### 2.7.1 文件末尾查找
```c
off_t ret;
ret =lseek(fd,1688,SEEK_END);


if(fd==(off_t)-1){
  perror("lseek")
  return;
}


write(fd,buf,count);


note:
   中间空洞的空间会用0来填充

   UNIX: 文件系统吧空洞不展通任何物理空间
          意味着文件系统数据 >= 磁盘数据

```
### 2.7.2 文件末尾查找
```c
EBADF:
  fd 不是open 的文件描述符

EINVAL:
  off_t lseek(int fd, off_t offset, int whence);
  whence 参数这设置错误
  结果 offset 是相对与文件开始位置负数

EOVERFLOW:
  返回的结果不能通过 off_t 表示
  note:
     只有32 位的操作系统才会出现该错误

ESPIPE:
    fd 不支持 lseek() 操作

    例如:
        管道 pipe socket

```

### 2.7.3 限制
```
off_t 大部分计算机会定义为 C long 类型

note:
  C  标准规定 long 的最小不小于 32 bits

but:
  内核实现把偏移量值存储位long long 类型 

  note:
    64 bit os  long 类型 64 bits

    
    而 32 bits long 类型 通常 32 bits ,如果offset 超过该范围
    errno EOVERFLOW
  
```
## 2.8 定位读写
```c
 #include <unistd.h>
 ssize_t pread(int fd, void *buf, size_t count, off_t offset);
 ssize_t pwrite(int fd, const void *buf, size_t count, off_t offset);




_XOPEN_SOURCE >= 500
|| /* Since glibc 2.12: */ _POSIX_C_SOURCE >= 200809L


note:
   1.pread 和 pwrite 调用 不会更改 cur offset
   2. pread 和 pwrite 相比于
      lseek() +(read() or write()) 避免了 lseek() 时出现的数据竞争
```
**错误码**
```
pread()==-1
  errno 可能会插线 read() or lseek 的  errno

pwrite()==-1
  errno 可能会插线 write() or lseek 的  errno

```
## 2.9 文件截断
```c
#include <unistd.h>
#include <sys/types.h>
int truncate(const char *path, off_t length);
int ftruncate(int fd, off_t length);


return 
    succ : 返回文件长度为指定len



note:
  len > 文件长度 

  这种情况是允许的,会出现文件空洞

```
## 2.10 I/0 多路复用
```c
前面讲的非阻塞I/0
  
  fd= open(name,O_NONBLOCK)

  ret =read(fd,buf,count)

  or 
  
  ret =write(fd,buf,count)


ret ==-1  && errno == EAGAIN 需要在次请求 判断是否可以写入和读取


如果是桌面程序 or 高效的程序 上面的这种非阻塞方式设计的非常糟糕
   因为 如果需要做某件事 需要 去轮询调用




IO 多路复用:
  多个文件描述符阻塞,直到某个fd 收到 可读 or 可写 的消息 进程会收到对应的消息
  

 IO 多路复用设计遵循
    1.任何一个文件准备就绪通知
    2.没有任何一文件描述符可用之前处于休眠状态
    3.有文件描述符可以,会被唤醒
    4.处理所有的IO就绪的文件描述符,没有阻塞
    5.返回第一个重新开始

```

### 2.10.1 select()
```c
#include <sys/select.h>

int select(int nfds, fd_set *readfds, fd_set *writefds,fd_set *exceptfds, struct timeval *timeout);

void FD_CLR(int fd, fd_set *set);
int  FD_ISSET(int fd, fd_set *set);
void FD_SET(int fd, fd_set *set);
void FD_ZERO(fd_set *set);




readfds 监听是否数据可读


writefds 监听某个写操作是否可以无阻塞完成
exceptfds  监听是否有异常, 可以指定为NULL






struct timeval {
  time_t      tv_sec;         /* seconds */
  suseconds_t tv_usec;        /* microseconds */
};


timeout:  
  在指定的时间后没有IO准别就绪,调用会返回


note:
  每次调用表select 的时候timeval 重新定义

  Linux：
     会修改 timeval 对应的值 
    


例如 
   tv_sec =5
   在地3s有准备好的IO,tv_sec=2(会被修改)



fd_set writesfds; 
FD_ZERO(&writesfds); // 删除指定集合所有文件描述符

FD_SET(fd,&writesfds);// 向 writesfds 集合中添加fd 文件描述符

FD_CLR(fd,&writesfds); // 从 writesfds 删除fd文件描述符

FD_ISSET(fd,&writesfds)  检查 writesfds 中是否有fd

```
**返回值和错误码**
```c
int select(int nfds, fd_set *readfds, fd_set *writefds,fd_set *exceptfds, struct timeval *timeout);


return 0
      -1 error



EBADF:
  非法文件描述符
EINTR:
  等待时捕获Interrupt

EINVAL:
   fd < 0
   timeout 设置为非法值

ENOMEM:
    没有足够的内存来完成该请求


```
**pselect()**
```c
       int pselect(int nfds, fd_set *readfds, fd_set *writefds,
                   fd_set *exceptfds, const struct timespec *timeout,
                   const sigset_t *sigmask);

   Feature Test Macro Requirements for glibc (see feature_test_macros(7)):

       pselect(): _POSIX_C_SOURCE >= 200112L

      


note:
 1. pselect 不会修改 timeout, 后续不需要 重新初始化
 2. sigmask 未 NULL ,则 pselect() 和 select() 没有区别
 




为什么pselect的存在
  1.为了解锁文件描述符和信号之间等待而出现竞争条件

note:第10章 信号
```