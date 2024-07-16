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
       


    5.Displacement
    6.Immediate
```