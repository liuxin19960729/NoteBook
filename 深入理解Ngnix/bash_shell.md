# Bash Shell
## Shell 文件包含
```shell
1.
. filename


2.
source filename

```
## 输入输出重定向
``` shell


ls -al > ls.txt
将 ls-al 的输出的内容重定向写入到 ls.txt 中 覆盖写入



 ls -al >> ls.txt
 将内容追加到ls.txt 中



ws -l filename
行数 filename

wc -l <  ls.txt
行数

wc -l 命令 获取ls.txt文件输入

note:
    重定向  wc 从标准输入获得   和 直接重文件读取获得输出的内容不一样



cat <ls.txt  >ls2.txt
ls 读取作为标准输入被cat 读取,cat 将标准输出重定向到ls2.txt 文件写入

<<tag
  输入重定向
  tag 作为输入结束的标记

```
### 重定向深入讲解
```shell
0 标准输入
1 标准输出
2 标准错误

cat ls2.txt 2>ls3.tx
note:
  覆盖写入
读取 ls2.txt 内容 并且将标准错误重定向到 ls3.tx中 


cat ls100.txt 2>>ls3.tx
    note:
        append 写入



cat ls.txt >>ls3.txt 2>&1
合并输出   2>&1 将标准输出和标准错误合并并且从定向到 ls3.txt append 输出

cat ls.txt >ls3.txt 2>&1
note:
  和上面一样 只是是覆盖内容输出到文件

```
### 特殊重定向
```shell
1.
commond << delimiter
     document
delimiter

将 delimiter 之间的内容传递给commond


note:
  delimiter 前后不能有任何字符(包括 空格和tab缩进)
  

2.
/dev/null
从定向到 /dev/null 不会输出到屏幕和任何文件

```
## test 命令
```
-d 文件是否存在
-z 
  test -z 字符串
  判断字符串长度是否是0

```

## uname 命令
```
-s 
  print the kernel name

   例如
    Linux
-r
   print the kernel name

    例如
    5.15.0-71-generic
-m  
    print the machine hardware name

    例如
    x86_64  

```

## ps 命令
```
获取当前进程的快照

-e
  Select all processes.  Identical to -A.
  和 -A 一样

-f
  输出格式选项


```
## kill 命令
```
-s,--signal
  

kill -s  xxx  <pid>
  对指定进程发送信号
  




```