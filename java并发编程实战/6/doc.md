# 6任务执行
### 6.1.2显示的为每个人物创建线程
```java
note:
 这种方式要求请求速率不能超过服务器的处理能力
```
### 6.1.3 无限制的创建线程的不足
```java
1.线程的创建和销毁开启并不是没有代价，当请求的到达率很高,这样同一时间创建大量的线程,将消耗巨大的计算资源(内存，Gc带来压力,太多的线程,Os调度切喊上下文)


note:
   线程数量的限制(OS限制，JVM启动参数)
   Thread请求的栈大小
   如果超出了这些限制会抛出OutOfMemoryError 异常 


```
## 6.2 Executor 框架
```java
web 服务器任务处理 
单线程串行执行:响应慢,吞吐量低
每个连接一个线程处理:资源管理限制等复
```
### 6.2.1 示例：基于Executor 的Web服务器
### 6.2.2 执行策略
### 6.2.3 线程池
```java
线程池的好处
1.线程的重用(不用重新分配 销毁等操作)
2.线程一定提前创建好,task 请求来到 如果存在空闲线程,直接获取任务执行,提供task 的请求性
3.线程池启动,通过调整产生为每台不同配置的机器调整适合并且性能最高的参数


1. 固定长度的线程池

    public static ExecutorService newFixedThreadPool(int nThreads) {
        return new ThreadPoolExecutor(nThreads, nThreads,
                                      0L, TimeUnit.MILLISECONDS,
                                      new LinkedBlockingQueue<Runnable>());
    }


  
  execute(r)
      max 和  core 数量一样
      每提交一个任务创建一个线程知道创建到传入的最大数量



2.可缓存的线程池
 public static ExecutorService newCachedThreadPool() {
        return new ThreadPoolExecutor(0, Integer.MAX_VALUE,
                                      60L, TimeUnit.SECONDS,
                                      new SynchronousQueue<Runnable>());
core 线程数量0
最多线程数量  int 最大整数
线程数量不足,创建线程。线程数量多个回收
note: 可缓存线程池对线程的数量没有限制



3.单线程的线程池
    public static ScheduledExecutorService newSingleThreadScheduledExecutor() {
        return new DelegatedScheduledExecutorService
            (new ScheduledThreadPoolExecutor(1));
    }


    创建单个线程执行任务，如果线程异常结束会创建另一个线程来代替


......
```
### 6.2.4 Executor 的生命周期
```java
JVM 关闭条件：必须所有非守护线程结束
note:
  如果无法正确的关闭executor 则Jvm无法正确的结束


exector 关闭的时候任务的状态
1.任务已经完成
2.正在执行
3.任务正在任务队列等待执行


关闭线程池的方式:
1.平缓关闭
  完成正在执行的任务
  完成队列里存在的任务
  不在接受新任务入任务队列
2.暴力关闭


```

