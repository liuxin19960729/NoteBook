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
```cpp
没有任何动作的接口,是纯数据类
EntitySystem:
    ComponetCollection * GetComponentCollections();


    保存实体或组件

    ComponetCollection * 一系相似的组件放在一起   
        例如:
            所有UpdateComponetn放在一次




    class ComponetCollections
       note:
        ComponetCollections 是一个集合,为了避免死锁
           Add or Remove ... 都会缓存,在下一帧处理
       



class  EntitySystem

    update(){
        ComponetCollection->Swap();
    }
        // 不同于其他系统的update 对每一个ComponentCollections 调用
    Swap 函数
  
  

Swap() 左的事情
采取CacheRefresh的方式
class ComponetCollection 
    存在三种数据
    1.当前正在运行的数据
    2.新增加的数据
    3.删除的数据



    Swap(){
        将新增和删除数据合并到有效的的集合里面
    }

    



note:
   实体和组件式相互循环的机构，实体可以创建无限个实体做自己的组件
   
   EntitySystem->ComponetCollection->Swap() 在执性更新操作的时候
   在某种特殊情况下,创建一个是新实体,新实实例也有UpdateComponent,如果这时候加入有效列表 就会出现bug.

    因此,更新 or删除 放入到下一帧执行可以避免上面的问题


```
### 8.1.2 更新系统 UpdateSystem
```
两种类型组件组成:
    UpdateComponent 相当于是更新标记
    UpdateSystem
       找到所有UpdateComponet并且执行更新 
    
```
**关键点1:组件UpdateComponent**
```cpp
将NetworkListen 的 update 函数绑定到 UpdateComponent UpdateFunction 上
```
**关键点2:系统UpdateSystme**
```cpp
```
