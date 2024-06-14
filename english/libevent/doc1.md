# libevent
```
The libevent API provides a mechanism to execute a callback function when a specific event occurs on a file descriptor or after a timeout has been reached. Furthermore, libevent also support callbacks due to signals or regular timeouts.
libevent is meant to replace the event loop found in event driven network servers. An application just needs to call event_dispatch() and then add or remove events dynamically without having to change the event loop. 

due to 由于 因为
mechanism n 机制 
regular adj 常规的


after a timeout has been reached
    after 连词,引导事件状语从句,表示时间顺序
    a timeout 名词短语
    had been reached 完成时被动语态
    到超时后


状语:
  短语 或从句修饰动词或形容词或复词


libevent is meant to replace the event loop found in event driven network servers.

lebevent 主语
is meant to 谓语动词短语 表目的 意图
replace 动词 替代 
the event loop 宾语 事件循环

found in event driven network servers 定于重句修饰 the event loop ,表示event loop 存在的地方 
    

libevent API提供了一种机制，当特定事件在文件描述符上发生或达到超时时间后，执行回调函数。此外，libevent还支持由于信号或常规超时触发的回调。

libevent旨在取代事件驱动网络服务器中的事件循环。应用程序只需要调用event_dispatch()，然后可以动态添加或移除事件，而无需更改事件循环。



 An application just needs to call event_dispatch() and then add or remove events dynamically without having to change the event loop. 

 An application  主语 应用

just needs to call 谓语动词短语

event_dispatch 宾语


without having to
   without 介词 表示没有或不需要
   having to  动词短语 表示 必须做某事

   without having to 不必要做某事

    例句:
       You can complete the task without having to ask for help


```

```
Currently, libevent supports /dev/poll, kqueue(2), event ports, POSIX select(2), Windows select(), poll(2), and epoll(4). The internal event mechanism is completely independent of the exposed event API, and a simple update of libevent can provide new functionality without having to redesign the applications. As a result, Libevent allows for portable application development and provides the most scalable event notification mechanism available on an operating system. Libevent can also be used for multi-threaded applications, either by isolating each event_base so that only a single thread accesses it, or by locked(加锁) access to a single shared event_base. Libevent should compile on Linux, *BSD, Mac OS X, Solaris, Windows, and more.


redesign n v 重新设计 重新规划

As a result 因此


most scalable event notification mechanism available on an operating system.
   most scalable 最高扩展 形容词短语
   event notification mechanism 名词短语 事件通知机制
   available 形容词 可用的
   on an operating system 介词短语 修饰名词短语 在操作系统上



either by isolating each event_base so that only a single thread accesses it
either by 介词 短语 方法自已
isolating 动名词 隔离
each event_base 名词短语 每一个 event_base
so that 连词 引导状语从句
only a single thread accesses it 从句 
   解释 前面 的内容

当前，libevent 支持 /dev/poll、kqueue(2)、事件端口、POSIX select(2)、Windows select()、poll(2) 和 epoll(4)。其内部事件机制完全独立于外部公开(expose)的事件 API，只需简单更新 libevent 即可提供新功能，而无需重新设计应用程序。因此，libevent 允许开发可移植(portable)的应用程序，并提供操作系统上最具扩展性的事件通知机制。

libevent 还可以用于多线程应用程序，既可以通过隔离每个 event_base 使得只有一个线程访问它，也可以通过加锁访问一个共享的 event_base。libevent 应该可以在 Linux、*BSD、Mac OS X、Solaris、Windows 等系统上编译。

```

```
Libevent additionally provides a sophisticated framework for buffered network IO, with support for sockets, filters, rate-limiting, SSL, zero-copy file transmission, and IOCP. Libevent includes support for several useful protocols, including DNS, HTTP, and a minimal RPC framework.


sophisticate
 n 见多识广的人
 v 更复杂 先进(设备技术)

several adj 各自的 

Libevent 还提供了一个复杂的(sophisticated)缓冲网络 I/O 框架，支持套接字、过滤器、速率限制、SSL、零拷贝文件传输和 IOCP。Libevent 还包括对多个有用协议的支持，包括 DNS、HTTP 和一个简单的 RPC 框架
```