### Executor 生命周期接口
```java


ExecutorService 三种状态
  运行 关闭  已终止


终止状态:所有任务都执行完毕当前线程没有线程在执行任务

平缓关闭
   showdown ()  execuorService 关闭状态
   

public interface ExecutorService extends Executor {

    /**
     

     平缓关闭

     * @throws SecurityException if a security manager exists       denies access.
     */
    void shutdown();

    /**
     暴力关闭
     1.尝试取消所有的运行任务
     2.还未执行的在任务队列里的任务不会执行
     *
     * @return list of tasks that never commenced execution
     * @throws SecurityException if a security manager exists 
     */
    List<Runnable> shutdownNow();

    /**
     * Returns {@code true} if this executor has been shut down.
     *
     * @return {@code true} if this executor has been shut down
     */
    boolean isShutdown();

    /**
      是否已经终止
     */
    boolean isTerminated();

    /**
      
      等待ExecutorService 终止
     * @throws InterruptedException if interrupted while waiting
     */
    boolean awaitTermination(long timeout, TimeUnit unit)
        throws InterruptedException;

    /**
     * Submits a value-returning task for execution and returns a
     * Future representing the pending results of the task. The
     * Future's {@code get} method will return the task's result upon
     * successful completion.
     *
     * <p>
     * If you would like to immediately block waiting
     * for a task, you can use constructions of the form
     * {@code result = exec.submit(aCallable).get();}
     *
     * <p>Note: The {@link Executors} class includes a set of methods
     * that can convert some other common closure-like objects,
     * for example, {@link java.security.PrivilegedAction} to
     * {@link Callable} form so they can be submitted.
     *
     * @param task the task to submit
     * @param <T> the type of the task's result
     * @return a Future representing pending completion of the task
     * @throws RejectedExecutionException if the task cannot be
     *         scheduled for execution
     * @throws NullPointerException if the task is null
     */
    <T> Future<T> submit(Callable<T> task);

    /**
     * Submits a Runnable task for execution and returns a Future
     * representing that task. The Future's {@code get} method will
     * return the given result upon successful completion.
     *
     * @param task the task to submit
     * @param result the result to return
     * @param <T> the type of the result
     * @return a Future representing pending completion of the task
     * @throws RejectedExecutionException if the task cannot be
     *         scheduled for execution
     * @throws NullPointerException if the task is null
     */
    <T> Future<T> submit(Runnable task, T result);

    /**
     * Submits a Runnable task for execution and returns a Future
     * representing that task. The Future's {@code get} method will
     * return {@code null} upon <em>successful</em> completion.
     *
     * @param task the task to submit
     * @return a Future representing pending completion of the task
     * @throws RejectedExecutionException if the task cannot be
     *         scheduled for execution
     * @throws NullPointerException if the task is null
     */
    Future<?> submit(Runnable task);

    /**
     * Executes the given tasks, returning a list of Futures holding
     * their status and results when all complete.
     * {@link Future#isDone} is {@code true} for each
     * element of the returned list.
     * Note that a <em>completed</em> task could have
     * terminated either normally or by throwing an exception.
     * The results of this method are undefined if the given
     * collection is modified while this operation is in progress.
     *
     * @param tasks the collection of tasks
     * @param <T> the type of the values returned from the tasks
     * @return a list of Futures representing the tasks, in the same
     *         sequential order as produced by the iterator for the
     *         given task list, each of which has completed
     * @throws InterruptedException if interrupted while waiting, in
     *         which case unfinished tasks are cancelled
     * @throws NullPointerException if tasks or any of its elements are {@code null}
     * @throws RejectedExecutionException if any task cannot be
     *         scheduled for execution
     */
    <T> List<Future<T>> invokeAll(Collection<? extends Callable<T>> tasks)
        throws InterruptedException;

    /**
     * Executes the given tasks, returning a list of Futures holding
     * their status and results
     * when all complete or the timeout expires, whichever happens first.
     * {@link Future#isDone} is {@code true} for each
     * element of the returned list.
     * Upon return, tasks that have not completed are cancelled.
     * Note that a <em>completed</em> task could have
     * terminated either normally or by throwing an exception.
     * The results of this method are undefined if the given
     * collection is modified while this operation is in progress.
     *
     * @param tasks the collection of tasks
     * @param timeout the maximum time to wait
     * @param unit the time unit of the timeout argument
     * @param <T> the type of the values returned from the tasks
     * @return a list of Futures representing the tasks, in the same
     *         sequential order as produced by the iterator for the
     *         given task list. If the operation did not time out,
     *         each task will have completed. If it did time out, some
     *         of these tasks will not have completed.
     * @throws InterruptedException if interrupted while waiting, in
     *         which case unfinished tasks are cancelled
     * @throws NullPointerException if tasks, any of its elements, or
     *         unit are {@code null}
     * @throws RejectedExecutionException if any task cannot be scheduled
     *         for execution
     */
    <T> List<Future<T>> invokeAll(Collection<? extends Callable<T>> tasks,
                                  long timeout, TimeUnit unit)
        throws InterruptedException;

    /**
     * Executes the given tasks, returning the result
     * of one that has completed successfully (i.e., without throwing
     * an exception), if any do. Upon normal or exceptional return,
     * tasks that have not completed are cancelled.
     * The results of this method are undefined if the given
     * collection is modified while this operation is in progress.
     *
     * @param tasks the collection of tasks
     * @param <T> the type of the values returned from the tasks
     * @return the result returned by one of the tasks
     * @throws InterruptedException if interrupted while waiting
     * @throws NullPointerException if tasks or any element task
     *         subject to execution is {@code null}
     * @throws IllegalArgumentException if tasks is empty
     * @throws ExecutionException if no task successfully completes
     * @throws RejectedExecutionException if tasks cannot be scheduled
     *         for execution
     */
    <T> T invokeAny(Collection<? extends Callable<T>> tasks)
        throws InterruptedException, ExecutionException;

    /**
     * Executes the given tasks, returning the result
     * of one that has completed successfully (i.e., without throwing
     * an exception), if any do before the given timeout elapses.
     * Upon normal or exceptional return, tasks that have not
     * completed are cancelled.
     * The results of this method are undefined if the given
     * collection is modified while this operation is in progress.
     *
     * @param tasks the collection of tasks
     * @param timeout the maximum time to wait
     * @param unit the time unit of the timeout argument
     * @param <T> the type of the values returned from the tasks
     * @return the result returned by one of the tasks
     * @throws InterruptedException if interrupted while waiting
     * @throws NullPointerException if tasks, or unit, or any element
     *         task subject to execution is {@code null}
     * @throws TimeoutException if the given timeout elapses before
     *         any task successfully completes
     * @throws ExecutionException if no task successfully completes
     * @throws RejectedExecutionException if tasks cannot be scheduled
     *         for execution
     */
    <T> T invokeAny(Collection<? extends Callable<T>> tasks,
                    long timeout, TimeUnit unit)
        throws InterruptedException, ExecutionException, TimeoutException;
}


note:
   executorService 关闭后提交的任务会throw  RejectedExecutin 
   提交任务的时候需要捕获该异常处理
  
    

    executorService.awaitTermination(); 等待到当前线程变为终止状态
    executorService.shotdown(); 产生同步执行关闭的效果
   


```
### 6.2.5 延迟队列
```
Timer 缺陷：
  1.单线程  不适合同步费时的线程执行
  2.TimerTask 抛出未检查异常，Timer 未对该异常处理,会导致定时线程终止
```
## 6.3 找出可利用的并行性
### 6.3.1 示例:串行的页面渲染
### 6.3.2 携带结果的任务Callable与Future
```java
Runnable:
  确定:不能返回结果
       不能获取异常

Executor 任务的4个生命周期
  创建
  提交
  开始
  完成


  note:
   1. Executor框架中已提交未开始的任务可以取消任务

   2. 已经开始执行的任务需要他们可以响应中断的是时候才能取消任务,否则不能取消任务

   3.取消一个已经完成的任务不会有任何影响




Future 任务
  Future.get() 行为取决于任务的状态(尚未开始,正在运行,已经完成)

  已经完成 
    Future.get() 立即返回值 or 会抛出 Exception
    
  正在运行
      Future.get() 阻塞到任务完成返回  
   

  
  note:
    Future.get() 抛出异常 会将执行的异常封装成ExecutionException 重新抛出
    如何获得ExecutionException的原始异常
    Future.getCause()




ExecutorService 
<T> Future<T> submit(Callable<T> task);


public abstract class AbstractExecutorService implements ExecutorService 


Runnable 或 Callabel 都默认实现创建一个新的FutureTask

    protected <T> RunnableFuture<T> newTaskFor(Runnable runnable, T value) {
        return new FutureTask<T>(runnable, value);
    }

    protected <T> RunnableFuture<T> newTaskFor(Callable<T> callable) {
        return new FutureTask<T>(callable);
    }
```
### 6.3.3 示例:使用Future实现页面渲染器
### 6.3.4 在异构任务并行化中存在局限
### 6.3.5 CompletionService:Executor与BlockingQueue
```java
完成服务
    public interface CompletionService<V>

     CompletionService 将 Executor 和 BlockingQueue功能融合在一起


public class ExecutorCompletionService<V> implements CompletionService<V> {
    private final Executor executor; 计算部分
    private final AbstractExecutorService aes;
    private final BlockingQueue<Future<V>> completionQueue;

    //  Future 计算结果


    public Future<V> take() throws InterruptedException {
        return completionQueue.take();
    }

    public Future<V> poll() {
        return completionQueue.poll();
    }





private class QueueingFuture extends FutureTask<Void>{
          QueueingFuture(RunnableFuture<V> task) {
            super(task, null);
            this.task = task;
        }
        protected void done() { completionQueue.add(task); }
        private final Future<V> task;
}


completionQueue 存储当前Future 完成了的任务



ExecutorCompletionService.take();
ExecutorCompletionService.poll();


```
### 6.3.7 为任务设置时间限制
```java

Future.get
V get(long timeout, TimeUnit unit)
        throws InterruptedException, ExecutionException, TimeoutException;



throw TimeoutException
  任务需要超时立即停止计算
  可以由任务本身来管理,在超时后终止执行或取消任务
  
  Future future;
  try{
    future.get(time,NANOSECONDS);
  }catch(TimeoutException e){
    future.cancel(true)
  }
```
### 6.3.8 示例:旅行预定门户网站
