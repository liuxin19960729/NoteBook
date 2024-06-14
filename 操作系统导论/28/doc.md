# 锁
## 锁的基本思想
## Pthread 锁
## 实现一个锁
```
需要OS支持
需要硬件的支持
```
## 评价锁
## 控制中断
```c
 void lock() {
    DisableInterrupts();
 }
 void unlock() {
    EnableInterrupts();
 }

 关闭临界区中断,为单个CPU设计的

优点:
  简单
  不支持多处理器
缺点:
  允许调用线程执行特权(关闭开启中断)
   导致中断丢失(IO完成)


```
## 原子交换
```
exchange 指令 测试并交换(原子交换)
```
## 实现可用的自旋锁
## 评价自旋锁
```
自旋锁 不提供任何公平性的保证

```
## 比较与交换
```c
x86 
char CompareAndSwap(int *ptr, int old, int new) {
    unsigned char ret;
    // Note that sete sets a 'byte' not the word
    __asm__ __volatile__ (
    " lock\n"
    " cmpxchgl %2,%1\n"
    " sete %0\n"
    : "=q" (ret), "=m" (*ptr)
    : "r" (new), "m" (*ptr), "a" (old)
    : "memory");
    return ret;
 } 
```
##  链接的加载和条件式存储指令
## 简单方法：让出来吧,宝贝
## 使用队列代替自旋
```

```