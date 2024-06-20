# 20 信号:基本概念
## 20.1 概念和概述
```c
信号类型:
1.硬件发生异常
   硬件发生错误告诉OS,OS 将对应的信号给相关的进程
   例如:
        1.除0
        2.引用了无法访问的内存区域
2.键盘键入产生信号的终端字符
  例如:
    CTR+C
    CTR+Z
3.软件事件

```
**信号的定义**
[siginal-generic](./siginal-generic.h)
```c
note:
  信号对应的值是和对应的系统相关,并不是不会改变的



信号分类
1.传统信号
    Linux 1-31
2.标准信号





信号状态
    等待(pending)



进程接收到信号的时机
    1.如果该进程马上被调度执行,等待信号会马上送达
    2.如果进程正在执行,等待信号会立即送达




note:
  如果当前这段代码不允许信号到达中断该程序执行,可以将信号添加到进程的信息掩码中,如果内核需要发送信号到进程的时候,判断该信号被当前进程设置到阻塞之列,那么当前该发送的信号始终保持等待状态(pending) ，知道等待到对应的信号掩码移除,才会金等待的信号发送

 



进程可以如何处理这些到达的信号?
1.忽略信号
    内核将信号丢弃,不会像进程发送该信号
2.终止进程
  非正常终止(非 exit()终止进程)
3.核心文件转储并且终止进程

4.停止进程
    暂停进程的执行
5.进程重前面的暂停在恢复进程





程序可以改变信号的默认的响应的行为
    1.将修改的信号行为恢复成默认的信号行为
    2.忽略信号
        (适用于忽略默认终止进程的默认行为)
    3.执行信号处理程序



note:
    无法将信号处置设置为终止经常或转储核心

```
## 20.2 信号类型和默认行为
```c

Linux 标准信号 1-31
signal(7) 定义确超过了Linux 标准信号 
    note:有很多信号名是同义词的为了和其他Unix实现保持兼容



1.
#define	SIGABRT		6	/* Abnormal termination.  */
    abort() 调用会发送SIGABRT信号
    进程会接收到信号会产生转存文件,并且终止进程

2.
#define	SIGALRM		14	/* Alarm clock.  */

    #include <unistd.h>
    unsigned int alarm(unsigned int seconds);
    #include <sys/time.h>
    int setitimer(int which, const struct itimerval *new_value,
                        struct itimerval *old_value);

    定时器一旦到期会产生SIGALRM 信号




3. SIGBUS
 SIGBUS       P2001      Core    Bus error (bad memory access)
某种内存访问错误发送的信号(49.4.3节)

例如:
    mmap() 创建内存映射的时候,试图访问地州超出底层内存映射文件的结尾,会产生SIGBUS错误


4. SIGCHLD
    SIGCHLD      P1990      Ign     Child stopped or terminated

   4.1父进程某一子进程终止(exit() or 被信号杀死),内核会向父进程发发送SIGCHILD信号
   4.2 父进程某一子进程收到时信号停止或恢复父进程也会接收到SIGCHILD 信号



5. SIGCLD
 SIGCLD         -        Ign     A synonym for SIGCHLD
 和SIGCHILD 同义(synonym n)

6. SIGCONT
  SIGCONT      P1990      Cont    Continue if stopped
  
  SIGCONT信号发送给停止的进程,该进程会恢复运行(在某个时间点会被kernel 重新调度)

  如果接受信号的进程不是停止的状态,会忽略该信号


  note:(22.2和 34.7)
    该进程可以捕获该信号,当该进程恢复执行的时候会执行捕获函数可以执行程序员执行的某些操作


7. SIGEMT
    SIGEMT         -        Term    Emulator trap
    



8. SIGFPE
 SIGFPE       P1990      Core    Floating-point exception

 SIGFPE 特定的算数错误而产生(例如: 除0)
 note: 
    虽然 FPE float point exception 的缩写,但是整数的运算错误也会产生该信号

    何时产生取决于硬件架构对CPU控制寄存器的设置

        例如
            X86-32  整数/0 总是产生  SIGFPE 信号
            浮点数/ 0 的处理区域于是否启用了FE_DIVBYZERO 异常(启用 浮点数/0 产生 SIGFPE 信号)

         

         fenv(3)




9. SIGHUP
SIGHUP       P1990      Term    Hangup detected on controlling 

```