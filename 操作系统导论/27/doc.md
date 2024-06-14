# 线程API
## 线程完成
```c
#include <pthread.h>
int pthread_join(pthread_t thread, void **retval);
   thread 指定需要等待的线程
   retval 线程执行的function 返回的参数
 

pthread_join
  并不是所有的程序都需要join
  join 确保程序在进行下一个阶段之前上一个任务已经完成
```
## 锁
```c

两种方式初始化锁
pthread_mutex_t lock PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock ;
int rc = pthread_mutex_init(&lock, NULL);
assert(rc == 0); // always check success! 


pthread_mutex_lock(&lock)// 当不持有lock 会卡在该函数内部
   没有其他持有lock 线程进入临界区

pthread_mutex_unlock(&lock)


note:
pthread_mutex_lock or  pthread_mutex_unlock
 都可能执行失败
 所以需要进行错误判断
  


pthread_mutex_trylock
  如果lock 已经被持有 则返回失败
pthread_mutex_timedlock 
    获取锁的 timedlock定版本会在超时或获取锁后返回
```
## 条件变量
```C
条件变量的用处
  一个线程,等待另一个线程继续执行某些操作


pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex); 
   线程进入休眠 等待其他线程发出信号,
pthread_cond_signal(pthread_cond_t *cond); 

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;


Pthread_mutex_lock(&lock);
while (ready == 0)
   Pthread_cond_wait(&cond, &lock); ready 等于0调用等待函数以便休眠 直到被唤醒
    // wait 并且 释放锁
    // 被换新之后需要去重新获得锁
Pthread_mutex_unlock(&lock);



Pthread_mutex_lock(&lock);
ready = 1;
Pthread_cond_signal(&cond); // 唤醒 wait 的线程
Pthread_mutex_unlock(&lock);



```
## 编译和运行
