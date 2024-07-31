## luaL_loadbufferx
```c
是 Lua C API 中的一个函数，用于将内存中的 Lua 代码块加载到 Lua 虚拟机中，并且可以选择指定一个模式来控制代码块的加载方式。它是 luaL_loadbuffer 的扩展版本，增加了一个 mode 参数。



int luaL_loadbufferx (lua_State *L,
                      const char *buff,
                      size_t sz,
                      const char *name,
                      const char *mode);

name:代码块的名字

```