```
Most beginning programmers start with blocking IO calls. An IO call is synchronous if, when you call it, it does not return until the operation is completed, or until enough time has passed that your network stack gives up. When you call "connect()" on a TCP connection, for example, your operating system queues a SYN packet to the host on the other side of the TCP connection. It does not return control back to your application until either it has received a SYN ACK packet from the opposite host, or until enough time has passed that it decides to give up.


or until enough time has passed that your network stack gives up.

    or 连词  两种情况 之一 或
    enough time has passed 
       直到过了很久
    
    that your network stack gives up. 
      使你的网络放弃为止
        
      

大多数初学编程的人从阻塞 I/O 调用开始。当一个 I/O 调用是同步的时，当你调用它时，它不会返回，直到操作完成，或者网络堆栈放弃为止。例如，当你在 TCP 连接上调用 "connect()" 时，你的操作系统会将一个 SYN 数据包排队发送到另一端的主机。只有在收到对方主机的 SYN ACK 数据包，或者经过足够长的时间决定放弃后，它才会将控制权返回给你的应用程序。



```
```

All of the network calls in the code above are blocking: the gethostbyname does not return until it has succeeded or failed in resolving www.google.com; the connect does not return until it has connected; the recv calls do not return until they have received data or a close; and the send call does not return until it has at least flushed its output to the kernel’s write buffers



All of the network calls in the code above are blocking:
  
  All of 限定短语 整体 全部 所有
the network calls  
   the 定冠词 指定 in the code 
   network calls 名词短语 做主语

 the code above 名词短语 上面的代码


  All of 限定  the network calls  

  are blocking blocing 形容词 形容前面主语的一种状态



上面的代码中的所有网络调用都是阻塞的：gethostbyname 在成功或失败地解析 www.google.com 之前不会返回；connect 在连接之前不会返回；recv 调用在接收到数据或关闭之前不会返回；send 调用在至少将其输出刷新到内核的写缓冲区之前不会返回。


```


```
Now, blocking IO is not necessarily evil. If there’s nothing else you wanted your program to do in the meantime, blocking IO will work fine for you. But suppose that you need to write a program to handle multiple connections at once. To make our example concrete: suppose that you want to read input from two connections, and you don’t know which connection will get input first. You can’t say

evil:
   adj 有害的
   n  有害 邪恶

meantime
    n 期间 
    adv 同时 

fine
  adv 很好的
  adj 令人满意的 很好的

现在，阻塞IO并不一定是有害的。如果在此期间(n meantime)你的程序没有其他任务要执行，阻塞IO对你来说完全可行(fine adj )。但是假设(suppose v)你需要编写一个程序来同时处理多个连接。为了使我们的例子更具体：假设你想从两个连接读取输入，而且你不知道哪个连接会先接收到输入。

```

```
because if data arrives on fd[2] first, your program won’t even try reading from fd[2] until the reads from fd[0] and fd[1] have gotten some data and finished.


因为如果数据先到达 fd[2]，你的程序在从 fd[0] 和 fd[1] 读取到一些数据并完成之前，甚至不会尝试从 fd[2] 读取。



because:连词引导状语从句
the reads from fd[0] and fd[1] 主语
have gotten some data and finished. 谓语


have gotten 现在完成时态
  gotten get 的过去分词 获得得到某物的动作
  have+done(动词过去分词)
    到当前已经完成

```
```
Sometimes people solve this problem with multithreading, or with multi-process servers. One of the simplest ways to do multithreading is with a separate process (or thread) to deal with each connection. Since each connection has its own process, a blocking IO call that waits for one connection won’t make any of the other connections' processes block.



有时人们通过多线程或多进程服务器来解决(v solve)这个问题。进行多线程的最简单方法之一是为每个连接使用一个单独的进程（或线程）。由于每个连接都有自己的进程，因此一个阻塞IO调用在等待一个连接时，不会使其他连接的进程阻塞。


```

```
Here’s another example program. It is a trivial server that listens for TCP connections on port 40713, reads data from its input one line at a time, and writes out the ROT13 obfuscation of line each as it arrives. It uses the Unix fork() call to create a new process for each incoming connection.

trivial: adj 简单的 

obfuscation:n 困惑 迷糊 混淆


这里是另一个示例程序。这是一个简单的(adj trivial)服务器，监听 TCP 连接的端口 40713，逐行从输入中读取数据，并在每行到达时写出其 ROT13 加密。它使用 Unix 的 fork() 调用来为每个传入的连接创建一个新的进程。


```

