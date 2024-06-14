# 构造函数语意学
```

cin << intVal;


编译器 不会分析出上面的是错误的会找到
   
  1.cin  不包含 <<
  2.会使用内建的 operator << 左操作符号
  3.编译会在cin 找到合适的转换运算符号
      operator int();


 4.被编译为
    
    int temp =cin.operator int();
    temp << intVal; 





显示关键词
explicit 
```
##  2.1Default Constructor的构造操作
```c

class Foo
{
public:
    int val;
    Foo *pnext;
}


/**
 * c++ standard:
 * 如果用户未在class 声明出 constructor
 * 则 default constructor 会被隐式(implicitly) 声明  
 * 
 * 
 * 
*/

void
foo_bar()
{   
    Foo bar;
    if (bar.val||bar.pnext)
    {
        
    }
    
}



编译器和成nontrival default constructor 的四种情况 

1.带有Default Contructor 的Member Class Object

    class A{

        private:
            B b;// b 含有 Default Contructor
            char *str;
    }



   上面这种情况是 notrival

  
    编译器会在AClass 真正使用的时候合成一个 default constructor 

    note:
      c++ 为了在不在每个模块由编译器生成默认的构造函数,析构函数..... 编译器把这些合成的函数合成为 inline 方式




A default constructor 
    编译器合成的constructor 

    // c++伪代码
inline Bar::Bar(){
    foo.Foo::Foo();//调用Foo() 的默认构造函数
}




note:
  如果程序员自定义构造函数



    里面有 B b object memeber ,并且B b
    包含Default Construtor ,由于一定显示的定义
    了Constructor ,编译器不能定义第二个无参构造函数


    编译器会做以下事情:
         class A 里面包含一个以上object members
         编译器会扩展自定义的constructor
         会为未初始化的对象调用 default Constructor

         
    A::A(){
        foo.Foo::Foo();//编译器扩张 出来的代码
        str=0;

    }






例2:

    class Dopey
{
public:
    Dopey() {}
};

class Sneezy
{
public:
    Sneezy() {}
    Sneezy(int) {}
};

class Bashful
{
public:
    Bashful() {}
};

class Snow_White
{
public:
    Dopey depey;
    Sneezy sneezy;
    Bashful bashful;

private:
    int mumble;
};



Snow_White 没有定义 constructor
  会被编译器合成 nontrivial constructor

合成的default constructor
Snow_White::Snow_White(){
    depey.Dopey::Dopey();
    sneezy.Sneezy::Sneezy();
    bashful.Bashful::Bashful();
}


程序员写的

Snow_White::Snow_White()：sneezy(2024){
    numble=2048;
}


由于包含有未被初始化的对象编译器会扩展程序员写的构造函数






//cpp 伪代码
Snow_White::Snow_White()：sneezy(2024){

    //编译器implicit 扩张出来的代码 
    depey.Dopey::Dopey();
    sneezy.Sneezy::Sneezy()2024;
    bashful.Bashful::Bashful();

    // explicit user code
    numble=2048;
}


```
### 带有 Default Constructor 的Base Class
```
如果没有任何constructors 的class 派生自一个带有default constructor 的那么这个 derived class 的 default constructor 会被视为nontrival.



如果设计者实现了多个constructor ,其中没有default constructor,编译器会扩张现有的每一个constructors
将掉许所必要的default constructors 的程序代码加进去
  
  note:
      derived class 通过设计者自己实现了constructor ,编译器并不会自己实现default construcotr(哪怕设计者自己没有实现无参构造)



derived class 合成 or 扩张的构造会
会扩展调用上一层的 base classes



note:
  如果 derived class 有 object memebers 
  则 编译器会扩张 or  合成 default constructor

  1.先base classes constructor 调用 
  2.设计者自己实现的代码
  3.object member 的初始化
```
### 带有一个Virtual Function 的Class
```cpp
有两种情况也要合成defaut constructor

1.class 声明(或继承)一个 virtual function

2.class 派生自一个继承串链,其中有一个或多个 virtual base blasses。



不管上面量两种情况的那种情,由于缺乏user constructors,
编译器会合成一个default constructor 的必要信息



class Widget
{
public:
    virtual void flip() = 0;
};

void flip(const Widget &widget)
{
    widget.flip();
}

void foo()
{
}

int main(int argc, char *argv[])
{

    return 0;
}





1.编译器会产生出来 virtual function table ,并且在虚表中设置
虚函数的指针

2. 编译器会把 vptr(虚表指针) 合并到 class object 里面




void flip(const Widget &widget)
{
    widget.flip(); 
    // cpp 会改写成
    // (*widget.vptr[1])(&widget)
}


note:
    编译器会为每个 Widget(或者Widget 派生类) 的 object 设定初始值,
    编译器会为每个virtual class 的 constructor 插入一次代码,来做虚表
    slot 绑定初始化等操作

```
### 带有一个Virtual Base Class的 Class
```cpp

class X
{
public:
    int i;
};

class A : public virtual X
{
public:
    int j;
};

class B : public virtual X
{
public:
    double d;
};

class C : public A, public B
{
public:
    int k;
};



void foo(A *pa)
{
    // note:  无法在编译的时期判断出 pa->X::i 的位置
    pa->i = 1024;
    // 编译器会把上面这一行改成 pa->_vbcX->i=1024
}

int main(int argc, char const *argv[])
{

    foo(new A);
    foo(new C);

    return 0;
}


note:
  virtual base class 的实现法在不同的编译器之间有极大的差异
 


pa->__vbcX->i=1024
   __vbcX 编译器产生的指针,指向virtual base X; 


    编译器会合成或安插virtual base class 的执行期间存取的代码

```
### 总结
```
编译器合成或安插constructor代码组要是为了
1.member object 构造初始化
2.base class 被基类默认调用
3.virtual function 
4. virtual base class
  虚表初始化和绑定



note:
    含有 base class subobjects 和  members class objects 会在default constructor
    初始化,
    nonstatic data (整数,整数指针,帧数数组等)都不会被初始化


    上面这些初始化操作,对于编译器来说不是必须的,需要设计者根据设计自行初始化



CPP新手的两个常见误解
    1.任何没有定义default constructor 都会被合成一个出来
        
    2.编译器和成default constructor 会初始化每个 data member
       note:
          只会初始化有default construcot member object
```
## 2.2 Copy Constructor
```cpp
class X
{
};

/**
 * 三种会以object 的内容作为另一个class object 的初始值
 *
 *
 */

X x;

/**
 * 显示的以一个object的内容作为另一个 class object的初始值
 */
X xx = x;

extern void foo(X x);

void bar()
{
    X xx;
    /**
     * xx 作为foo的一个参数的初始值
     * 隐私的初始化操作
    */
    foo(xx);
}

X foo_bar(){
    X xx;
    /**
     * xx 作为初始值 给返回的class object
     * 隐式的初始化操作
    */
    return xx;
}




显示定义copy constructor

class X
{
public:
    X(const X &x, int = 0);
    X();
};

X::X()
{
}

X::X(const X &x, int a = 0)
{   
    
}
```
### Default Memberwize Initialization
```cpp
若没有显式(explicit) 提供 copy constructor

编译器合成
  一个copy constructor 
  会将内建的或派生的data member(指针或数组)的值 从 other object 拷贝
  到另一个object 上

  note:
    并不会拷贝 member class object



#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
class String_
{
public:
    String_(const char *);
    ~String_();
    char *str;
    void test();
    int len;

private:
};

String_::String_(const char *str)
{
    void *_str = std::malloc(std::strlen(str));
    std::memset(_str, 0, std::strlen(str));
    this->str = (char *)str;
    std::cout << "String_::String_(const char *str)" << std::endl;
}
String_::~String_()
{
}

void String_::test()
{
    if (str != nullptr)
    {
        std::cout << "str: " << str << " len: " << len << std::endl;
    }
    else
    {
        std::cout << "str: nullPtr " << " len: " << len << std::endl;
    }
}

int main(int argc, char const *argv[])
{

    String_ noun("book");
    noun.len = 100;
    String_ cp = noun;

    noun.len = 200;

    noun.test();

    cp.test();

    return 0;
}




打印输出:
String_::String_(const char *str)
str: book len: 200
str: book len: 100


上面的 String_ 会被编译器合成一copy constructor 

根据上面答应可以知道
    指针 数组 非引用类型的成员变量 都会被复制一份




class Word
{
public:
private:
    int _occurs;
    
    // object member
    String_ _word;

};

编译器合成的copy constructor
    1.拷贝非object member 
    2._word =xxx;
       调用copy constructor 的 object member 
       会通过 object member 的 copy constructor 初始化对象成员
       object 也会复制非object member成员和 向上面一样初始化object member




note:
  不是未定义 default constructor 和  copy constructor 会被编译构建出来
  而是编译会根据判断在需要的时候构建出来




class object 可用两种方式赋值得到
    1.初始化 copy constructor 
    2.被指定(assignment) copy assignment operator





决定是否需要编译器合成copy constructor ,需要编译器判断该
class 是否是notrivial 的实例





```
### Bitwise Copy Semantics (位逐次拷贝)
```cpp
Word noun("book");
Word verb = noun;


Word
  1. explicit copy constructor
  设计者定义copy constructor 
  例如
  Word::Word(const Word &word,int a=100,b=200)
 
  verb class object 初始化的时候会调用 设计者定义的copy constructor
  






2.

下面的class 展现了bitwise smantics

class Word
{
public:
    Word(const char *);
    ~Word()
    {
        delete[] str;
    }

private:
    int cnt;
    char *str;
};


3.



class String_
{
public:
    String_(const char *);
    ~String_();
    String_(const String_ &);//显示声明了copy constructor
private:
};

class Word
{
public:
    Word(const Word &word);
    ~Word();

private:
    int cnt;
    String_ str;
};



// 以下声明并未展现出 位逐次拷贝语言

class Word
{
public:
    Word(const String_ &word);
    ~Word();

private:
    int cnt;
    String_ str;
};

编译器会合成copy constructor 

// 伪代码

inline Word::word(const Word &word){
    str=wd.str;
    cnt=wd.cnt;
}


note:
  合并出来的copy constructor ,
  会复制整数数组等等的nonclass members 也会被复制

```
### 什么情况下不需要 编译器合成copy constructor
```
1.
```