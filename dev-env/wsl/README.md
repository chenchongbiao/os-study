# WSL安装deepin

## 环境要求

- 系统版本
  - 对于 x64 系统：版本 1903 或更高版本，内部版本 18362 或更高版本。
  - 对于 ARM64 系统：版本 2004 或更高版本，内部版本 19041 或更高版本。
- 使用WSL 需要开启虚拟化。这里使用virtualbox安装windows11虚拟机。
  - 在控制面板，程序开启和关闭，打开“适用于Linux的Windows子系统”和“虚拟机平台”两个可选功能。
  - 在virtualbox安装windows虚拟机，需要在设置中为windows虚拟机启用嵌套虚拟化，即勾选“启用VT-x/AMD-V”和“启用嵌套分页”选项。
- 安装wsl（使用wsl2)
  - `wsl --update`
  - `wsl --set-default-version 2`

## filesystem提取安装系统

以deepinv23-beta为例

### 下载镜像

先下载v23-beta的镜像。使用解压工具将iso文件解压成文件夹。

### 提取filesystem

找到filesystem.squashfs文件

下载squashfs-tools工具[https://github.com/plougher/squashfs-tools](https://github.com/plougher/squashfs-tools)

需要使用squashfs-tools的4.3版本，可以从[squashfs-tools（1:4.3-12+deb10u2） ](https://packages.debian.org/buster/squashfs-tools)找到对应架构的进行下载，源代码仓库的提示不支持gzip解压，待后续研究。

```bash
# 下载源码进入目录
cd squashfs-tools
sudo make && sudo make install
```

或者通apt对squashfs-tools进行安装

使用unsquashfs命令将filesystem.squashfs文件解压到一个目录

```bash
sudo unsquashfs -d rootfs filesystem.squashfs
```

需要通过sudo来执行否则根系统的文件权限会错误。

### 打包tar文件

使用tar命令将解压后的目录打包成一个tar文件

```bash
cd rootfs
sudo tar -cf rootfs.tar *
```

ps: 如果使用tar -cf rootfs.tar rootfs/*的方式，会把rootfs目录给打包进去。

### 将tar导入

使用[deepin-wsl](https://github.com/linuxdeepin/deepin-wsl)工具来导入rootfs.tar文件，将下载下来的deepin-wsl和rootfs.tar放到一个文件夹下。

```bash
deepin install rootfs.tar
```

运行

```bash
deepin.exe
```

详细使用方法参考[yuk7/wsldl](https://github.com/yuk7/wsldl#wsldl)

## 添加软件源

```bash
sudo vim /etc/apt/sources.list
```

```bash
deb https://community-packages.deepin.com/beige/ beige main community
#deb-src https://community-packages.deepin.com/beige/ beige main community
```

## 添加一个sudo用户

```bash
# 添加一个bluesky用户
useradd -m bluesky
passwd bluesky
usermod -aG lp bluesky
usermod -aG sudo bluesky
usermod -aG netdev bluesky
usermod -aG lpadmin bluesky
usermod -aG scanner bluesky
usermod -aG sambashare bluesky

# 设置默认shell
su bluesky
chsh -s /usr/bin/bash
```

直接使用root无法登录图形界面

## 开启systemd支持

```bash
vim /etc/wsl.conf
```

```bash
[boot]
systemd=true
```

## 开启自动挂载Windows分区

```bash
vim /etc/wsl.conf
```

```bash
[automount]
enabled=true
options="metadata,umask=22,fmask=11"
```

- enabled = true表示启用自动挂载功能，如果设置为false，就需要手动挂载。

* options = "metadata,umask=22,fmask=11"表示挂载时的选项，其中metadata表示启用元数据支持，umask和fmask表示文件和目录的默认权限。
* mountFsTab根据/etc/fatab的内容自动挂载

## 自动挂载.X11-unix

```bash
vim /etc/wsl.conf
```

```bash
[boot]
command="sleep 5; sudo umount /tmp/.X11-unix; sudo mount -t none -o bind /mnt/wslg/.X11-unix /tmp/.X11-unix"
```

## 启动tmp.mount服务

启用tmp.mount服务

```bash
cp -v /usr/share/systemd/tmp.mount /etc/systemd/system/
systemctl enable tmp.mount
```

添加配置项,将wsl关闭后，重新进入。

## 设置wsl的默认用户

```bash
vim /etc/wsl.conf
```

```bash
[user]
default=bluesky
```

win系统下，使用deepin.exe修改。

```bash
# 在windows terminal
deepin.exe config --default-user bluesky
```

## 配置中文环境

```bash
sudo dpkg-reconfigure locales
```

找到zh_CN.UTF-8回车。

## 安装界面

### xrdp

安装xrdp

```bash
sudo apt install xrdp xorg xorgxrdp
```

#### 配置

```bash
sudo cp /etc/xrdp/xrdp.ini /etc/xrdp/xrdp.ini.bak
sudo sed -i 's/3389/3390/g' /etc/xrdp/xrdp.ini
sudo sed -i '/max_bpp=32/ amax_bpp=128' /etc/xrdp/xrdp.ini
sudo sed -i 's/max_bpp=32/#max_bpp=32/' /etc/xrdp/xrdp.ini
sudo sed -i '/xserverbpp=24/ axserverbpp=128' /etc/xrdp/xrdp.ini
sudo sed -i 's/xserverbpp=24/#xserverbpp=24/' /etc/xrdp/xrdp.ini
echo dde-session > ~/.xsession
```

配置DISPLAY环境变量

```bash
vim ~/.bashrc
```

```bash
export DISPLAY=:10.0
```

#### 自动填充账号和密码

```bash
sudo vim /etc/xrdp/xrdp.ini 
```

```bash
[Xorg]
name=Xorg
lib=libxup.so
username=ask
password=ask
ip=127.0.0.1
port=-1
code=20
```

找到这一段，将username和password设置成自己的。

退出wsl,重启wsl再进入。

打开win的桌面远程连接输入localhost:3390

# 暂时不看

## 添加lightdm

修改/etc/lightdm/lightdm.conf及/etc/lightdm/lightdm.conf.real
通过下面指令获取WSL 2网关。

```bash
ip route | grep default | awk '{print $3; exit;}'
# 或者
cat /etc/resolv.conf
```

为lightdm.conf追加如下内容,找到 **[Seat:*]** 之后相同的字段，去掉开头的 **#** ，修改成相同的内容。

```bash
type=xremote
xserver-hostname=x.x.x.x //替换此处
xserver-display-number=0
autologin-user=bluesky
```

## 配置X显示服务

打开X410，改成Floating Desktop模式，勾选Allow full public access。重启

$(cat /etc/resolv.conf | grep nameserver | awk ‘{print $2}’):0

## DNS无法解析的问题（非必要）

### 添加wsl.conf文件

```bash
vim /etc/wsl.conf
```

```bash
[network]
generateResolvConf = false
```

### 修改resolv.conf

```bash
vim /etc/resolv.conf
```

修改nameserver

```bash
nameserver 114.114.114.114
```

退出系统

```bash
wsl --shutdown
```

关闭deepin系统，重新运行。

在wsl中的系统中，运行

```bash
export ALL_PROXY="http://<Windows的IP地址>:<代理端口>" 来设置代理环境变量。
例如 export ALL_PROXY="http://172.19.80.1:7890"
```

# 参考

[在wsl中安装并运行deepin](https://blog.csdn.net/sinat_14817045/article/details/124286821)

[WSL和DeepinWSL的安装与中文界面配置](https://www.bilibili.com/read/cv16279419)

[解决WIN10 WSL安装报错](https://www.bilibili.com/read/cv21175889/)

[WSL2安装配置教程（XRDP图形界面）](https://blog.csdn.net/MANX98/article/details/127486532)

[为wsl2安装图形化界面](https://www.bilibili.com/read/cv15335653)

[Deepin GNU/Linux的WSL 2发行版](https://www.cnblogs.com/mobeisiran/p/16987272.html)

# 记录

## 使用wslg运行应用

## X11模式下

### 问题一_GTK_FRAME_EXTENTS 原子

`Failed to create atom with name _GTK_FRAME_EXTENTS`

可能应用使用了一个不受支持的X11扩展，导致无法创建_GTK_FRAME_EXTENTS这个原子。这个原子是用来存储窗口边框的大小和位置的信息的。

通过xprop工具，使用命令行启动xprop工具，再点击需要查看的应用可以查看到window id，复制下id。

* id是你想要设置属性的窗口的ID。
* left,right,top,bottom是你想要设置的边框的大小，单位是像素。
* 32c是这个属性的格式，表示32位的卡片型。

举个例子，假设你想要给一个窗口ID为0x1600045的窗口设置_GTK_FRAME_EXTENTS属性，让它的左右边框为10像素，上下边框为20像素，你可以使用这个命令：

```bash
xprop -id 0x1600045 -f _GTK_FRAME_EXTENTS 32c -set _GTK_FRAME_EXTENTS 10,10,20,20
```

注意，这个命令可能会破坏窗口的显示效果，不推荐使用。如果你想要恢复原来的属性，你可以使用这个命令：

```bash
xprop -id 0x1600045 -remove _GTK_FRAME_EXTENTS
```

### 尝试通过xstrace调试应用

## Wayland模式下

添加环境变量

```bash
export XDG_SESSION_TYPE="wayland"
```

不过在wayland模式下，部分应用有问题

- 多出标题栏：
  - deepin-terminal
  - deepin-home-appstore-client
- 还是以x11模式显示
  - dde-file-manager

原因：

在deepin系统下应用标题栏绘制由窗管进行管理，在使用wslg的wayland模式下，使用的是[weston](https://gitlab.freedesktop.org/wayland/weston)管理的，应用的标题栏会被绘制。

解决办法：

在查看[kegechen/chore: dtkwidget csd without dxcb](https://github.com/kegechen/dtkwidget/commit/aad7d764297b87b865a5e3e38e3ad517d0de2441)的这次提交中发现，在qt代码中加入setWindowFlag(Qt::FramelessWindowHint) 方法，隐藏系统自动生成的默认边框。看是否能合入主线程中。

发现加入在dmainwindows的构造函数中加入setWindowFlag(Qt::FramelessWindowHint)，这样就可以让应用走csd模式，不过需要考虑兼容性问题。
