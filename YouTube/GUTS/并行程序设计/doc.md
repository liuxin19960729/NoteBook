[Scheduling Internals](https://tontinton.com/posts/scheduling-internals/)
</br>
[SMP CPU 架构](https://www.techtarget.com/searchdatacenter/definition/SMP) 
</br>
[ipi inter processor interrupt](https://en.wikipedia.org/wiki/Inter-processor_interrupt)
```
ipi cpu  和 cpu 之间的终端

```
```
调度器:
  硬件:
     对于CPU 来说根本不知道调度器的存在

调度器   
  做任务的分配到CPU的执行

CPU Affinity (CPU亲和力)

cpu 和 cpu中断 (ipi ), 其他硬件的中断,无法保证一个任务一次执行完毕

```
##### select
```
connect 很多,每次只能连接一个
select(事件的监听器) 可以通知程序客户端的数据来了或客户端的连接来了

poll
epoll  (相比于select 资源上限更加高)
```

#### event loop
```
coroutine
    c++20
    go 实现goroutine


qemu 模拟器
  单工 可以模拟255个cpu 使用coroutine 技术


folly , facebook 工程师制作

甚至LLVM或者说llvm的编译器也提供builtin coroutine support.


```
