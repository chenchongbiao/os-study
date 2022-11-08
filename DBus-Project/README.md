# dbus仓库

[https://github.com/godbus/dbus/](https://github.com/godbus/dbus/)

# DBus相关例子记录

## polkit-qt

介绍：利用polkit调用root权限的操作，需要使用systemBus注册dbus服务。

参考：

## DBus-Docker

介绍：使用DBus对Docker的api进行封装注册到session-dbus中

# go-lib使用

使用linuxdeepin下的go-lib库，里面有dbustil，实现方法暴露在dbus中，无法通过github下载

仓库链接：[https://github.com/linuxdeepin/go-lib](https://github.com/linuxdeepin/go-lib)

## 方法一

尝试使用以下方法无效，项目未使用go mod进行管理

通过下载源码重命名，~/go/pkg/mod/github.com/linuxdeepin/go-lib/go-lib@v5.8.7。

在go.mod下的require加入github.com/linuxdeepin/go-libv0.0.0-incompatible// indirect

在require之外加入

replace github.com/linuxdeepin/go-lib => /home/bluesky/go/pkg/mod/github.com/linuxdeepin/go-lib/go-lib@v5.8.7

## 方法二

不使用go mod在，shell中使用export GO111MODULE=off，go mod进行关闭，然后将go-lib源码下载到，$GOPATH/src/github.com/linuxdeepin/go-lib下，依赖go-lib的项目也不要使用go mod进行管理。代码执行的时候可以引入go-lib了。

# go-dbus-factory

方便的GO绑定代码，用于自动生成DBUS服务。

仓库链接：[https://github.com/linuxdeepin/go-dbus-factory](https://github.com/linuxdeepin/go-dbus-factory)

在项目根目录执行命令，生成构成器。

先关闭go mod管理 ，构建过程缺失的库，根据提示补齐。

```bash
GO111MODULE=off
```

```bash
make bin
```

尝试编译结果报错

```bash
/usr/local/go/pkg/tool/linux_amd64/link: running gcc failed: exit status 1
```

# DBus-Docker

介绍：使用docker的go语言接口调用docker的api，并使用dbus将服务注册到sessionbus中，方便其他进程进行调用。

技术点：godbus、Docker-SDK-Go、sqlite、go-lib

参考：

[Docker SDK使用指南](https://blog.csdn.net/SHELLCODE_8BIT/article/details/126429362?spm=1001.2101.3001.6650.1&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EYuanLiJiHua%7EPosition-1-126429362-blog-125198200.pc_relevant_multi_platform_whitelistv3&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EYuanLiJiHua%7EPosition-1-126429362-blog-125198200.pc_relevant_multi_platform_whitelistv3&utm_relevant_index=1)

[使用Docker的API及SDK](https://blog.csdn.net/qq_44846324/article/details/125198200?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522166778178716782412533759%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fblog.%2522%257D&request_id=166778178716782412533759&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~blog~first_rank_ecpm_v1~rank_v31_ecpm-1-125198200-null-null.nonecase&utm_term=%E4%BD%BF%E7%94%A8docker%E7%9A%84api%E5%92%8Csdk&spm=1018.2226.3001.4450)

[Dockore 一个简单、便捷、开箱即用的Docker GUI客户端。](https://github.com/HsOjo/Dockore)
