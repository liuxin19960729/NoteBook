# 8.输入组件式编程
## 8.1 新个管理类SystmeManager
```
面向对象的设计方式
Systme:
        游戏逻辑动作部分
            每帧调用:
                std::list<IUpdateSystem> 
                IUpdateSystem  update()

            组件首次调用
                std:list<IStartSystme>
                IStartSystme start()


            ...... 随着游戏功能增加，动作会不断增加


           通过继承的方式 随着动作 越来越多 System 会 越来越冗余和不可维护

ECS:
    例如：
    SystemManager :管理所有系统
        EntitySystem:
            实体系统：管理所有实体与组件
            note:
                如果是多线程 EntitySystem 值负责本线程的组件
        MessageSystem:
            消息系统
            网络层 或其他线程发送来的Packet 消息
        UpdateSystem:
            更新系统:
            处理不断更新的组件

        

        note:
            1.除了EntitySystme 之外，所有的系统都继承Isytem基类
            2.EntitySystem 和  MessageSystem 两个系统在 SystemManager 被单独处理,其他System 都放在一个队列里面一起处理    
```
### 8.1.1 实体系统EntitySystem
```

``` 
