内容来自统信UOS应用开发进阶教程

# VS Code配置环境

## 安装插件

CMake：支持VS Code的扩展语言。

CMake Tools：支持VS Code的扩展。

C/C++：C++代码提示。

# dtkwidget

仓库链接：[https://github.com/linuxdeepin/dtkwidget](https://github.com/linuxdeepin/dtkwidget)

介绍：提供dtk基础控件，方便开发统一风格的应用

## DTK加入到QT设计师中

下载dtkwidget进行编译，如果是cmake工程使用以下操作，使用了tag 5.6.0.2

```bash
git clone https://github.com/linuxdeepin/dtkwidget.git
```

```bash
sudo apt install qttools5-dev
# build 在dtkwidget执行下面命令
cmake ./plugin/dtkuiplugin -B build -DINSTALL_PLUGIN=ON -DCMAKE_INSTALL_PREFIX=/usr
cmake --build build -j $(nproc)
```

编译过程可能出现Could NOT find Doxygen (missing:  DOXYGEN_EXECUTABLE)

```bash
sudo apt install doxygen  
```

在build文件夹中找到libdcustomwidgets.so文件，并复制到设计师的插件里，重启QtCreator可以在设计师看到dtk控件。

```bash
sudo cp libdcustomwidgets.so /usr/lib/x86_64-linux-gnu/qt5/plugins/designer/
```

如果代码是qmake工程，如release/5.5分支。

可以使用QtCreator进行项目构建，在编译结果中plugins/designer下有libdcustomwidgets.so文件，复制到指定位置。

## 自定义控件

使用QtCreator新建启动项目->Qt设计师自定义控件

设置控件类->说明中添加组

# CMake演示项目

项目名：cmake-demo

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

# Q_D指针和Q_Q指针

项目代码：Q_D_Demo

作用：

* 信息隐藏：把类头文件中的私有数据成员和方法隐藏起来，只暴露用户需要的接口
* 二进制兼容：如果程序从一个以前版本的库动态链接到新版本的库之后，能够继续正常运行，而不需要重新编译，那么我们就说这个库是二进制兼容的。

## Q_D指针

> 在class中配合使用 Q_DECLARE_PRIVATE 和 Q_D ，方便获取d指针，d指针指向Class##Private；

## Q_Q指针

> 在class##Private配合使用 Q_DECLARE_PUBLIC 和 Q_Q ，方便获取q指针，q指针指向原class本身；
> Q_DECLARE_PRIVATE 和 Q_DECLARE_PUBLIC 在作用是定义d_func和q_func这两个函数, 他们是用来在Class和Class##Private中获取彼此的指针。
> Q_D 和 Q_Q 宏是用过上面定义的d_func和q_func函数来获取d、q指针

## 实际运用

**使用Q_D指针指向私有成员和Q_Q指针指向公开成员**

开发DLL为什么要使用Q_D/Q_Q指针？
 假如，我们要把下面这个类封装成DLL：

```cpp
class MyClass
{
	public:
	  MyClass();
	  ~MyClass();
	private:
	  int myVar;
};
```

显然，这个私有成员myVar是我们不想给第三方看到的，而且是代码[二进制](https://so.csdn.net/so/search?q=%E4%BA%8C%E8%BF%9B%E5%88%B6&spm=1001.2101.3001.7020 "二进制")兼容性的大敌。所以我们使用Q_D指针和Q_D指针，对该私有成员myVar进行私有化。

### 使用d_ptr指针指向MyClass的私有成员

我们定义一个私有类MyClassPrivate,并配合Q_DECLARE_PRIVATE宏，以定义指针d_ptr指向该私有类。

```cpp
class MyClassPrivate;
class MyClass
{
	public:
	  MyClass();
	  ~MyClass();
	private:
	  MyClassPrivate * const d_ptr;
	  Q_DECLARE_PRIVATE(MyClass);
};
```

然后，我们把MyClass类中该隐藏的变量塞到私有类MyClassPrivate中，下面展示私有类MyClassPrivate的实现：

```cpp
class MyClassPrivate
{
	public:
	  MyClassPrivate(MyClass *parent);
	private:
	  MyClass * const q_ptr;
	  Q_DECLARE_PUBLIC(MyClass);
	  int myVar;
};
```

### 使用q_ptr指针指向MyClass的公有成员

从私有类MyClassPrivate的实现代码可以看到，我们在私有类中，配合Q_DECLARE_PUBLIC宏来定义q_ptr指针指向MyClass的公有成员。

以上就是Qt使用Q_D和Q_Q指针私有实现的基本方法，下面给出一个比较完整的例子：
 [ myclass.h]

```cpp
#ifndef MYCLASS_H
#define MYCLASS_H

#include <QtCore/QObject>

class MyClassPrivate;
class MyClass: public QObject
{
      Q_OBJECT
public:
      MyClass(QObject *parent = nullptr);
      virtual ~MyClass();
      void dummyFunc();

signals:
      void dummySignal();

private:
      MyClassPrivate * const d_ptr = nullptr;
      Q_DECLARE_PRIVATE(MyClass)
      Q_DISABLE_COPY(MyClass)              //防止指针d_ptr的二次释放
};
#endif // MYCLASS_H
```

[myclass.cpp]

```cpp
#include "myclass.h"

class MyClassPrivate : public QObject
{
public:
    MyClassPrivate(MyClass *parent)
    : q_ptr(parent)
    {
    }
    void foobar()
    {
        Q_Q(MyClass);
        emit q->dummySignal();
    }
private:
    MyClass * const q_ptr = nullptr;
    Q_DECLARE_PUBLIC(MyClass)

};

MyClass::MyClass(QObject *parent)
  : QObject(parent)
  , d_ptr(new MyClassPrivate(this))
{

}

MyClass::~MyClass()
{
    Q_D(MyClass);
    delete d;
}

void MyClass::dummyFunc()
{
    Q_D(MyClass);
    d->foobar();
}

```

# QTest单元测试框架

Qt Test 是一个用于对基于 Qt 的应用程序和库进行单元测试的框架。Qt Test 提供了单元测试框架中常见的所有功能以及用于测试图形用户界面的扩展

## Qt Test特性

Qt Test 旨在简化基于 Qt 的应用程序和库的单元测试的编写：

| 特征          | 细节                                                                |
| ------------- | ------------------------------------------------------------------- |
| 轻量级        | Qt Test 由大约 6000 行代码和 60 个导出符号组成。                    |
| 自包含        | Qt Test 只需要 Qt Core 模块中的几个符号来进行非 gui 测试。          |
| 快速测试      | Qt Test 不需要特殊的测试运行器；没有特殊的测试注册。                |
| 数据驱动测试  | 可以使用不同的测试数据多次执行测试。                                |
| 基本 GUI 测试 | Qt Test 提供了鼠标和键盘模拟的功能。                                |
| 基准测试      | Qt Test 支持基准测试并提供多个测量后端                              |
| IDE 友好      | Qt Test 输出可由 Qt Creator、Visual Studio 和 KDevelop 解释的消息。 |
| 线程安全      | 错误报告是线程安全和原子的。                                        |
| 类型安全      | 模板的广泛使用可以防止隐式类型转换引入的错误。                      |
| 易于扩展      | 自定义类型可以很容易地添加到测试数据和测试输出中。                  |

## AutoTest 插件 

qtCreator 中 帮助->关于插件->实用工具>AutoTest勾选上，默认自动勾选

## 使用QMake构建单元测试

如果您将qmake其用作构建工具，只需将以下内容添加到您的项目文件中：

```cpp
QT += testlib
```

## QTest 命令行参数

语法

执行自动测试的语法采用以下简单形式：

```bash
testname [options] [ testfunctions [：testdata ] ] .. . 
```

替换testname为您的可执行文件的名称。testfunctions可以包含要执行的测试函数的名称。如果没有testfunctions通过，则运行所有测试。如果您在 中附加条目的名称testdata，则测试函数将仅使用该测试数据运行。

```
/ myTestDirectory$ testQString toUpper
```

toUpper运行使用所有可用测试数据调用的测试函数。

```bash
/myTestDirectory$ testQString toUpper toInt:zero
```

toUpper使用所有可用的测试数据运行测试函数，并toInt调用带有测试数据的测试函数zero（如果指定的测试数据不存在，则关联的测试将失败）。

```bash
/myTestDirectory$ testMyWidget - vs - eventdelay 500
```

## 创建测试

要创建测试，请将QObject子类化并为其添加一个或多个私有槽。每个私有插槽都是您测试中的一个测试函数。`QTest::qExec ()` 可用于执行测试对象中的所有测试函数。


# UOS程序启动器

项目名：starter-demo

# 文件操作

计算机中所有的数据都以文件形式存在。在计算机中，对文件的操作包括目录操作、新建文件、文件命名、文件重命名、文件删除、文件属性设置等。本章主要介绍Qt中目录和文件的操作。

# 多线程和多线程同步

在一个程序中，独立运行的程序片段称为线程（Thread），多线程（Multithreading）是指从软件或者硬件上实现多个线程并发执行的技术。需要有硬件支持，计算机才能够具有多线程能力，同时执行多个线程，从而提升整体的处理性能。具有这种能力的系统包括对称多处理机、多核处理器、芯片级多处理器以及同时多线程处理器。对线程进行编程处理的过程称为多线程处理。

## 多线程的状态和线程调度

线程是操作系统能够进行运算调度的最小单位。大部分情况下，线程包含在进程中，是进程中的实际运作单位。一个线程指的是进程中一个单一顺序的控制流，一个进程中可以并发执行多个线程，每个线程执行不同的任务。同一进程中的多个线程共享该进程中的全部系统资源，如虚拟地址空间、文件描述符、信号处理等。但同一进程中的多个线程有各自的调用栈（Call Stack）、寄存器环境（Register Context），以及独立的线程本地存储（Thread-local Storage）。

线程调度有下面两种方式。

分时调度（系统级别）：所有线程轮流拥有CPU的使用权，平均分配每个线程占用CPU的时间。

抢占式调度（语言级别）：优先级高的线程先使用CPU，如果可运行线程池中的线程优先级相同，就随机选择一个线程，使其占用CPU。处于运行状态的线程会一直运行，直至其放弃CPU。

## 多线程的创建和管理

Qt通过3种形式提供对线程的支持，分别是平台无关的线程类、线程安全的事件投递、跨线程的信号槽连接。Qt中主要的线程类如下。

QThread：提供跨平台的多线程解决方案。

QThreadStorage：提供逐线程数据存储。

QMutex：提供相互排斥的锁或互斥量、

QMutexLocker：辅助类，可自动对QMutex加锁与解锁。

QReadWriteLock：提供可以同时读写操作的锁。

QReadLocker与QWriteLocker：自动对QReadWriteLock加锁与解锁。

QSemaphore：提供整型信号量，是互斥量的泛化。

QWaitCondition：线程在被其他线程唤醒之前一直休眠。

QThread是Qt线程中的一个公共的抽象类，所有的线程类都是从QThread抽象类中派生的。需要实现QThread中的虚函数run，可通过start函数来调用run函数。在默认情况下，QThread::run会启动一个事件循环（QEventLoop::exec）。线程相关的函数如下。

void run：线程体函数，用于定义线程的功能。

void start：启动函数，用于将线程入口地址设置为run函数。

void terminate：用于强制结束线程，不保证数据完整性和资源释放。

## 线程同步

线程同步即当有一个线程在对内存地址进行操作时，其他线程都不可以对这个内存地址进行操作，直到该线程完成操作，其他处于等待的线程才能对该内存地址进行操作，而别的线程又处于等待状态。

## Qt多线程

在进行桌面应用程序开发的时候， 假设应用程序在某些情况下需要处理比较复杂的逻辑， 如果只有一个线程去处理，就会导致窗口卡顿，无法处理用户的相关操作。这种情况下就需要使用多线程，其中一个线程处理窗口事件，其他线程进行逻辑运算，多个线程各司其职，不仅可以提高用户体验还可以提升程序的执行效率。

- 默认的线程在Qt中称之为窗口线程，也叫主线程，负责窗口事件处理或者窗口控件数据的更新
- 子线程负责后台的业务逻辑处理，子线程中不能对窗口对象做任何操作，这些事情需要交给窗口线程处理
- 主线程和子线程之间如果要进行数据的传递，需要使用Qt中的信号槽机制

## 多线程项目1

项目名：Qthread-demo

介绍：使用多线程的方式完成随机数的生成，并将随机数进行冒泡排序和快速排序两种方式进行排序，将结果显示到窗口中。

使用方式：添加子线程的方式是非常简单，但是也有弊端，假设要在一个子线程中处理多个任务，所有的处理逻辑都需要写到run()函数中，这样该函数中的处理逻辑就会变得非常混乱，不太容易维护。

[原链接](https://subingwen.cn/qt/thread/)

## 多线程项目2

项目名：Qthread-demo2

介绍：使用多线程的方式完成随机数的生成，并将随机数进行冒泡排序和快速排序两种方式进行排序，将结果显示到窗口中。

使用方式：假设有多个不相关的业务流程需要被处理，那么就可以创建多个类似于 Work 的类，将业务流程放多类的公共成员函数中，然后将这个业务类的实例对象移动到对应的子线程中 moveToThread() 就可以了，这样可以让编写的程序更加灵活，可读性更强，更易于维护。

## 线程池

项目名：Qthreadpool

介绍：使用多线程的方式完成随机数的生成，并将随机数进行冒泡排序和快速排序两种方式进行排序，将结果显示到窗口中。

使用方式：线程池是一种多线程处理形式，处理过程中将任务添加到队列，然后在创建线程后自动启动这些任务。

[原链接](https://subingwen.cn/qt/threadpool/)

## QtConcurrent并发模块

项目名：WaterProgress-demo

介绍：完成负载、CPU使用率、内存使用率、磁盘使用率的信息获取，使用DWaterProgress控件进行显示，使用QTimer定时检测硬件数据变化，使用QProcess调用外部程序执行指令，QtConcurrent并发模块将计算部分放入子线程中。

参考：[Qt编写获取CPU占用率、内存信息、硬盘容量、已运行时间等功能](http://www.qtcn.org/bbs/read-htm-tid-60613.html)

宝塔面板就算负载状态算法

# 套接字和网络编程

套接字（Socket）是不同主机上的应用进程之间通过网络进行双向通信的端点，一个套接字就是通信的一端。套接字提供了应用层进程利用网络协议交换数据的机制。网络编程是指编写运行在多个设备（计算机）上的程序，这些设备都通过网络连接起来。网络编程主要的工作就是在发送端把信息通过规定的协议组装成包，在接收端按照规定的协议对包进行解析，从而提取出对应的信息，达到通信的目的。其中主要的工作就是数据包的组装、过滤、捕获和分析。

# D-Bus进程间通信

D-Bus是针对桌面环境优化的进程间通信（InterProcess Communication，IPC）机制，用于进程间的通信或进程与内核的通信。最基本的D-Bus协议是一对一的通信协议，但在很多情况下，通信的一方是消息总线。消息总线是一个特殊的应用，可同时与多个应用通信，并在应用之间传递消息。D-Bus最主要的用途是在Linux桌面环境中为进程提供通信服务，同时能将Linux桌面环境和Linux内核事件作为消息传递到进程。注册后的进程可通过总线接收或传递消息，进程也可注册后等待内核事件响应，例如等待网络状态的转变或者计算机发出关机指令。目前，D-Bus已被大多数Linux发行版采用，开发者可使用D-Bus完成各种复杂的进程间通信任务。

D-Bus分为以下两种类型。

系统总线（System Bus）：用于系统（例如Linux等）和用户程序之间的通信和消息传递。

会话总线（Session Bus）：用于桌面（例如GNOME、KDE等）用户程序之间的通信。一般用到的是会话总线。在建立基于D-Bus的连接时需要选择建立系统总线连接还是会话总线连接。D-Bus是一个消息总线系统，其功能已涵盖进程间通信的所有需求，并具备一些特殊的用途。D-Bus是三层架构的进程间通信系统，三层架构介绍如下。

接口层：由函数库libdbus提供，进程可通过该函数库使用D-Bus。

总线层：实际上由D-Bus守护进程提供。它在Linux系统启动时运行，负责进程间的消息路由和传递，其中包括Linux桌面环境和Linux内核的消息传递。

封装层：一系列基于特定应用程序框架的Wrapper库，将D-Bus底层接口封装成方便用户使用的通用API。

## Dbus例子

[原文链接](https://blog.csdn.net/qq_39392008/article/details/120703987#t8)

项目名：QtDBus-demo

## D-Bus XML自动生成Proxy类

Proxy Object提供了一种更加直观的方式来访问Service，如同调用本地对象的方法一样。
生成Proxy类的流程如下：
A、使用工具qdbuscpp2xml从object.h生成XML文件；
qdbuscpp2xml -M server.h -o com.bluesky.test.xml

```xml
<!DOCTYPE node PUBLIC "-//freedesktop//DTD D-BUS Object Introspection 1.0//EN" "http://www.freedesktop.org/standards/dbus/1.0/introspect.dtd">
<node>
  <interface name="com.bluesky
.test.value">
    <method name="maxValue">
      <arg type="i" direction="out"/>
    </method>
    <method name="minValue">
      <arg type="i" direction="out"/>
    </method>
    <method name="value">
      <arg type="i" direction="out"/>
    </method>
  </interface>
</node>
```

使用工具qdbusxml2cpp从XML文件生成继承自QDBusInterface的类
qdbusxml2cpp com.bluesky.test.xml -p valueInterface
生成两个文件：valueInterface.cpp和valueInterface.h

## Adapter注册Object

可以直接把test类注册为消息总线上的一个Object，
大多数情况下，可能只需要把自定义的类里的方法有选择的发布到消息总线上，使用Adapter可以很方便的实现选择性发布。
生成Adapter类的流程如下：
A、使用工具 qdbuscpp2xml从test.h生成XML文件
qdbuscpp2xml -M server.h -o com.bluesky.test.xml
B、编辑com.bluesky.test.xml，选择需要发布的method，不需要发布的删除。
C、使用工具qdbusxml2cpp从XML文件生成继承自QDBusInterface的类
qdbusxml2cpp com.bluesky.test.xml -i server.h -a valueAdaptor
生成两个文件：valueAdaptor.cpp和valueAdaptor.h

## 自动启动Service

D-Bus系统提供了一种机制可以在访问某个service时，自动把应用程序运行起来。
 需要在/usr/share/dbus-1/services下面建立com.bluesky.test.service文件，文件的内容如下：

```txt
[D-BUS Service]
Name=com.bluesky.test
Exec=/usr/bin/dbusserver
```

Name是服务器的公共名，Exec是服务器的执行路径。

## Go DBus

[https://pkg.go.dev/github.com/godbus/dbus/v5](https://pkg.go.dev/github.com/godbus/dbus/v5)

[dbus in go](https://www.codeplayer.org/Wiki/go/%E5%9C%A8go%E4%B8%AD%E4%BD%BF%E7%94%A8dbus%E5%92%8Cgsettings.html#orgd279943)

## 统信UOS磁盘管理器

项目链接：[https://github.com/linuxdeepin/deepin-diskmanager.git](https://github.com/linuxdeepin/deepin-diskmanager.git)

磁盘分区工具，使用了DBus
