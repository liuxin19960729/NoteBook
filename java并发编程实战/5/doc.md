# 5基础构建模块
## 5.1 同步容器
```java
早期JDK
  Vector  HashTable
JDK 1.2 添加
  Collections.synchronizedXxx 等 工厂方法创建
```
###  5.1.1 同步容器类的问题
```
只要我门知道使用了哪个锁,那些新操作就与容器其他操作一样都是原子操作

```
### 5.1.2 迭代器与ConcurrentModificationException
```java
java 5.0 引入了 for-each 循环语法
  for-each 这种方式都使用了Iterator这种方式
  note:
  fail-fast "及时失败"
    在设计容器类迭代器时并没有考虑到并发修改问题.当发现容器在迭代过程中被修改,会throw 出
    ConcurrnetModifiationException



fail-fast 实现方式
    将计数器的变化和容器关联起来,如果在迭代期间计数器被修改,hasNext 或 nest() 操作将会抛出
    ConcurrnetModifiationException





        public E next() {
            synchronized (Vector.this) {
                checkForComodification();// 检查数据是否被修改
                int i = cursor;
                if (i >= elementCount)
                    throw new NoSuchElementException();
                cursor = i + 1;
                return elementData(lastRet = i);
            }
        }


在迭代期间对容器上锁,若果容器很大,并且每个元素操作一些东西也很浪费时间,则会增加锁的锁的竞争b并且,在响应时间和吞吐量方面都会受到很大影响


解决方式:
  克隆容器 在使用迭代器遍历
```
### 5.1.3 隐藏迭代器
```java

HashSet toString()

    public String toString() {
        Iterator<E> it = iterator();
        if (! it.hasNext())
            return "[]";

        StringBuilder sb = new StringBuilder();
        sb.append('[');
        for (;;) {
            E e = it.next();
            sb.append(e == this ? "(this Collection)" : e);// 元素 o.toString()的值放入sb
            if (! it.hasNext())
                return sb.append(']').toString();
            sb.append(',').append(' ');
        }
    }



// test.java

		Set<String> set = new HashSet<String>();
		System.out.println(set);

        答应set 实际是先调用toString() 获取字符串在打印





note:
  HashSet 答应的同时,在另一线程在add or remove 则可能会抛出ConcurrnetModifiationException
  (add or remove) 即使 add  和 remove 是 sychronized 方法
  


  容器不光toString() 会这行迭代器操作,hashCode() 和 equals等方法也会简介的执行迭代操作
  ......


```
## 并发容器
```java
Java 5.0 提供多种并发容器来改进同步容器的性能
note:
    同步容器 所有对容器状态的的访问实现成串行化,
    使用同步容器在多个线程竞争的时候吞吐量将严重降低



ConcurrentHashMap  ->  HashMap
    ConcurrentHashMap 增加一些复合型操作
      public V putIfAbsent(K key, V value) 
      ....等操作
CopyOnWriteArrayList  -> List


Queue 
  ConcurrentLinkedQueue
   传统的先进先出队列
  PriorityQueue  
    非并发优先队列

BlockingQueue  
    对 Queue 扩展
  public interface BlockingQueue<E> extends Queue<E> 
  增加了可阻塞的插入和获取等操作
  
  获取一个元素,若果队列没有相关元素阻塞,知道存入元素
  掺入数据,如果队列满了,则阻塞,知道队列出现可用的空间
  note: 生产者和消费者这种设计模式,阻塞队列非常有用



Java 6 引入
@since 1.6
public class ConcurrentSkipListMap<K,V> extends AbstractMap<K,V>
@since 1.6
public class ConcurrentSkipListSet<E>
    extends AbstractSet<E>
    implements NavigableSet<E>, Cloneable, java.io.Serializable 

分别作为同步SortedMap 和 SortedSet 并发替代品


```
### 5.2.1 ConcurrentHashMap
```java
ConcurrentHashMap 不是将每个方法都在同一个锁上同步并使得每次只能有一个线程访问容器
而是使用分段锁
读操作操作支持并发访问，
读写操作支持并发访问
一定量写操作支持并发的修改Map 


和 HashTable 等相比在并发的环境下吞吐量更加大



迭代器不会抛出ConcurrentModificationException 
ConcurrentHashMap 返回的迭代器是具有弱一致性，并且及时失败。
遍历数据的同时并可以在迭代器构造后将修改操作反映给容器(并不能保证)。

Map 上的方法 size() 和 isEmpty() 这些进行计算的方法予以被略微减弱,用反应容器上的并发性特征
size() 返回 可能过期(并发情况下),所以size() 返回的值只是一个预估值


``` 
### 额外的原子Map操作
### 5.2.3 CopyOnWriteArrayList
```java
并发使用场景下 List 的替代
迭代情况下,不用对容器加锁或复制


使用场景：
   迭代使用次数远远多余写入修改操作
   example:
      事件分发系统,对事件列表的迭代需求远远大于 修改

    public E set(int index, E element) {
        final ReentrantLock lock = this.lock;
        lock.lock();
        try {
            Object[] elements = getArray();
            E oldValue = get(elements, index);

            if (oldValue != element) {
                int len = elements.length;
                Object[] newElements = Arrays.copyOf(elements, len);
                newElements[index] = element;
                setArray(newElements);
            } else {
                // Not quite a no-op; ensures volatile write semantics
                setArray(elements);
            }
            return oldValue;
        } finally {
            lock.unlock();
        }
    }


上面的代码 就是 CopyOnWriteArrayList set  方法  当调用 修改元素函数会赋值一个新数组在替换掉原来旧的数组        
```
### 5.3 阻塞队列和生产者-消费者模式
```java
无界限队列:
    生产者生产比率大于消费者,那么工作队列很快就用完了。直到内存耗尽导致系统崩溃
有界队列:
    队列充满,生产者将阻塞,不能继续工作。而消费者就有时间来赶上工作进度。




ArrayBlockingQueue.java

    public boolean offer(E e) {
        checkNotNull(e);
        final ReentrantLock lock = this.lock;
        lock.lock();
        try {
            if (count == items.length)
                return false;//如果数据不能被添加到队列
            else {
                enqueue(e);
                return true;
            }
        } finally {
            lock.unlock();
        }
    }

1.并发情况下 offer() 返回 false 将 多余的数据项灵活的做一些策略

高可用的应用程序,可以用有界队列做强大的资源管理工具,防止产生过多的工作项,使应用种子负荷过载的情况下变的更加健壮




BlockingQueue 的实现
    ArrayBlockingQueue
        
    LinkedBlockingQueue
        
    
    FIFO 队列


非线程安全
    ArrayList
    LinkedList




PriorityBlockingQueue
   按照优先级排列的队列,
      通过存入元素,实现的  Comparable 或 comparator 接口来进行排列



SynchronousQueue
    实际不是一个真正的队列，不是维护队列中元素的空间
    实际维护的是线程,这些线程等待着将元素移出队列和加入队列
     
    改方式是直接交互的方式,当我们把元素交给了队列,其实就可以认为消费者接受了 任务
    note:
       这种方式和 其他阻塞队列不同的是,将数据交给了队列,并不能认为任务开始执行,需要消费者去阻塞队列去领取数据

        SynchronousQueue 并没有存储能力,put 和 take 会直接

    

    SynchronousQueue 适合使用的场景
        当消费者足够多的情况下,并且总有消费者等待着接收任务的情况下适合使用SynchronousQueue

```
### 5.3.1 桌面搜索
### 5.3.2 串行线程封闭
```java
java6新增加的另种容器类型
Deque 双端队列  实现头部或尾部高效的插入或移除
ArrayDeque

LinkedBlockingDeque
    两端都能获取元素增加线程的并行执行效率

```
###  阻塞方法与中断方法
```
阻塞的状态:BLOCKED,WAITNG,TIME_WAITING


Interrupt-Exception
  当Thread.sleep() 或启动方法执行导致阻塞,抛出InterruptException 的时候则代表提前结束阻塞


 Thread.interrupt() 
    用来中断或者查询某个线段是否中断


```
## 5.5 同步工具类
### 5.5.1
```
CountDownLatch 是闭锁的实现
await()  等待到数量为0 才继续向下执行  or  超时  or  Interrupt Exception
countDown() 递减计数器

```

