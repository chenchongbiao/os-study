# WSL安装deepin

## 前置条件

1.使用WSL 需要开启虚拟化。

在控制面板，程序开启和关闭，打开“适用于Linux的Windows子系统”和“虚拟机平台”两个可选功能，Hyper-v。

2.系统版本

- 对于 x64 系统：版本 1903 或更高版本，内部版本 18362 或更高版本。
- 对于 ARM64 系统：版本 2004 或更高版本，内部版本 19041 或更高版本。

3.在virtualbox安装windows虚拟机，需要在设置中为windows虚拟机启用嵌套虚拟化，即勾选“启用VT-x/AMD-V”和“启用嵌套分页”选项。

4.设置WSL 2为默认版本

```bash
wsl --set-default-version 2
```

## 安装系统

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

### 使用qemu创建

#### 安装qemu

```bash
sudo apt install qemu
```

#### 创建vhdx文件

```bash
qemu-img create -f vhdx disk.vhdx 50G
```

创建一个disk.vhdx的文件，50G大小，动态分配。

#### 创建虚拟机

```bash
qemu-system-x86_64 -m 4G -drive file=disk.vhdx,format=vhdx -cdrom foo.iso -boot order=dc
```

命令来启动虚拟机，并指定 **vhdx** 文件作为虚拟硬盘，**iso** 文件作为光盘镜像，其中 `foo.iso` 是镜像文件名，`-m 4G` 是分配给虚拟机的内存大小，`-boot order=dc` 是指定启动顺序为先光盘后硬盘。

根据提示进行系统安装。

## 添加软件源

### 打包tar文件

使用tar命令将解压后的目录打包成一个tar文件

```bash
cd rootfs
tar -cf rootfs.tar *
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

详细使用方法参考[yuk7/wsld](https://github.com/yuk7/wsldl#wsldl)

## 添加一个sudo用户

```bash
# 添加一个bluesky用户
useradd -m bluesky
passwd bluesky
usermod -aG sudo bluesky

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

添加配置项,将wsl关闭后，重新进入。

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

## 安装界面

### xrdp方式

安装xrdp

```bash
sudo apt install xrdp xorg xorgxrdp
```

#### 配置

```bash
sudo cp /etc/xrdp/xrdp.ini /etc/xrdp/xrdp.ini.bak
sudo sed -i 's/3389/3390/g' /etc/xrdp/xrdp.ini
sudo sed -i 's/max_bpp=32/#max_bpp=32\\nmax_bpp=128/g' /etc/xrdp/xrdp.ini
sudo sed -i 's/xserverbpp=24/#xserverbpp=24\\nxserverbpp=128/g' /etc/xrdp/xrdp.ini
echo dde-session > ~/.xsession
```

配置DISPLAY环境变量

```bash
vim ~/.bashrc
```

```bash
export DISPLAY=0:0
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

# 参考

[在wsl中安装并运行deepin](https://blog.csdn.net/sinat_14817045/article/details/124286821)

[WSL和DeepinWSL的安装与中文界面配置](https://www.bilibili.com/read/cv16279419)

[解决WIN10 WSL安装报错](https://www.bilibili.com/read/cv21175889/)

[WSL2安装配置教程（XRDP图形界面）](https://blog.csdn.net/MANX98/article/details/127486532)

[为wsl2安装图形化界面](https://www.bilibili.com/read/cv15335653)

[Deepin GNU/Linux的WSL 2发行版](https://www.cnblogs.com/mobeisiran/p/16987272.html)

# 记录

## 启动lightdm错误

* 检查lightdm的权限或所有者是否正确，你可以使用

```bash
ls -l /usr/sbin/lightdm和ls -l /etc/lightdm来查看相关文件的权限和所有者

```

```bash
chown root:root /usr/sbin/lightdm和chmod 755 /usr/sbin/lightdm来修复权限和所有者
```

```
lightdm --test-mode --debug
```

命令来测试lightdm

## systemd设置环境变量

为所有的服务设置环境变量，可以在/etc/systemd/system.conf文件中使用DefaultEnvironment=选项。

```bash
DefaultEnvironment= "DISPLAY=:0" "XAUTHORITY=/home/username/.Xauthority"
```

可以使用EnvironmentFile=选项来指定一个包含环境变量的文件。

```bash
EnvironmentFile=/etc/test_env_service/var_file
```

systemctl status --user dde-filemanager-server.service

## dde-dock崩溃

[Warning][ ] Connecting to deprecated signal QDBusConnectionInterface::serviceOwnerChanged(QString,QString,QString)
20230529.09:31:15.041[Info][RecentAppHelper::updateRecentVisible 157 ] recent Widget count: 0 , app Widget count 0

* [在/usr/share/applications目录下创建一个dde-dock.desktop文件，内容如下](https://blog.csdn.net/weixin_39652658/article/details/116967205)：

```
[Desktop Entry]
Comment=dde-dock
Exec=dde-dock
Hidden=false
Icon=desktop
Name=dde-dock
Terminal=false
Type=Application
Version=1.0
```
