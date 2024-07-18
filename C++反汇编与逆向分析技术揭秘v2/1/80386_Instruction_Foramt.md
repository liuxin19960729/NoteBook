# 80386 Instruction Format 
```
Prefix:(每个前缀1byte 不超过4个选项)
  1.instruction prfex
  2.address size prefix
  3.operand(操作数)  size prefix 
  4.segment override 
  
push imm32 or push imm16
0x68=0 110 1000
     0: instruction prfex
     1:address size prefix
     1:operand size prefix
     0:segment override 


Required
  
                0x4A 0x4B 0x4c  0x4d
    1149:       f3  0f    1e    fa             endbr64
                0x4e
    114d:       55                      push   %rbp
                0x4f 0x50 0x51
    114e:       48   89   e5                mov    %rsp,%rbp
    1151:       48 83 ec 10             sub    $0x10,%rsp
    1155:       48 c7 45 f8 64 00 00    movq   $0x64,-0x8(%rbp)
    115c:       00
    115d:       48 8b 45 f8             mov    -0x8(%rbp),%rax
    1161:       89 45 f4                mov    %eax,-0xc(%rbp)
    1164:       8b 45 f4                mov    -0xc(%rbp),%eax
    1167:       89 c6                   mov    %eax,%esi
    1169:       48 8d 05 94 0e 00 00    lea    0xe94(%rip),%rax        # 2004 <_IO_stdin_used+0x4>
    1170:       48 89 c7                mov    %rax,%rdi
    1173:       b8 00 00 00 00          mov    $0x0,%eax
    1178:       e8 d3 fe ff ff          call   1050 <printf@plt>
    117d:       90                      nop
    117e:       c9                      leave
    117f:       c3                      ret
```