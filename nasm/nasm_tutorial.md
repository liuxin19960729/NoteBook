[汇编教程](https://cs.lmu.edu/~ray/notes/nasmtutorial/)
```


rax rbx rcx rdx rsp  rpb rsi rdi


lowerest  32-bits 
eax ebx ecx edx esp epb  esi edi


lowerest  16-bits 
ax   bx  cx  dx sp  pb  si  di


lowerest 8-bits 
al   bl  cl  dl spl pbl sil  dil


for historical reasons,bits 15 through 8  .... are named:
ah ch dh bh





there are 16 xmm register,each 128 bits wide ,named:

XMM0  ..................XMM15

```

## Memory Operands
```
[num]
[reg]
[reg+reg*scale]  note: scale is 1,2,4, or 8 only
[reg + number]
[reg +reg*scale +number]


note:
    The number is  called  the displacement ;
    the plain register is called the base; 
    the register with the scale is called the index.

examples:
 [750] ; displacement only 
 [rbp] ; base register only
 [rcx+rsi*4]; base + index* scale
 [rbp+rdx] ;base+index*1
 [rbx-8] ;displacement is -8
 [rax +rid*8+500] ;base + index*scale(8) + displacement;
```
## Immediate Operands
```
200 ; decimal



xx0d suffix is decimal
0dxx 0d prefex is decimal

0200 ; decimal  note: the leaading 0 dose not make  it octal
0200d ;explicitly decimal  -d suffix
0d200 ;also decimal -0d prefex





08ch ;hex   0xxh
0xc8 ;hex  
0hcb ;hex -for some reason name like 0h


310q  octal  - q suffix
0qd10 octal  -0q prefix

11001000b ;binary - b suffix
0b1100_1000 ;binary  -0b prefix, and by thei way ,underscores are allowed

```
## Instructions with two memory operands are extremely rare(adj 少见的)
```
add reg,reg
add reg,mem
add reg,imm
add mem,reg
add meme,imm
```
## Defining Data and Reserving (reserve v  reserving adj 预留) Space
```
db 0x55; just the byte 0x55;
db 0x55,0x56;two bytes in succession

db 'a',0x55 ;character constants are OK

dw 0x1234 ; 0x34 0x12 little endian

dw 'a' ;0x61 0x00;
dw 'ab' ;0x61 0x62

dw 'abc' ; 0x61 0x62 0x63 0x00

dd 0x12345678; 0x78 0x56 0x34 0x12

dd 1.234567e20 ;floating-point constant

dq    0x123456789abcdef0  ; eight byte constant
dq    1.234567e20         ; double-precision float
dt    1.234567e20         ; extended-precision float


To reserve space (without initializing),you can thie following psedudo instructions.They should go in a seciton called .bss
    note:
        you'll get an errorif you try to use them in a .text .section 


    buffer:  resb 64; reserve 64 bytes
    wordvar: resw 1  ;reserve a word
    realarray: resq 10 ;array of ten rasls

```
```
cmp does a comparison
je  is equal 
jne  not equal 
jl  less 
jnl not less
jg greater 
jng not greater
jle less or equal 
jnle not less or equal
jge greater or equal
jnnge not greater or equal

.....so so
```
## Using C Library
```
_start label
_start  does some inilication, it calls main,then it does clean up,
then it issues the system call for exit.
So you just have to replement main. 
```
## Understaidng Calling Conventions
```
From left to right, pass as many parameters as will fit in registers. The order in which registers are allocated, are:


For integers and pointers, rdi, rsi, rdx, rcx, r8, r9.

For floating-point (float, double), xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7.


note:
  Additional parameters are pushed on the stack,right to  left ,and are to be removed by the calleer after call;



fter the parameters are pushed, the call instruction is made, so when the called function gets control, the return address is at [rsp], the first memory parameter is at [rsp+8], etc.


[
    two parameters; [rsp+16]
    one parameters; [rsp+8]
    call address; 
]





function return  a  integer value by using rax ;
function return  a  float  value by using xmm1 :xmm0 ;


```
## Mixing C and Assembly Language
```

        global  maxofthree
        section .text
maxofthree:
        mov     rax, rdi                ; result (rax) initially holds x
        cmp     rax, rsi                ; is x less than y?
        ; if(x < y ) x=y
        cmovl   rax, rsi                ; if so, set result to y
        cmp     rax, rdx                ; is max(x,y) less than z?
        ; if(x< z) x=z
        cmovl   rax, rdx                ; if so, set result to z
        ret                             ; the max will be in rax




上面的汇编是 下面函数原型
int64_t maxofthree(int64_t x, int64_t y, int64_t z){
    int64_t value=x;

    if(x<y){
        x=y
    }

    if(x<z){
        x=z
    }
    return value;
}
rdi, rsi, rdx, 分别是  x ,y z 
```
## Conditional Instruction
```
After an arithmetic(n 计算) or logic instruction,or thie compare instruction,
cmp ,the processor sets or clear bits in its rflags. The most intersting flags are:
s (sign)
z (zero)
c (carry/进位)
o (overflow)


The conditional instructions have three base forms:
1. j for conditional jump, 
2. cmov for conditional move,and set for condition set
3. The suffix of the instrustion has one of the 30 forms :
    s ns z nz c nc o no p np pe po e ne l nl le nle g ng ge nge a na ae nae b nb be nbe.

```

## Command Line Arguments
```
int main(int argc,char *[] argv)

argc will end up rdi, and 
argv (a pointer )will ened up in  rsi.
 

```
## A Longer Example
```
Note that as far as the C Library is concerned ,command line 
arguments are always strings. if you want to treat them as intergers, call atoi.

Here' s neat(adj 小巧的 简洁的) program to compute x^y


```