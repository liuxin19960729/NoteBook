# 相同的功能不同的代码
```
学习目标:
  1.另一种分段方式访问分段内存机制
  2.两种非顺序的的流程控制方法
    2.1循环
    2.2条件转移
 
  3.新指令认识
    movsb movsw inc dec cld std div neg cbw cwd sub idiv jcxz cmp 等

 4.INTEL 8086  FLAGS 的标志位 

 5.认识计算机中的负数

 6.Bochs 调试的更多技巧(查看FLAGS寄存器的格个标志的状态....)

```
## 7.1 代码清单
[c07_mbr](./c07_mbr.asm)

## 7.2 跳过非指令数据区
## 7.3 在数据声明中使用字面值
```
1.nasm  中\ 符号可以作为续行符,当一行写不下时可以在行尾使用 \ 符号 表示下一行的内容和我门这一行合并为一行



 message db '1+2+3+...+100=' ;声明非指令数据
 note:
    编译器会把 上面的字符转换为ASCII 码

```
## 7.4 断地址初始化
```
将默认的CS:IP 0x0000:0x7c00, 

我们可以设置CS:IP 0x07c0:0x0000
  
```
## 7.5 段之间的批量数据传送
```
move string byte word
movsb,movsw 默认只执行一次

执行前的准备:
DS:SI 原始数据传的段地址:偏移地址
ES:DI  目标位置段地址:偏移地址

正向:低地址->高地址
   SI ,DI 传送一次自动+1
反向:高地址->低地址
    SI ,DI 传送一次自动-1


cx 计算器指定 rep 重复次数
rep movsw/movsb  

note 每次执行 movsw/movsp 执行之前必须检查 cx 是否为0


特殊寄存器 FLAGS(标志寄存器)
  1.ZF(6bit)
    cpu 执行一条算术活泼逻辑运算指令,算数逻辑部件送出的结果除了运送到指定的位置,还送到一个或非门(输入全为0 输出为1,输如不全为0 或全部为1 则输出为0 )。

```
![8086的处理器的标志寄存器](./images/8086的处理器的标志寄存器.jpg)
```
FLAGS 寄存器 可以通过改变标志位来改变处理器的运行状态


例如:
  DF(Direction Flag):
    通过对 DF 设置 0 1 来设置movsb 和 movsw 传送的方向
    cld DF=0 低->高
    std DF=1 高->低



note:
   单纯的movsb movsw 只能执行一次 
   rep movsb  or  rep movsw  则会重复的 CX 为 0 结束

```
## 7.6 使用循环分解数位
```
loop digit 
    CX : 指定 循环的次数
    loop 重复执行一段相同的代码
    CX= CX -1
    if(CX!=0){
       jmp digit;
    }


编译器 计算位置 (会被编译器计算出相对于当前 loop 的相对位置)
     digit = 标号汇地址 -下一条汇编地址 




note:
    在8086处理器上只有 bx si di bp 来提供偏移地址
mov[bx]
mov[si]
mov[di]
mov[bp]

  note:
      bx最初的功能就是提供数据访问的基地址


每个寄存最初设计都有自己的特殊用途
  ax:累加器
  cx:计数器
  dx:数据寄存器,还用于和外部设备之间数据传送
  si:(source index) 寄存器 
  di:(destination index) 寄存 



add bx ,1
or
inc al
inc byte [bx] ; segement<<4+bx 内存地址的内容 +1
inc word [label_a] ;


dec al; al register 内容 -1


```
## 7.7 计算机中的负数
### 7.7.1 无符号数和有符号数
```

-1 编译器编译后
0xff=1111 111B=0x00-0x01 =......ffff 

-2 
0000 0000 B -0000 0010 =1111 1110 B =0xFE


note:
  db 0xff 在内存中都是一样,怎样来区分该数据是负数或者正数 
  10 进制 255 or -1 

  计算机将数分为两大类:无符号数和有符号数 
  

  unsgined number
     0000 0000 --> 1111 1111  (0-255)


  singed number

    最高位来判断正负 
       1 负数
       0 正数



  0000 0000 
- 1000 0000
  1000 0000 (十进制128)

  0000 0000
 -1111 1111   (0-(-1)=1)
  0000 0001  (10 进制 1)



8086 指令 neg  

  neg al
  neg dx
  neg word [label_a]


  功能:
    0-指定操作数


neg al,
 若 al内容  00001000
 neg al 
   0-0000 1000 = 1111 1000
 

 若 al 110001000(10进制 -60)
    neg al

     0000 0000
    -1100 0100
     0011 1100  (60)

  
note:
  1. 不要给编译器添加麻烦,   
  如果一个数的范围超过了内存or 寄存器返回会被截断



```