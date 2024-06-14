# 文件IO:通用的文件io模型
## 4.1 概述
```c
shell 中执行某一个程序,该程序会继承(fork 子进程)shell 的 三个标准文件描述符号


当执行某一个程序,并且重定向输入的时候,shell启动程序会对标准的文件描述符进行设置并启动程序


文件描述符宏定义位置
#include<unistd.h>



#include <stdio.h>
FILE *freopen(const char *pathname, const char *mode, FILE *stream);
  freopen() 使文件描述符号指向任意文件
note:
    stdout 调用 freopen函数后无法保证stdout变量仍然为1

fd=open(pathname,flags,mode)
  pathname 所标识的文件
  flags 指定文件的打开方式
  
  mode  open 创建文件的访问权限(如果open函数没有创建文件,mode 参数忽略)


numread=read(fd,buffer,count)
   count:读取文件最多可以读取的字节数量
   note:
     numread 返回 EOF(0) 代表读取完毕

numwritten=write(fd,buffer,count)
    count 写入该文件的字节数
    note:
      返回numwritten 可能小于count

status=close(fd)
  输入/输出操作完成后
  释放文件描述符号与之相关的内核资源

```
## 4.2 通用I/O
## 4.3 打开一个文件:open()
```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int open(const char *pathname, int flags, mode_t mode);
return -1 error

SUSv3 规定open()调用成功 保证返回值为进程未用描述符的最小值
```
### 4.3.1 open调用的flags参数
```
fcntl() F_GETFL 检索文件的访问模式
   O_RDONLY O_WRONLY O_RDWR

fcntl F_GETFL F_SETFL 可以检索和修改文件状态(除了文件创建标志)


/proc/pid/fdinfo
  文件信息
```
### 4，3,3 craate()系统调用
## 4.4 读取文件内容:read()
## 4.5 数据写入文件:write()
```c
#include <unistd.h>
ssize_t write(int fd, const void *buf, size_t count)
return 返回的size 可能小于 count
原因
  1.磁盘满了
  2.RLIMIT_FS IZE 进程资源对文件大小的限制
```
## 4.6关闭文件:close()
## 4.7改变文件偏移量:lseek()
### 文件空洞
```c
文件空洞不会占用磁盘空间,空洞后写入的数据才会分配磁盘空间
note:
  对于大多数磁盘是以块为单位,块大小(1024,2048,4096)
  当空洞文件边界落在块内,非落在块边界上,则会分配完整的块来存储数据
  空洞相关部分以空字节填充



不支持文件空洞的文件系统会显示的将字节存入文件

空洞的存意味着文件大小,要比占用空间大,
    当向空洞区域写入数据的时候,文件大小不变,但是磁盘空间会减少


#include <fcntl.h>
int posix_fallocate(int fd, off_t offset, off_t len);
  return 0  success ,or fail
向磁盘写入value 未 0 大小为len 的空间

linux 2.6.23 开始

 #define _GNU_SOURCE             /* See feature_test_macros(7) */
       #include <fcntl.h>

       int fallocate(int fd, int mode, off_t offset, off_t len)

更加高效的实现磁盘空间分配

```
## 通用的IO模型以外的操作:ioctl()
```c
ioctl()  系统调用又为执行文件和设备操作提供了一种多用途机制

#include <sys/ioctl.h>
int ioctl(int fd, unsigned long request, ...);



request:指定fd的控制操作
   #include <sys/ioctl.h> 定义了request 参数的常量
  
```