
const fs = require("fs");
const process =require("process")
console.log("1")
const start=Date.now();
/**
 * timer 阶段  
 * 执行到该阶段会 libuv 会检查 超时的回调
 */
setTimeout(() => {
    console.log('setTimeout2000',Date.now()-start)
}, 10)




fs.readFile("./3/doc.md","utf-8",()=>{
    console.log("readFile")
    // while(Date.now()-start<=4000){}
})


// setTimeout(() => {
//     console.log('setTimeout1000',Date.now()-start)
// }, 1000)


/**
 * poll 阶段
 * 1.后面的阶段队列没有会等待 
 * 2.wait timeout 进行下一个循环
 * 
 * 
 * 
 */


// check 阶段 poll 发现 check 阶段 有回调 会指向下面的回调 进入下一次循环
// check 阶段发现有回调立即执行

function _vvv(i){
    setImmediate(()=>{
        console.log("setImmediate2",i)
        // _vvv(i+1);
    })
}

_vvv(0);



/**
 * promise 和 process.nextTick()
 * 会在每次 循环的最开始阶段必须先把 微队列清空
 * process.nextTick
 * Promise.resolve().then
 */
process.nextTick(()=>{
    console.log("nextTick")
})

process.nextTick(()=>{
    console.log("nextTick2")
})

Promise.resolve().then(v=>{
    console.log("Promise.reject().then")
})