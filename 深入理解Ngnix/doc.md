## ngx_modules.c
```c

ngx_modules.c configure 文件生成

ngx_module_t *ngx_modules[] = {
    ....
}

ngx_modules 指明了每个模块在Nginx中的优先级


http 过滤模块 和ngx_modules 数组的顺序相反


```

## Nginx options
### 1.默认启动
```
/xx/xx/..../sbin/nginx

默认启动会读取 /xx/xx/..../conf/nginx.conf 配置文件


note:
  可以在执行 configure 的时候指定 nginx.conf 的配置地址

--conf-path

```

### 2.另行指定配置文件的启动方式
```
nginx -c /...../nginx.conf

```
### 3.另行指定安装目录启动方式
```
nginx -p xxx
```
### 4.另行指定全局配置启动方式
```
nginx -g ""


note:
  如果是全局配置的方式启动,则如果需要该Nginx 执行执行其他命令
  如果不带上 -g "" 那么就找不到pid 文件


例如
nginx - g "" -s stop

```

### 5.不启动nginx 只测试 nginx.conf 是否正确
```
nginx -t 
```

### 6测试配置期间不输出错误级别一下的信息
```
nginx -t -q
 -q            : suppress non-error messages during configuration testing
```

### 7显示版本信息
```
nginx -v
```
### 8显示configure 设置的选项
```
-V            : show version and configure options then exit

./bin/sbin/nginx -V

```

### 9 快速的停止服务
```
nginx -s stop 


-s signal     : send signal to a master process: stop, quit, reopen, reload



-s 告诉Nginx 向 执行 pid 执行的进程发送信号(signal)

Nginx 通过 nginx.pid 来 找到对应的master 进程


```

### 10 优雅的停止服务
```
nginx -s quit

1关闭监听端口，停止接受新连接
2.把当前正在处理的任务全部处理完全
3.退出进程


对进程发送 SIGQUIT 信号和 -s quit 
kill -s SIGQUIT <nginx master pid> 


优雅的停止某个 worker 进程

kill -s SIGWINCH <nginx worker pid>

```
### 11 使用运行中的Nginx重读配置项并生效
```
nginx -s reload

执行流程
1.检查新的配置项是否有误
2.以优雅的方式停止
3.重启Nginx


等效方式
kill -s SIGHUP <nginx master pid>


```
### 12 日志回滚
```

```


