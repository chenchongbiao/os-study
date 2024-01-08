# 介绍

Docker 是一个开源的应用容器引擎，基于 [Go 语言](https://www.runoob.com/go/go-tutorial.html)   并遵从 Apache2.0 协议开源。

Docker 可以让开发者打包他们的应用以及依赖包到一个轻量级、可移植的容器中，然后发布到任何流行的 Linux 机器上，也可以实现虚拟化。

容器是完全使用沙箱机制，相互之间不会有任何接口（类似 iPhone 的 app）,更重要的是容器性能开销极低。

Docker 从 17.03 版本之后分为 CE（Community Edition: 社区版） 和 EE（Enterprise Edition: 企业版），我们用社区版就可以了。

# 安装

如果需要使用distrobox工具的话请安装。

```bash
sudo apt-get update
sudo apt install docker.io
```

如果想获取较好的功能支持，请使用下面的。

```bash
sudo apt-get update
sudo apt-get install docker-ce docker-ce-cli containerd.io
```

- Docker CE (Community Edition) 是 Docker 的社区版本，包含了 Docker Engine，它是 Docker 的核心组件，在深度操作系统上安装 Docker CE 之后就可以运行容器了。但是 docker-ce-cli 和 [containerd.io](http://containerd.io) 这两个软件包也是必需品，原因如下：
- Docker CLI (docker-ce-cli)：Docker CLI 是 Docker 命令行工具，用于管理 Docker 容器和图像。这个工具提供了一组命令，用于构建，运行和管理 Docker 容器。
- Containerd ([containerd.io](http://containerd.io))：Containerd 是一个轻量级的守护进程，用于管理容器生命周期，包括创建，运行和销毁容器。Docker Engine 基于 containerd 构建，并使用其进行容器管理。

源里暂时没有docker相关的包，这里先使用debian的包安装。使用debian安装docker的脚本。

```bash
curl -fsSL https://get.docker.com -o get-docker.sh
sudo sh get-docker.sh
```

## 换源

```bash
sudo mkdir -p /etc/docker
sudo tee /etc/docker/daemon.json <<-'EOF'
{
  "registry-mirrors": ["https://registry.docker-cn.com"]
}
EOF
sudo systemctl daemon-reload
sudo systemctl restart docker
```

## 添加到docker用户组

```bash
sudo usermod -aG docker $USER
newgrp docker
```

## 修改容器存放的位置

```bash
sudo vim /etc/docker/daemon.json
```

```bash
{
  "graph": "/new-path/docker"
}

```

这里的/new-path/docker是指存在的某个路径，如果有其他磁盘想将docker相关的数据存放到别的磁盘可以进行设置，否则使用不需要设置。如果之前已经有很多容器和镜像，需要把 **/var/lib/docker** 目录下的所有文件复制到新的目录下。注意将原/var/lib/docker目录删除或者转移，否则会出现重复挂载的情况。例如：

```bash
sudo cp -R /var/lib/docker /new-path/
```

```bash
sudo systemctl restart docker
```

重启docker服务才能生效。

## 允许远程

为了方便测试使用，不要在生产环境使用。

Docker守护进程提供了一个远程API，默认监听在Unix域套接字 `/var/run/docker.sock`上，这个套接字允许本地进程与Docker守护进程进行通信来控制容器等操作。

使用下面的命令查看 docker 的 service 服务使用的哪个文件。

```bash
systemctl status docker
```

修改 service 文件

```bash
sudo sed -i 's|^ExecStart=/usr/bin/dockerd|ExecStart=/usr/bin/dockerd -H tcp://0.0.0.0:2375|' /lib/systemd/system/docker.service
```

重启服务

```bash
sudo systemctl daemon-reload
sudo systemctl restart docker
```

测试

```bash
docker -H tcp://$HOST:2375 ps
```

`$HOST` 是远程主机 ip

# Docker Compose

Compose 是用于定义和运行多容器 Docker 应用程序的工具。通过 Compose，您可以使用 YML 文件来配置应用程序需要的所有服务。然后，使用一个命令，就可以从 YML 文件配置中创建并启动所有服务。

## 安装

```bash
sudo curl -L "https://github.com/docker/compose/releases/download/v2.18.1/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose
```

需要指定指定版本的花，修改v2.18.1

将可执行权限应用于二进制文件：

```bash
sudo chmod +x /usr/local/bin/docker-compose
```

创建软链：

```bash
sudo ln -s /usr/local/bin/docker-compose /usr/bin/docker-compose
```

测试是否安装成功：

```bash
docker-compose version
```

# Distrobox

Distrobox 是一个命令行工具，它使用 Docker 或 Podman 提供访问多个 Linux 操作系统的方法。

## 安装

使用安装脚本

```bash
sudo apt install distrobox
```

不过distrobox依赖于runc docker.io,这属于旧版本docker,如果要更好的稳定性，性能和安全性版本建议使用新版的docker-ce，不过这样就无法使用distrobox。

## 使用

### 创建容器

```bash
distrobox create --image debian:latest --name debian
```

### 查看容器列表

```bash
distrobox list
```

### 进入容器

```bash
distrobox enter debian
```

进入容器后使用exit命令退出。

### 删除容器

```bash
distrobox rm debian
```

### 停止容器

```bash
distrobox stop debian
```

## 使用APPIMAGE

安装FUSE库支持

```bash
sudo apt install libfuse2 fuse3
```

在/etc/ld.so.conf.d/目录下新建文件fuse.conf

```
sudo vim /etc/ld.so.conf.d/fuse.conf
```

输入fuse的安装路径 /usr/local/lib

```bash
/usr/local/lib
```

保存退出，执行ldconfig 重新挂载

```bash
ldconfig
```

## 单独配置Git

为了与外部区别，重新配置一份gitconfig

```bash
sudo cp ~/.gitconfig /etc/gitconfig
```

profile.d下面编辑一个git_config.sh

```bash
sudo vim /etc/profile.d/git_config.sh
```

```bash
alias git='git -c include.path="/etc/gitconfig"'
```

# tigervnc 远程

## 安装桌面环境。

```bash
sudo apt install deepin-desktop-environment-base
sudo apt install deepin-desktop-environment-cli
sudo apt install deepin-desktop-environment-core
sudo apt install deepin-desktop-environment-extras
sudo apt install deepin-desktop-environment-ll
```

## 安装VNC服务

```bash
sudo apt install tigervnc-standalone-server tigervnc-xorg-extension autocutsel
```

- tigervnc-standalone-server：TigerVNC的服务器端组件
- tigervnc-xorg-extension：TigerVNC的Xorg扩展模块,实现直接共享本地显示器的功能。
- autocutsel：一个剪贴板同步工具，它可以让您在本地和远程桌面之间复制和粘贴文本。

## 客户端

```bash
sudo apt install tigervnc-viewer
```

- tigervnc-viewer：这个包是TigerVNC的客户端组件，它可以让您连接到任何支持VNC协议的服务器，并查看和控制远程桌面。

## 安装XRDP服务

```bash
sudo apt install xrdp xorgxrdp
```

# x11docker

x11docker是一款允许在Docker容器中运行图形应用程序的软件。它通过在主机系统上运行X显示服务器，给Docker提供了GUI的支持。此外，x11docker对Docker和X window提供安全增强，实现以容器隔离并预防X window安全漏洞，通沙盒环境运行图形程序，以保护主机系统的安全。

## 安装

```bash
git clone git@github.com:mviereck/x11docker.git
cd x11docker && sudo bash x11docker --update
```

拉取 x11docker/xserver 镜像，这个是用来运行 X 服务器的镜像。

```bash
docker pull x11docker/xserver
```

拉取 x11docker/deepin 镜像，一个 deepin v20 的仓库。

```bash
x11docker --desktop --gpu --systemd --pulseaudio x11docker/deepin
```

运行起来后可以运行一个比较流程界面。

# deepin v23的Docker镜像

可以在wsl中的记录中查看，怎么获取一个根文件系统的tar包。

或者使用debootstrap制作一个根文件系统。

```bash
cat rootfs.tar | sudo docker import - deepin:v23
```

将rootfs.tar导入到docker中，镜像名为deepin:v23。

```bash
sudo docker run --name v23 -itd deepin:v23 bash
```

运行容器。

# 参考

[Debian Docker 安装](https://www.runoob.com/docker/debian-docker-install.html)

[x11docker Github 仓库](https://github.com/mviereck/x11docker)

[x11docker：让你的Docker跑图形程序](https://zhuanlan.zhihu.com/p/60073751)