### 5.5.2FutureTask
```
future.get() 讲阻塞到任务结束并返回结果

```
### 5.5.3 信号量
```
Semphore 构造函数制定许可数量
Semphore.acquire() 主阻塞到有许可
Semphore.release() 返回一个许可
```
### 5.4.4 栅栏
```java
栅栏(Barrier) 类似于闭锁 
栅栏:所有线程必须同时到达栅栏位置才能继续执行
闭锁用于等待事件
栅栏用于等待其他线程
CyclicBarrier
    并行迭代算法，
       将一个问题拆分成一系列子问题。
       await() 后,必须等到所有线程到达该位置
       await() 后超时 or  阻塞的线程或被中断,await 会抛出BrokenBarrierException

       每个线程到达后 成功返回 则会返回一个该线程到达的索引值
   

   note:
       可以通过await()返回的索引指定一个领导线程,下一次迭代由该领导线程执行一些特殊的操作。
       

       CyclicBarrier 构成的时候可以传入Runable ,当所有线程通过后会由子任务的线程执行Runable



```
## 5.6 高效可伸缩性的缓存
```java
ConcurrentHashMap<string,Future>


import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;
import java.util.concurrent.FutureTask;

public class FutureTaskTest {

    public static void main(String[] args) throws ExecutionException, InterruptedException {

        FutureTask<Integer> future=new FutureTask<>(new Callable<Integer>() {
            @Override
            public Integer call() throws Exception {

                  Thread.sleep(2000);
                return Integer.valueOf(100);
            }
        });

        Thread thread =new Thread(future);
        thread.start();
       
        // future 会将结果缓存
        System.out.println(future.get());
        System.out.println(future.get());


    }
}


note:
   ConcurrentHashMap

   Future f=cache.get(key) //cache 线程安全

   if(f==null){
       FutureTask<Integer> future=new FutureTask<>(new Callable<Integer>() {
            @Override
            public Integer call() throws Exception {

                  Thread.sleep(2000);
                return Integer.valueOf(100);
            }
        });

        f=cache.putIfAbsent(key,future)； 如果不存在添加
    
         // putIfAbsent key 在容器中没有对应的映射返回null
         if(f==null){ 
        future.run()
        f=future;
   }
   }


   v=v.get()



```