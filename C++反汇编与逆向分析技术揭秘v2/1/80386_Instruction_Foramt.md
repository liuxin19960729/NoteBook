# 80386 Instruction Format 
```
Prefix:(每个前缀1byte 不超过4个选项)
  1.instruction prfex (0 or 1 bytes)
  2.address size prefix (0 or 1 bytes)
  3.operand(操作数)  size prefix  (0 or 1 bytes)
  4.segment override (0 or 1 bytes)
  

    例如:


Required:
   opcode:(1 or 2 bytes)
   MOD R/M:(0 or 1 bytes)
   SIB R/M:(0 or 1 bytes)
   Displacement:(0,1,2,OR 4 bytes)
   Immediate:(0,1,2,OR 4 bytes)


``