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

# DBus-Docker

介绍：使用docker的go语言接口调用docker的api，并使用dbus将服务注册到sessionbus中，方便其他进程进行调用。