```
So, do we have the perfect solution for handling multiple connections at once? Can I stop writing this book and go work on something else now? Not quite. First off, process creation (and even thread creation) can be pretty expensive on some platforms. In real life, you’d want to use a thread pool instead of creating new processes. But more fundamentally, threads won’t scale as much as you’d like. If your program needs to handle thousands or tens of thousands of connections at a time, dealing with tens of thousands of threads will not be as efficient as trying to have only a few threads per CPU.


threads won’t scale as much as you’d like(希望).
  wont't  will not 缩写
  as much as 表程度 尽可能多
  thread 主语
  won't scale 谓语
  as much as you'd like 状语短语
  
  线程不会是非常希望的那样可扩展


 dealing with tens of thousands of threads will not be as efficient as trying to have only a few threads per CPU.
  
  dealing with tens of thousands of threads
    deal with 动词短语 处理
    tens of thousands of threads 名词 短语成千上万个线程
   will not be as efficient as
      will not be 未来时态 不会是
      as efficient(adj) as
          像....一样高效
      
  
  trying to have only a few threads per CPU
   trying to have 动词短语 尝试...
  

  主语
    dealing with(动名词短语做主语核心) tens of thousands of threads
  as efficient as 表程度 像....一样高效    



那么，我们是否已经找到了处理多个连接的完美解决方案了？我可以停止写这本书，去做其他事情了吗？并不完全是这样。首先(First off)，进程创建（甚至线程创建）在某些平台上可能非常(adv prretty)昂贵(adj 昂贵的)。在实际生活中，你会希望使用线程池来代替创建新进程。但更根本的是(But more fundamentally)，线程的扩展性可能不如你希望的那样。如果你的程序需要同时(at a time)处理数千(thousands of)甚至数万个(tens of thousands)连接，处理成千上万个线程将不如每个 CPU 只有几个线程的效率高


```

```
But if threading isn’t the answer to having multiple connections, what is? In the Unix paradigm, you make your sockets nonblocking. The Unix call to do this is:
fcntl(fd, F_SETFL, O_NONBLOCK);


But if threading isn’t the answer to having multiple connections,
 isn’t(is not)
 to having multiple connections 介词短语 修饰 the answe


但如果线程不是处理多个连接的答案，那么什么是呢？在Unix编程范式中，你可以将套接字设置为非阻塞模式。在Unix中，用于实现这一操作的系统调用是：

```

```
where fd is the file descriptor for the socket. [1] Once you’ve made fd (the socket) nonblocking, from then on, whenever you make a network call to fd the call will either complete the operation immediately or return with a special error code to indicate "I couldn’t make any progress now, try again." So our two-socket example might be naively written as:


from then on 
  从那时候起

naively adv 天真地

在这里，fd 是套接字的文件描述符。一旦你将 fd（套接字）设置为非阻塞模式，从那时起，每当你对 fd 进行网络调用时，该调用要么立即完成操作，要么返回一个特殊的错误代码，表示“我现在无法取得任何进展，请重试。”因此，我们的双套接字示例可能会天真地(naively adv )写成：


```

```
Now that we’re using nonblocking sockets, the code above would work… but only barely. The performance will be awful, for two reasons. First, when there is no data to read on either connection the loop will spin indefinitely, using up all your CPU cycles. Second, if you try to handle more than one or two connections with this approach you’ll do a kernel call for each one, whether it has any data for you or not. So what we need is a way to tell the kernel "wait until one of these sockets is ready to give me some data, and tell me which ones are ready."



the code above would work… but only barely
 the 定冠词 特定的代码
 code 名词
 above adv  上文提到的代码

 would(情态动词 表示假设和推测) work 
 only adv 副词 仅仅
 barely adv 勉强 几乎不可能


 the code 主语
 would work 可能运行
 but only barely 状语 修饰 would work 
 上面的这个代码仅仅有一点可能会执行





using up all your CPU cycles
  using up 动词短语 消耗
  using 
  up adv 修饰 using

  all 限定词 所有



现在我们正在使用非阻塞套接字，上面的代码会工作……但效果很差。性能将非常糟糕(awful adj /ˈɔːf(ə)l/ )，有两个原因。首先，当两个连接上都没有数据可读时，循环将无限(indefinitely adv 无限地)旋转(spin v)，耗尽所有的 CPU 循环。其次，如果尝试使用这种方法处理超过一两个连接，你将为每个连接执行一个内核调用，无论它是否有数据可供读取。因此，我们需要一种方法来告诉内核：“等待直到这些套接字中的一个准备好提供数据给我，并告诉我哪些准备好了。”


```

