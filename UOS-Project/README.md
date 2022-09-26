记录UOS应用开发

# VS Code配置环境

## 安装插件

CMake：支持VS Code的扩展语言。

CMake Tools：支持VS Code的扩展。

C/C++：C++代码提示。

# CMake演示项目

文件夹cmake-demo

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
