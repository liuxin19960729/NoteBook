# 对象的共享
```
在多个线程同时访问的情况下,如何安全共享和发布对象.

synchronized 的作用
1.临界区的原子性
2.内存可见性
  (当一个线程修改了状态,其他线程可见状态发生了改变)
```
## 3.1 可见性
```java
public class NoVisibility {

	private static boolean ready;
	private static int number;

	private static class ReaderThread extends Thread {
		@Override
		public void run() {
			long count = 0;
			while (!ready) {
				Thread.yield();// 放弃执行权
				count++;
			}

			System.out.println("执行次数: " + count);
			System.out.println(number);
		}
	}

	public static void main(String[] args) throws InterruptedException {

		Thread thread = new ReaderThread();
		thread.start();
		Thread.sleep(100);
		number = 42;
		ready = true;
		thread.join();
	}
}


执行可能
1.可能永远不停止
2.可能 number 输出0 
   编译器重排序


note:
  在没有同步的情况下,编译器和处理器以及运行时都可能对操作的顺序进行意想不到的调整
```
### 3.1.1 失效数据
```java
一个线程先set一个值,另一个线程get 可能获取的值是old value 也有可能是 new 

value



	private boolean value;

	public synchronized boolean getValue() {
		return value;
	}

	public synchronized void setValue(boolean v) {
		value = v;
	}

上面这种写法 一个线程 setValue ,另一个线程获取到的值 getValue 也有可能是过期的


```
### 3.2.2 非原子的64位操作
```
非 volatiel 类型 64位变量类型(long double)
Java内存模型要求,变量的读取和操作必须是原子的(除了 64bits long和dobule)

JVM 允许将64位操作读写分为两个32bits操作

当多个线程读取或写入非volatile 或 非 同步语句下的64bits(long double)类型的时候，不同的线程读可能会只读到高32bits也可能会读取到底32bits,这样我们获取到的数据就是错误的数据


解决上面的问题
1.volatile 修饰
2.锁保护起来

```
### 3.1.3 加锁与可见性
```
A 线程  
y=1
locl M
x=1
unlock M

B 线程 
lock M
i=1
unlock M
j=y

A 线程先执行
A 释放 M锁
B执行获取M锁


B 在获取和A使用同一把M的锁的时候 B能看到A释放锁前做的所欲修改变量的值
note:同一个锁才可见

```
### 3.1.4 Volatile变量
```
volatile 变量
作用:
  修改数据 会通知所有线程,对所有线程可见
  编译器和运行时CPU都不会对该变量进行重排序等优化


 局限性：
  volatile 变量  例如 count++,不能表示该操作时原子性的
  加lock 在同步代码块中可以确保count++ 的原子性可见性,而volatile 只能保证 count 修改值后的可见性
  note:
     count++ 操作流程  读-修改-写 
```

