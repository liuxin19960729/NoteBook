## 1.7 反汇编引擎的工作原理
```
Intel指令由6部分组成
    1.Instruction prefexies 
       指令前缀作为指令不从信息

    重复指令 rep  repe repz
    跨段指令 mov dword ptr fs:[xxx],0
    32位转换为16位  mov ax,word ptr ds:[eax]     
    16位转换为32位  mov eax,dword ptr ds:[bx+si]    

    note:
        ptr 表示一个指针 内存地址

    2.Opcode 
         mov
         jmp
         call
         ....

  
         note:
            解析Opcode是反汇编主要的工作 

    3.Mode R/M (1 byte)
        辅助Opcode解释汇编指令助记符的操作数类型
        M:内存单元
        R:寄存器
        
        0-2:bits:
            寄存器/内存单元
        3-5:bits
           用来辅助前面Opcode
        6-7:(4 种状态)
             状态1:.0-2 bits是寄存器还是内存单元
             状态2-4: 3 种寻址方式
             
        
    4.SIB
      辅助Mode R/M 计算偏移地址
       
       SIB 寻找方式=基址+变址
        
        例如:
            mov eax ,dword ptr ds:[ebx+ecx*2]
            SIB 结构 *2 就是SIB 指定
            0-2 bits:
                自定基址寄存器
            3-5 bits：
                变值寄存器
            
            6-7:bits
                 用于指定乘数 2bits 表示4中状态 分别为
                 1 2 4 8


    5.Displacement 计算偏移量
        辅助Mode R/M 计算偏移地址
         Displacement 用于辅助 SIB

         mov eax,dword ptr ds:[ebx+ecx*2+3]

         note: +3 就是 displacement 指定
         


    6.Immediate
        指令操作数作为常量的一个值


反汇编引擎用过查表由上面6种方盒组合而成的汇编码解释为对应的汇编指令


例如


1. push 立即数 32 bits or 16 bits
push  imm32
push 指令 opcode 0x86

例如当前机器码 小端
68 00304000
   0x 00  40 30 00 
  
   32 bits 模式下 默认 push 32bits 大小

push 指令 opcode 0x86
PUSH imm16
   
   32 bits 模式 如果需要push 16 bits 需要 指定 push double num;




2. push  16bits立即数
  	PUSH imm8

push 指令 opcode 6A
  1.有符号判断
  if(opcode[i+1]>=0x80){//0x80 = 1000 0000 B
     // byte 是负数
  }else{// 正数
    
  }





```