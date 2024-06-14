```
so-so ways 一般方式
so that our program can run in restricted environments
  restricted(adj 受限制的) environments 受限制的环境



and not to introduce much overhead as it does so.
  to introduce 不定式短语 引入
  overhead n 花费 开销

   as it does so
   as 连词引入比较状语从句 
   it  前面提到的主语
   dose 做某事
   so adv 表示在这样的方式和情况下


stable adj 稳定的


Libevent is divided into the following components

Libevent 主语
id divided into 
   动词短语 被动 被划分

he following components
  宾语

```
```
evutil
Generic functionality to abstract out the differences between different platforms' networking implementations.

abstract out 抽象出
通用功能用于抽象出不同平台网络实现之间的差异。


event and event_base
This is the heart of Libevent. It provides an abstract API to the various platform-specific, event-based nonblocking IO backends. It can let you know when sockets are ready to read or write, do basic timeout functionality, and detect OS signals.


heart of Libevent 
  libevent 的核心


这是 Libevent 的核心。它提供了一个抽象的 API，用于访问各种平台特定的、基于事件的非阻塞 IO 后端(backends n )。它可以通知你套接字何时准备好读取或写入数据，执行基本的超时功能(functionality n)，并检测操作系统信号。





bufferevent
These functions provide a more convenient wrapper around Libevent’s event-based core. They let your application request buffered reads and writes, and rather than informing you when sockets are ready to do, they let you know when IO has actually occurred.



这些函数提供了对 Libevent 基于事件的核心更方便(adj convenient)的封装。它们允许你的应用程序请求带缓冲的读取和写入操作，而不是在套接字准备就绪时通知你，而是在实际发生 IO 操作时通知你。


These functions provide a more convenient wrapper around Libevent’s event-based core. 

These functions 
  These  限定词 表示复数

provide 动词

a more convenient wrapper
   a 不定冠词 表示一个
   more adv 
   convenient adj 方便的
    wrapper n 封装


around Libevent’s event-based core. 
  around prep 介词 关于 围绕
  core n 核心
  
```
```
evbuffer
This module implements the buffers underlying bufferevents, and provides functions for efficient and/or convenient access.



该模块实现了 bufferevents 底层(adj underlying)的缓冲区，并提供了用于高效和/或方便访问的函数。

```
## The Libraries
```
it may go away in a future version of Libevent. 

可能会在未来的版本消失

may 情态动词 表示可能
go away 动词短语 消失 不在存在


```

## The Headers
```
Headers fall into three broad classes:

    Headers 名词 主语

    fall into 动词短语  归入 划分为

    three broad classes
    broad adj 宽广的  大的
    classes 名词 类别

    three broad  classes  三大类别




An API header is one that defines current public interfaces to Libevent. These headers have no special suffix.


API 头文件是定义当前 Libevent 公共接口的头文件。这些头文件没有特殊的后缀。


Structure headers
These headers define structures with relatively volatile(adj 变化的) layouts. Some of these are exposed in case you need fast access to structure component; some are exposed for historical reasons. Relying on any of the structures in headers directly can break your program’s binary compatibility with other versions of Libevent, sometimes in hard-to-debug ways. These headers have the suffix "_struct.h"



这些头文件定义了结构，这些结构的布局相对(relatively adv)不稳定。之所以公开这些头文件，有些是为了在你需要快速访问结构组件时使用，有些则是出于历史原因。直接依赖这些头文件中的任何结构可能会破坏你的程序与其他版本 Libevent 的二进制兼容性，有时会以难以调试的方式发生。这些头文件的后缀为 "_struct.h"。


```
## If you have to work with an old version of Libevent
```
Libevent 2.0 has revised its APIs to be generally more rational and less error-prone. If it’s possible, you should write new programs to use the Libevent 2.0 APIs. But sometimes you might need to work with the older APIs, either to update an existing application, or to support an environment where for some reason you can’t install Libevent 2.0 or later.



Libevent 2.0 已经修改(has revised v 修改 )了其 API，使其更加合理(rational adj )且更少出错。如果可能的话，你应该编写使用 Libevent 2.0 API 的新程序。但有时你可能需要使用旧的 API，要么是为了更新现有应用程序，要么是为了支持某个环境，在该环境中由于某些原因你无法安装 Libevent 2.0 或更高版本。



In Libevent 2.0 and later, the old headers still exist as wrappers for the new headers.
   
 as wrappers for the new headers. 
     作为新头文件的封装


Before 2.0, there was no support for locking; Libevent could be thread-safe, but only if you made sure to never use the same structure from two threads at the same time.


在 2.0 之前，Libevent 不支持锁机制；Libevent 可以是线程安全的，但前提是你确保绝不会在两个线程中同时使用相同的结构。

individual adj 独立的 单独的

obsolete adj 淘汰的 
             vt 淘汰
encounter v n  相遇      



```