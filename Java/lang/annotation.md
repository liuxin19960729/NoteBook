# Annotation
```
注解用途
1.编译器信息
  检测错误或隐藏的信息
2.编译时和部署时的处理
  可以处理注解信息用来生成代码或xml 等
3.运行时处理
   注解在运行时检查
```
## 注解基础
```java
	@SuppressWarnings("myMethod1")
	public void myMethod1() {

	}
	
	@SuppressWarnings(value="myMethod2")
	public void myMethod2() {

	}

note:
   当注解只有value 一个元素的时候可以省略 values=
    例如:
        	@SuppressWarnings("myMethod1")





@Target({ElementType.TYPE})
public @interface Test1Anno {

}

@Test1Anno
public class Main

note:
    注解中没有一个元素可以用省略()





@Author(name = "Jane Doe")
@Author(name = "John Smith")
class MyClass { ... }
note: Java SE 8 开始支持重复注解




Overide 和 SuppressWarnings  称为预定义注解

```
## 可以用注解的地方
```java
主机适用于声明:
  类 字段  方法 和 其他元素的声明
Java SE8 开始注解也能应用于类型的使用

1.实例创建
   new @Interned MyObject();
2.类型转换
   myString = (@NonNull String) str;
3.implement 
     class UnmodifiableList<T> implements
        @Readonly List<@Readonly T> { ... }
4.抛出异常声明
  void monitorTemperature() throws
        @Critical TemperatureException { ... }

```

## 声明类型
```java

javadoc 生成文档的时候 会通过 @Documented 注解判断是否需要出现在文档中


@Documented
public @interface XXX{
    String author();
    String date() default "ss";// 默认值设置
}

```
## 预定义注解类型
```java
@Deprecated 被标记的元素已经被抛弃,现在不应该在使用
    编译器检测到该元素在被使用的时候会在编译的时候答应警告信息


@Override
    通知编译器覆盖超类的该元素
     
     如果使用该注解,编译器在编译的时候会检测是否正确覆盖,如果未正确覆盖编译器会生成错误

@SuppressWarnings 
Java语言规范列出了两个类别
   unchecked 抑制未经检查的操作的警告，例如使用原始类型的泛型
   "deprecation"：抑制使用过时方法或类的警告
   "rawtypes"：抑制使用未经参数化的泛型类型的警告
  "serial"：抑制缺少 serialVersionUID 字段的警告。
  "unused"：抑制未使用的代码的警告，如未使用的变量、方法等。




@SafeVarargs


@FunctionalInterface
  Java 8 引入
  java 语言规范函数接口



@Retention

RetentionPolicy.SOURCE -标记的注释仅保留在源代码级别，并被编译器忽略。
RetentionPolicy.CLASS -标记的注释在编译时由编译器保留，但被Java虚拟机（JVM）忽略。
RetentionPolicy.RUNTIME—标记的注释由JVM保留，以便运行时环境可以使用。



@Target
ElementType.ANNOTATION_TYPE可以应用于注释类型。
ElementType.CONSTRUCTOR可以应用于构造函数。
ElementType.FIELD可以应用于字段或属性。
ElementType.LOCAL_VARIABLE可以应用于局部变量。
ElementType.METHOD可以应用于方法级注释。
ElementType.PACKAGE可以应用于包声明。
ElementType.PARAMETER可以应用于方法的参数。
ElementType.TYPE可以应用于类的任何元素。

 



@Inherited
注解类型可以从超类继承
此注释仅适用于类声明。
    note:必须声明为@Retention(RetentionPolicy.RUNTIME)
    父类使用了@Inherited的主机
    子类没有使用该注解也可以获得@Inherited相关的注解
@Repeatable
在Java SE 8中引入，表明标记的注释可以多次应用于同一声明或类型使用。详细信息请参见 重复注释

```
## 类型注解可以插入类型系统
```java
note:
  Java8之前注解只能用于声明
  Java8开始注解可以用于任何类型使用


@NonNull String str;
确保str 永远不应该为null
编译器在编译的时候检查到可能出现null 则会答应警告

```
## 重复注解
```java
import java.lang.annotation.Repeatable;

@Repeatable(Schedules.class)
public @interface Schedule {
  String dayOfMonth() default "first";
  String dayOfWeek() default "Mon";
  int hour() default 12;
}


```