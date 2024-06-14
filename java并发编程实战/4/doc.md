# 对象的组合
## 4.1 线程安全的类
```java
设计线程安全类的三个基本要素
    1.造成构成对象状态的所有变量
    2.找出约束状态变量的不变性条件
    3.建立对象状态并发访问管理策略



class Counter{
	private long value=0;
	
}


Counter 域只有vlaue 一个状态

对于含有n个基本类型域的对象,其状态就是这些域构成的n元组

例如 LinkedList 的状态就包含了链表节点中所有对象的状态


```
### 4.1.1 收集同步需求
### 4.1.2 依赖状态操作
### 4.1.3 状态的所有权
## 4.2 实例封闭
### 4.2.1 监视器模式
### 4.2.2 示例:车辆追踪问题
## 4.3 线程安全性的委托
### 4.3.2 独立的状态变量
### 4.3.3 当委托失效时
### 4.3.4 发布底层的状态变量
## 4.4 在现有的线程安全类中添加功能
```java
public class BetterVector<E> extends Vector<E> {
	/*
	 * 扩展如果没有则添加的函数
	 * */
	public synchronized boolean putIfAbsent(E x) {
		boolean absent = !contains(x);

		if (!absent)
			add(x);
		;

		return absent;
	}
	
	
}

子类扩展括扩展方法,这种方式很脆弱,如果底层代码改变,扩展的子类灭有同步更新，
则无法有正确性的保证



note:
  Vector 规范中定义同步策略,则BetterVector<E> 不存在上面的问题






public class ListHelper<E> {
	public List<E> list = Collections.synchronizedList(new ArrayList<E>());

	public boolean putAbsent(E x) {
		synchronized (list) {
			boolean absent = !list.contains(x);
			if (absent)
				list.add(x);
			;
			return absent;
		}
	}
}

```
### 4.4.2 组合
```java
public class ImprovedList<E> implements List<E> {

	private final List<E> list;

	public ImprovedList(List<E> list) {
		this.list = this;
	}

	public synchronized boolean putIfAbsent(E x) {
		boolean absent = !list.contains(x);

		if (absent)
			list.add(x);
		;

		return absent;

	}

	@Override
	public synchronized int size() {
		// TODO Auto-generated method stub
		return list.size();
	}

    .....
}


优点 并不关心底层List 是否是线程安全的
可能会造成轻微的性能损失,但是这些都是微不足道的
```
## 将同步策略文档化
```

```