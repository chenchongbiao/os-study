# 介绍

做一个根文件系统的相关介绍。

# 工具

## Debootstrap

Debootstrap 是一个可以快速获得基本 Debian 系统的一个工具，你可以将 Debootstrap 看作是一种特殊的安装工具。不同于 Debian Installter，不需要安装用的 CD/DVD ISO，仅需连接到 Debian 软件仓库。可以在任何 Linux/GNU 发行版上运行 Debootstrap，也可以用它来安装不同架构的 Debian 系统。Debootstrap 的工作是将基本的 Debian 系统安装到一个目录上，然后可以通过 chroot 切换到新安装的 Debian 系统。debootstrap 也可以用来构建 Docker 镜像。

## Multistrap

Multistrap是一个工具，它基本上和Debootstrap做相同的工作，但使用了一个完全不同的方法，然后扩展了功能，支持自动创建完整的、可引导的、根文件系统。它可以合并来自不同仓库的软件包来制作根文件系统。您可以在配置文件中指定要安装的软件包和它们的依赖关系，然后解压缩（但不配置）这些软件包。这样就会留下一个根文件系统，只需要挂载（或chroot）并用dpkg --configure -a进行配置。Multistrap主要用于制作外部架构嵌入式系统的根文件系统，但实际上也可以用于许多可能使用Debootstrap的任务。

## mmdebstrap

mmdebstrap是一个用于创建Debian或Ubuntu的根文件系统的工具，它可以在不同的架构之间进行交叉构建，并支持多种格式和选项。

使用以下命令格式来构建文件系统：

```bash
sudo mmdebstrap --arch=[平台] [发行版本代号] [输出文件] [镜像地址]
```

```bash
sudo mmdebstrap --arch=amd64 bookworm linux-rootfs.tar https://mirrors.tuna.tsinghua.edu.cn/debian/
```