## 3.2发布和溢出
## 3.3 线程封闭
```
什么事线程封闭:
   只在单线程访问数据
 Swing:
    将所有的执行都分发到分发线程执行,其他线程就不能对这些数据修改操作

JDBC:
     Servlet 或 Ejb调的时候都是单个线程调用,连接池获取Connnection对象使用都是在单独一个线程里面使用


java语言及核心库提供了一些机制来维持线程封闭性
  例如ThreadLocal类等

```
### 3.3.1 Ad-hoc线程封闭
```java
volatile变量上存在一种特殊的线程封闭
  只要确保只有唯一的一个线程能够写入volatile 变量,那么在共享变量上,执行
  读-修改-写 操作是安全的

```
### 3.3.2 栈封闭
```java
局部变量的固有属性之一就是封闭在执行线程中
```
### ThreadLocal类
```java
public class ThreadLocalTest {

	private static ThreadLocal<Connection> connectHolder = new ThreadLocal<Connection>() {
		protected Connection initialValue() {
			Connection connection = null;
			try {
				connection = DriverManager.getConnection("");
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			return connection;
		};
	};

	public static void main(String[] args) {
		Connection connection = connectHolder.get();
	}

}


ThreadLocal 使用场景
  频繁操作需要一个临时变量,作为缓存值,这个值只能对当前线程缓存

note:
  现成初次调用ThreadLocal.get,会调用initialValue() 函数来获取初始值,
  ThreadLocal<T> 类似 Map<Thread,T>,保存了特定的线程的值
  
  实际情况:
	是将这些ThreadLocal线程的值保存在Thread对象中
	thread 终止后这些值会被作为垃圾回收

```
## 3.4 不变性
```
满足同步需求的另一种空方法是使用不可变对象(对象创建后,其状态就不能被修改)
线程安全性是不可变对象的固有属性之一，不变性条件是由构造函数创建的

不可变对象状态是由构造函数控制的


对象不可变的条件:
1.对象创建以后，其状态不能修改
2.随想的所有域都可是final 类型
3.对象正确创建(在对象创建期间this引用没有逸出)

```
### 3.4.1 final 域
```java
final 用处
1.final 类型的域不能修改
2.java 内存模型 保证 final 域初始化的过程是安全的
```
### 3.4.2 示例:使用Volatile类型来发布不可变的对象
```java
class OneValueCache {
	private final BigInteger lastNum;
	private final BigInteger[] lastFactors;
	
	public OneValueCache(BigInteger lastNum) {
		this.lastNum=lastNum;
		
	    /*
	     * 下面这个是一些计算或一些耗时的其他操作获取数据
	     * */
		this.lastFactors = new BigInteger[10];
	}
	
	public BigInteger[] getlastFactors() {
		
		return lastFactors;
	}
}


1.不可变对象，当线程获得该对象的引用就不必担心会修改变量的状态
2.如果更新变量可以重新创建一个容器



	private volatile OneValueCache cache;

	public OneValueCache updateCache() {

		cache = new OneValueCache(new BigInteger("1"));

		return cache;
	}

	volatile 修饰 cache 每次更新其他线程都能看到
    volatile  确保其他线程的课件性
```
## 3.5 安全发布
```java

class Holder {

}

public class Demo04_01 {

	public Holder holder;

	public void initValue() {
		holder = new Holder();
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}



存在哪些问题:
 public Holder holder;

 其他线程看到holder 可能不一致,不能保证一个线程执行initValue()其他线程都能
 立即看到

```
### 3.5.1 不正确的发布:正确的对象被破坏
```java
class Demo04_02_1 {
	private int n;

	public Demo04_02_1(int n) {
		this.n = n;
	}

	public void assertSanity() {
		if(n!=n) {
			throw new AssertionError("Thies statement is false");
		}
	}
}



线程A 
  this.a=new Demo04_02_1()

线程B
  this.a.assertSanity()



note:
   未正确发布对象
    A 线程 能看到 this.a
    B 线程 
		情况 1  this.a 为null
	    情况 2 this.a.n 未 旧值(失效值)




	public void assertSanity() {
		第一个n 读取的是失效值
		第二个n 读取的是新值
		if(n!=n) {
			throw new AssertionError("Thies statement is false");
		}
	}



```
### 3.5.2 不可变对象与初始化安全性
```
Java内存模型为不可变对象共享提供了一种特殊的初始化安全性保证

note:
    this.a=new Demo04_02_1()
	this.a 引用对于其他线程可见,并不意味着this.a对象里面的元素（状态）对其他线程可见

为了解决上面出现的问题(引用和对象状态可见性问题),需要使用同步

一方面安全创建对象(不使用同步也能安全的构造方式)
  1.正确构造对象
  2.对象里面的状态都是final 域不可变


任何线程都可以在不需要额外同步的情况下安全的访问不可变对象

这种保证(安全性保证) 只能延续到构造函数将所有final域数据全部初始化


note:
  final 指向的对象里面的状态是可变的,对象状态修改仍然需要同步

```
### 3.5.3 安全发布的常用模式
```java
1.如何使用对象线程能够看到该对象处于发布状态?

	安全发布对象,对象的引用和对象的状态对其他线程的可见
    如何正确构造,并安全发布
	1.静态初始化函数中初始化一个对象引用
	2.对象的引用保存到volatile类型，或AtomicReferance对象中
	3.将对象引用保存到正确的构造对象的final类型域中
	4.对象的引用保存到一个由锁保护的域中



public class Demo04_02 {
	// 静态对象初始化器 由 JVM在类的初始化阶段执行,JVM本身存在同步机制
	// 通过这种发送发布 任何对象都能够安全的发布
	public static Demo04_02_1 demo04_02_1= new Demo04_02_1(100)
	
	public static void main(String[] args) {

	}
}


2.对象发布后如何对象状态的可见性进行修改?
```
### 3.5.4 事实不可变的对象
```java
事实不可变的对象:对象从技术上来看事可变的,但其状态在发布后不会在改变,这种对象就称为事实不可变的对象

```
### 3.5.5 可变对象
```java
对象在构造后发布,但是修改他的对象状态,只能确保在发布的时候的状态是可见的

```
### 3.5.6 安全的共享对象
```java

```