```
The oldest solution that people still use for this problem is select(). The select() call takes three sets of fds (implemented as bit arrays): one for reading, one for writing, and one for "exceptions". It waits until a socket from one of the sets is ready and alters the sets to contain only the sockets ready for use.




人们仍然用于解决这个问题的最古老的解决方案是 select()。select() 调用接受三组文件描述符集合（实现为位数组）：一个用于读取，一个用于写入，一个用于“异常”。它会等待直到其中一个集合中的套接字准备就绪，并修改(alters v)这些集合，只包含准备好使用的套接字。
```

```
But we’re still not done. Because generating and reading the select() bit arrays takes time proportional to the largest fd that you provided for select(), the select() call scales terribly when the number of sockets is high. [2]



但我们还没有完成。因为生成(generating v)和读取 select() 的位数组的时间与你为 select() 提供的最大文件描述符数量成正比(proportional adj)，所以当套接字数量很高时，select() 调用的性能表现非常糟糕(terribly adv 非常糟糕)。

```

```
Different operating systems have provided different replacement functions for select. These include poll(), epoll(), kqueue(), evports, and /dev/poll. All of these give better performance than select(), and all but poll() give O(1) performance for adding a socket, removing a socket, and for noticing that a socket is ready for IO.


不同的操作系统提供了用于替代(n replacement) select() 的不同函数。这些包括 poll()、epoll()、kqueue()、evports 和 /dev/poll。所有这些函数都比 select() 提供更好的性能，除了 poll() 外，它们在添加套接字、移除套接字和检测套接字是否准备好进行 IO 方面都具有 O(1) 的性能。

```
```
Unfortunately, none of the efficient interfaces is a ubiquitous standard. Linux has epoll(), the BSDs (including Darwin) have kqueue(), Solaris has evports and /dev/poll… and none of these operating systems has any of the others. So if you want to write a portable high-performance asynchronous application, you’ll need an abstraction that wraps all of these interfaces, and provides whichever one of them is the most efficient.


不幸的是，所有高效的接口都不是普遍存在的标准。Linux 使用 epoll()，BSD（包括 Darwin）使用 kqueue()，Solaris 使用 evports 和 /dev/poll…… 而且这些操作系统中没有一个支持其他的接口。因此，如果你想编写一个可移植且高性能的异步应用程序，你需要一个封装所有这些接口并提供其中最有效的接口的抽象层。



none of 没有一个

ubiquitous adj 形容词 无处不在的 普遍存在的
 

whichever 限定词 表示任何一个或无论哪一个


```

```
And that’s what the lowest level of the Libevent API does for you. It provides a consistent interface to various select() replacements, using the most efficient version available on the computer where it’s running.


这就是 Libevent API 的最底层功能为你提供的。它为你提供了一个统一的(cosistent adj)接口，用于访问各种(various adj 各种各样的) select() 的替代方法，并在运行它的计算机上使用可用的最高效版本。


```
```
Here’s yet another version of our non-blocking ROT13 server. This time, it uses Libevent 2 instead of select(). Note that the fd_sets are gone now: instead, we associate and disassociate events with a struct event_base, which might be implemented in terms of select(), poll(), epoll(), kqueue(), etc.



这里是我们非阻塞 ROT13 服务器的另一个版本，这次使用的是 Libevent 2 而不是 select()。请注意，现在已经没有 fd_sets 了：相反，我们将事件与一个 struct event_base 相关联和取消关联，该结构可能是基于 select()、poll()、epoll()、kqueue() 等实现的。

```

### what about convenientce? (and what about windows)
```
You’ve probably noticed that as our code has gotten more efficient, it has also gotten more complex. Back when we were forking, we didn’t have to manage a buffer for each connection: we just had a separate stack-allocated buffer for each process. We didn’t need to explicitly track whether each socket was reading or writing: that was implicit in our location in the code. And we didn’t need a structure to track how much of each operation had completed: we just used loops and stack variables.




你可能已经注意到，随着我们的代码变得更加高效，它也变得更加复杂(adj complex)了。当我们还在使用 fork 创建进程时，我们不需要为每个连接管理一个缓冲区：我们只需为每个进程分配一个单独的栈内存缓冲区。我们不需要显式跟踪每个套接字是在读取还是写入：这在我们代码中的位置中是隐含的。我们也不需要一个结构来跟踪每个操作已完成了多少：我们只是使用循环和栈变量。

```