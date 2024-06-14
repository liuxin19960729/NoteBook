# 进程API
## wait 系统调用
```
wait() 父进程等待子进程执行完毕
```
## exec 系统调用
```
让子进程和父进程执行不同的程序
从可执行的程序加载代码和静态数据,并覆盖自己的代码段和静态数据段

shell
  wc p3.c >new_file.txt

1.shell 先找到 wc 可执行程序
2.shell fork() 
3.
  3.1 关闭标准输出流
  3.2 带卡文件new_file.txt 文件
  3.3子进程exec() 执行可执行程序
  3.4 将结果写入new_file.txt
  
4.父进程wait 等待子进程执行完,再次输出提示符号


```