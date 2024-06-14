# 7 取消与关闭
```
Java没有提供任何机制来安全,快速的,可靠的停下来

Java 提供了中断(Interruption)
    作用:
        使一个线程中断指定线程的工作


行为良好的软件:
    1.完善的处理失败,关闭,和取 
```
## 7.1 任务取消
```java
可取消任务: 任务在正常完成之前可以将其置入“完成状态”

任务取消应用案例:
    1.图形界面用户点击取消操作
    2.有时间限制的操作
    3.多个任务每个任务根据不同的要求做某件事情,当某个任务事情做完,需要去取消那些没有作为的任务
    4.爬虫爬取任务,需要存储的磁盘已经满了,需要取消爬取的任务
    5.服务器平缓关闭,需要先取消当前所有的任务在关闭



java 没有安全的抢占式的方式停止线程，因此没有安全的抢占式方法来停止任务
只有协作式的机制(使请求取消的任务和代码遵守一种协商好的协议)


1.协作方式一
  将任务标志设置成已请求取消,任务定期的查看该标志,如果设置了标志,将提前结束任务



public class PrimeGenerator implements Runnable {
	private final List<BigInteger> primes = new ArrayList<BigInteger>();

	private volatile boolean cancelled;

	@Override
	public void run() {
		// TODO Auto-generated method stub

		BigInteger p = BigInteger.ONE;

		while (!cancelled) {
			p=p.nextProbablePrime();
			synchronized (this) {
				primes.add(p);
			}
		}
		
		System.out.println("PrimeGenerator 结束");

	}

	public void cancel() {
		System.out.println("cancel");
		cancelled = true;
	}

	public synchronized List<BigInteger> get() {
		return new ArrayList<BigInteger>(primes);
	}
	
	public static void main(String[] args) {
		
		PrimeGenerator primeGenerator=new PrimeGenerator();
		
		Thread thread =new Thread(primeGenerator);
		thread.start();
			
		
		try {
			Thread.sleep(2000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			primeGenerator.cancel();
		}
		
	}
}

考虑现实生活中停止支付
    请求
        那些响应性保证
    停止支付(支付中断)
        循序指定流程(通知事务中涉及的其他银行,付款账户的评估)

```
### 7.1.1 中断
```java
上面 PrimeGenerator 会出现一个问题
  如果线程正在阻塞

另一个线程执行
    primeGenerator.cancel();
也不会立即停止(会一直等待到阻塞返回)



note:
  前面第5章提及到一些阻塞库支持中断,
  中断是一种协作机制

  每个线程都有一个终端状态
  thread.isInterrupted() 

  线程发生中断
  
  public class TestInterrupt {

	private class TestThread extends Thread {

		@Override
		public void run() {

			try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				try {
					Thread.sleep(2000);
				} catch (InterruptedException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
			}

		}
	}

	public static void main(String[] args) {
		Thread thread = new TestInterrupt().new TestThread();
		thread.start();
		try {
			Thread.sleep(10);
			System.out.println(thread.isInterrupted());
			thread.interrupt();//中断目标线程  isInterrupted 设置为true
			System.out.println(thread.isInterrupted());
            
			thread.join();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			System.out.println(thread.isInterrupted());
		}

	}

} 

  isInterrupted() 为 true 
  1.发生中断
  2.线程还活着 


Thread.interrupted()
    清除当前线程的中断状态



Thread.sleep 和 Object.wait()
    都会检查线程何时中断 
	发现中断提前返回


   响应中断步骤:
		1.清除中断状态
		2.抛出 throw  InterruptedException

	    note: 
		     不触发抛出 InterruptedException 则isInterrupted() 状态不会清除

	private class TestThread extends Thread {

		@Override
		public void run() {

			try {
				Thread.sleep(1000); // 清除中断状态  抛出 throw  InterruptedException
			} catch (InterruptedException e) {
				// 中断状态已经被清除
			
				// TODO Auto-generated catch block
				//
				System.out.println(this.isInterrupted());// false
				e.printStackTrace();
				/*
				 * try { Thread.sleep(2000); } catch (InterruptedException e1) { // TODO
				 * Auto-generated catch block e1.printStackTrace(); }
				 */

			}

		}
	}




中断正确理解:
	1.正在运行的线程不会被中断(只是发出中断请求)
	  会在何时的时机中断自己(该时机被称为终端状态取消点)
	2.object.wait() Thread.sleep() thread.join()
		2.1收到终端请求
		2.2发现被设置成了中断状态

		以上两种情况当前线程会抛出InterruptedException异常




	note:
	   在使用interrupted()因该小心(会清除中断状态)
	  	
		public static boolean interrupted() {
           return currentThread().isInterrupted(true); true 获取当前中断状态 并且清楚中断状态
		}
	

	  通常中断是实现取消最合理的机制
	



run(){
	while(!Thread.current().isInterrupted()){// 非终端状态
	try{
		queue.put(xxx);//blocking queue 阻塞  另一个线程请求中断会抛出 InterruptedException
	}cactch(InterruptedException e){
		//终端退出线程
	}
}
}

cancel(){
	interrupt();
}

```
### 7.1.2 中断策略
```
中断策略规定线程如何解释某个中断请求,发现中断的时候因该做哪些工作,哪些工作单元对于中断来说是原子的操作,以及多快的速度来响应中断

```