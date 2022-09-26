记录UOS应用开发

# VS Code配置环境

## 安装插件

CMake：支持VS Code的扩展语言。

CMake Tools：支持VS Code的扩展。

C/C++：C++代码提示。

# CMake演示项目

项目名cmake-demo

通过快捷键“Ctrl+Shift+P”，打开命令面板并输入“cmake:Quick Start”

1.首先选择Kit，也就是选择所用的编译工具。选择GCC

2.然后在其中输入项目名称“demo”

3.选择生成库（Library）或生成执行文件（Executable）

4.自动生成CMakeLists.txt、main.cpp文件及build文件夹

5.生成的CMakeLists.txt文件内容如下。

```bash
cmake_minimum_required(VERSION 3.0.0) # CMake最低版本号
project(demo VERSION 0.1.0) # 确定项目名和项目版本号

include(CTest) # 引入CTest模块
enable_testing()

add_executable(demo main.cpp) # 通过main.cpp生成可执行文件

set(CPACK_PROJECT_NAME ${PROJECT_NAME}) # 设置CPack变量
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION}) # 设置包的供应商
include(CPack) # 引入CPack模块
```

6.配置调试文件，在运行菜单中，选择单击“以非调试模式运行”（运行但不调试），然后选择C++，

7.选择“C++(GDB/LLDB)”进行调试

8.选择“g++- 生成和调试活动文件”

9.编辑生成的tasks.json，更改program参数，即更改程序启动路径

```json
{
    // 使用Intellisense了解可能的属性 
    // 悬停以查看现有属性的描述
    // 欲了解更多信息，请访问: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
         {
             "name": "g++-生成和调试活动文件",
             "type": "cppdbg",
             "request": "launch",
             "program": "${command:cmake.launchTargetPath}",
             "args": [],
             "stopAtEntry": false,
             "cwd": "${fileDirname}",
             "environment": [],
             "externalConsole": false,
             "MIMode": "gdb",
             "setupCommands": [
                  {
                      "description": "为gdb启用整齐打印",
                      "text": "-enable-pretty-printing",
                      "ignoreFailures": true
                  }
             ],
             "preLaunchTask": "C/C++: g++ 生成活动文件",
             "miDebuggerPath": "/usr/bin/gdb"
        }
    ]
}
```

保存后启动调试，进行测试。成功输出“Hello，world!”表明测试成功。

# 元对象系统

Qt的元对象系统是一个基于标准C++的扩展，为Qt提供了3个重要的特性。

信号和槽机制：实现各个组件之间的通信。

实时类型信息：通过运行时使用的类型，执行不同的函数，复用接口。

动态属性系统：存储类的相关信息，用于在运行时识别类对象的信息。实时类型信息和动态属性系统使Qt具有了动态语言的特点。信号和槽机制是Qt中处理事件响应的方法，

# 信号和槽机制

信号和槽是Qt编程的基础，也是Qt的一大创新。有了信号和槽的编程机制，在Qt中处理界面各个组件的交互操作变得更加直观和简单。所谓信号和槽，实际就是观察者模式。当某个事件发生之后，比如按钮被单击，就会发出一个信号。GUI程序设计的主要内容就是对界面上各组件发出的信号进行响应，需要知道什么情况下会发出哪些信号，合理地去响应和处理这些信号。

# UOS程序启动器

项目名starter-demo

# 文件操作

计算机中所有的数据都以文件形式存在。在计算机中，对文件的操作包括目录操作、新建文件、文件命名、文件重命名、文件删除、文件属性设置等。本章主要介绍Qt中目录和文件的操作。

# 多线程和多线程同步

在一个程序中，独立运行的程序片段称为线程（Thread），多线程（Multithreading）是指从软件或者硬件上实现多个线程并发执行的技术。需要有硬件支持，计算机才能够具有多线程能力，同时执行多个线程，从而提升整体的处理性能。具有这种能力的系统包括对称多处理机、多核处理器、芯片级多处理器以及同时多线程处理器。对线程进行编程处理的过程称为多线程处理。
