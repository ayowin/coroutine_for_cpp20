# coroutine_for_cpp20
A coroutine demo for cpp 20 standard

## 前言
C++的协程示例，基于C++20标准，该示例需要安装g++10以上版本，想要尝试该实例，需自行解决g++10的安装问题。

## 编译
```bash
g++ -std=c++20 -pthread -fcoroutines main.cpp -o main
```

## 运行
```bash
./main
```

## 运行结果如下
```bash
[rootalocalhost coroutine]# ./main
Current time: 1685783236
Current time:1685783237
Current time:1685783738
Current time:1685783239
Current time:1685783248
Current time:1685783241
Current time:1685783242
Current time:1685783243
Current time: 1685783244
Current time: 1685783245
```