```
Cutting out the middleman in data transfers. The discussion started by David Miller's posting of an experimental zero-copy networking implementation (discussed on this page two weeks ago) continues, though it has moved into new areas. One of those is the optimization of data transfers to avoid copying the data as much as possible. Consider, for example, the sendfile() interface that Linux supports now; using sendfile(), an application (a web server, say) can transfer a disk file to a network socket without ever having to read it into user space. There is an obvious performance gain from operating in this mode for certain applications.



cutting out 切断
 
meddleman n 中间环节

experimental adj 实验性的


though it has moved into new areas
   though 连词 引出状语从句
   it 代词  the dissussion    
   has moved  现在完成时态
   into 介词 表示方向变化




在数据传输中切断(cutting out)中间环节。由David Miller发布的一个实验性(experimental)零拷贝网络实现引发的讨论（两周前在这个页面上讨论过）仍在继续(continues)，不过现在已经转向了新的领域。其中一个领域是优化数据传输，以尽可能避免数据拷贝。例如，考虑Linux目前支持的sendfile()接口；使用sendfile()，一个应用程序（比如说，一个网页服务器）可以将一个磁盘文件传输到一个网络套接字，而不必将其读取到用户空间。对于某些(certain adj 某些)应用程序来说，以这种模式操作显然可以获得性能提升。


```


```
So, why not extend the idea to its logical conclusion? Why not have a system call that says "copy data from here to there, and optimize as much as possible"? One approach to this mode is Larry McVoy's 'splice' interface, which tries to provide a general way for user space processes to control high-performance copies. It provides "push" and "pull" primitives which handle the destination and source sides of a copy, respectively, and give the application some latitude in how the two are put together.


extend v 延伸

give v 给 给予

latitude n 自由选择 灵活性

那么，为什么不把这个想法延伸(extend v )到它的逻辑终点呢？为什么不设计一个系统调用，指示 "将数据从这里复制到那里，并尽可能优化"？一种实现(n approach)这种模式的方法是Larry McVoy的(McVoy's) 'splice' 接口，它试图为用户空间进程提供一种控制高性能复制的通用方法。它提供了处理复制目标和源的 "push" 和 "pull" 原语，分别处理复制的目标和源，并且给予(give v )应用程序一些灵活性(latitude )来决定如何组合这两者

```

```
Here's Linus's comments on splice and why it has not been implemented so far. Essentially, sendfile handled the task that most users wanted, the splice interface needed a bit of work, and it didn't fit well into the structure of the kernel at the time. The kernel has since evolved, and Linus's message hints that an implementation of a modified form of splice would be easier now, and that it might even be accepted.


has not been implementd so far
   so far 到现在为止
   现在完成时态 到现在为止没有被实现


fit
   v  适合
   n  适合




 Linus's message hints that an implementation of a modified form of splice would be easier now, and that it might even(adv 甚至) be accepted.
 
    hint v 暗示

    that an implementation of a modified form of splice would be easier now, and that it might even be accepted.
    宾语从句
    an implementation of a modified
    a modified 修改后 修饰 an implementation 一个实现


以下是Linus对splice接口及其尚未实现的原因的评论。基本上(essentially adv )，sendfile处理了大多数用户需要的任务，而splice接口需要一些改进，并且当时它不太适合(it didn't fit)内核的结构(structure of kernel)。内核从那时起已经演变(has since evolved )，Linus的消息暗示(hints)现在实现修改后的splice形式会更容易，并且它可能会被接受。

```

```
One can take the idea further, however: why not, when appropriate, simply tell the hardware to copy the data between devices directly and leave the kernel (and the processor) out of it altogether? According to Linus, that's one of those great ideas that turns out not to be so great in practice. His short response to the idea was:



不过，这个想法可以进一步延伸：为什么不在适当的时候，直接指示硬件在设备之间复制数据，而完全不经过内核（和处理器）呢？根据Linus的说法，这是一个在理论上很棒但在实践中却不那么好的想法。他对此想法的简短回应是：


```

```
They suck. They add a lot of complexity and do not work in general. And, if your "normal" usage pattern really is to just move the data without even looking at it, then you have to ask yourself whether you're doing something worthwhile in the first place.



它们很糟糕(v suck)。它们增加了很多复杂性(complexity n)，而且一般情况下并不起作用。而且，如果你的“正常”使用模式真的只是移动数据，甚至不查看它，那么你必须问问自己，你做的事情是否有价值(adj worthwhile)。


```

```
Further into the discussion, Linus came up with other reasons to avoid direct device-to-device (D2D?) copies. One is that there is very little use for the capability in the end. One can talk, for example, of streaming video directly to disk - but how often will a user be recording video without wanting to look at it too? Another is that very little hardware supports that mode of operation. Linus sees a trend toward connecting hardware with direct, point-to-point links that are not amenable to direct operations between devices. Quoth Linus: "Just wait. My crystal ball is infallible."


trend n 趋势


在讨论的进一步中，Linus 提出了避免(avoid)设备直接对设备（D2D）复制的其他原因。其中一个原因是最终这种功能的用途非常少。例如，人们可以谈论将流媒体视频直接传输到磁盘，但用户在录制视频时不想查看它的情况又有多少呢？另一个原因是很少有硬件支持这种操作模式。Linus 看到一种趋势(trend n  趋势)，即硬件之间通过直接的点对点连接进行连接，而这些连接不适合设备之间的直接操作。Linus 说：“等着瞧吧。我的水晶球是不会出错的。”

```


```
TCP_CORK or MSG_MORE? Another branch of the same discussion has to do with getting optimal performance from network transfers. Imagine a web server using the sendfile() interface described above. In response to a request for a page, the server will first write out a short set of HTTP headers, then use sendfile() to actually transfer the page data. By the time the sendfile() call is actually made, however, the headers will have gone out on the net as a very short packet. The result is poor performance on both the sending and receiving side.


optimal adj 最佳的

TCP_CORK 还是 MSG_MORE？同一讨论的另一个分支涉及如何从网络传输中获得最佳(optimal adj)性能。想象一下，一个使用上述 sendfile() 接口的网络服务器。响应一个页面请求时，服务器将首先写出一小段 HTTP 头，然后使用 sendfile() 实际传输页面数据。然而，当真正调用 sendfile() 时，头部信息已经作为一个非常短的包发送到网络上了。结果是在发送端和接收端都会导致性能不佳。


```
```
Linux has handled this issue with a TCP option called TCP_CORK. If an application sets that option on a socket, the kernel will not send out short packets. Instead, it will wait until enough data has shown up to fill a maximum-size packet, then send it. When TCP_CORK is turned off, any remaining data will go out on the wire.


Linux 使用名为 TCP_CORK 的 TCP 选项来处理这个问题。如果应用程序在套接字上设置了该选项，内核将不会发送短包。相反，它会等待直到有足够的数据来填满一个最大尺寸的包，然后再发送。当 TCP_CORK 被关闭时，任何剩余的数据都会发送出去。

```