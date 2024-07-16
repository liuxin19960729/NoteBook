## 2.1 C Language
```
ANSI C标准
尽管ANSI 标准章节合并为ISO标准,但是ANSI 标准并不是 ISO 标准
ANSI标准存在两种形式,通常被称为C89,偶尔称为C90标准

1.
GCCANSI 标准
    -ansi -std=c90
    -std=iso9899:1990


要获得ANSI标准的检查诊断 还应该指定
  -pedantic ,(如果希望它们是错误而不是警告，则指定-pedantic-errors)


1990年ISO C标准中的错误在1994年和1996年出版的两个技术勘误中得到了纠正。 GCC不支持未更正的版本。

3.
1995 年巩固对 1990 年标准的修,并增加了 __STDC_VERSION__ 和   digraphs 
   修正后的标准被称为C94或C95
   
   -std= iso 9899：199409

   要获得ANSI标准的检查诊断 还应该指定
   -pedantic ,(如果希望它们是错误而不是警告，则指定-pedantic-errors)


3.
ISO 标准的新版本于1999年发布,称为ISO/IEC 9899：1999 通常称为 C99
  note: gcc 基本上完全支持了这个标准
  -std=c99
  or
  -std= iso 9899：1999



4.
1999年ISO C标准中的错误在2001年、2004年和2007年出版的三个技术勘误中得到了纠正。 GCC不支持未更正的版本。
  
   C标准的第四个标准,于2011年作为ISO/IEC 9899：2011发布
        note:GCC 基本完全支持了该标准
        -std=c11  or -std= iso 9899：201
   


5.
  017年编制了集成了校正的版本，并于2018年发布为ISO/IEC 9899：2018;它被称为C17，并支持
  
  -std=c17或-std= iso 9899：2017



note:
  C17 矫正版本也适用C11 
  区别:
     C17和 C11 的 __STDC_VERSION__ 值不同
    



6. C2X正在开发
    开启实验furture和不完全支持furture:
        -std=c2x 



GCC 编译器为C语言提供了一些扩展
    一些ISO新标准在老版本被扩展实现
    note:
       
       1.通过上面的执行标准方式可以禁用GCC的扩展
       
       2.开启扩展
        -std=gnu 90
        -std=gnu 99
        -std=gun 11


gcc 11.4
  如果不指定 -std 选型 默认使用 -std gun17




```