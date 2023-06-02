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

详细使用方法参考[yuk7/wsld](https://github.com/yuk7/wsldl#wsldl)

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

## 设置显示管理器

修改xorg配置

```bash
sudo vim /etc/X11/xorg.conf
```

修改为以下内容

```bash
Section "ServerLayout"
    Identifier     "Layout10"
    Screen      10  "Screen10" 0 0
    InputDevice    "Keyboard0" "CoreKeyboard"
    InputDevice    "Mouse0" "CorePointer"
EndSection
```

修改lightdm的配置

```bash
sudo vim /etc/lightdm/lightdm.conf
```

```bash
[XDMCPServer]
ServerPath=/tmp/.X11-unix/X10
```

创建data目录

```bash
sudo mkdir -p /var/lib/lightdm/data
sudo chown -R lightdm:lightdm /var/lib/lightdm/data
```

sudo vim /etc/xrdp/xrdp.ini

[XDMCPServer]
X11DisplayOffset=0

修改DISPLAY

```bash
export DISPLAY=:/tmp/.X11-unix/X10
```

重启wsl

后面部分待验证

修改xorg监听端口

```bash
sudo sed -i 's/console/anybody/g' /etc/X11/Xwrapper.config
```

启用tmp.mount服务

```bash
sudo cp -v /usr/share/systemd/tmp.mount /etc/systemd/system/
sudo systemctl enable tmp.mount
```

重启wsl

```
wsl -t wsl的名称
```

检查挂载

```bash
mount | grep /tmp
```

修复权限

```
sudo mount -o remount,rw /tmp
sudo chown root:root /tmp/.X11-unix
sudo chmod 1777 /tmp/.X11-unix
```

1. [安装xrdp和xfce4](https://dhuyvett.github.io/Using-xrdp-with-WSL-2/)[^1^](https://dhuyvett.github.io/Using-xrdp-with-WSL-2/)[^2^](https://medium.com/@apph/desktop-gui-using-wsl2-xrdp-a870a2d32df8)，这是一个轻量级的桌面环境。
2. [修改xrdp的配置文件，把端口号改成3390](https://dhuyvett.github.io/Using-xrdp-with-WSL-2/)[^1^](https://dhuyvett.github.io/Using-xrdp-with-WSL-2/)[，并且设置最大色深为128]()[^3^](https://github.com/meyayl/packer-lxd-wsl2-systemd-xrdp)。
3. [安装Firefox和Flash插件]()[^1^](https://dhuyvett.github.io/Using-xrdp-with-WSL-2/)，如果你需要浏览网页或者看视频的话。
4. [安装xrdp-pulseaudio-installer]()[^1^](https://dhuyvett.github.io/Using-xrdp-with-WSL-2/)，这是一个可以让你在远程桌面中听到声音的工具。
5. [启动xrdp服务]()[^1^](https://dhuyvett.github.io/Using-xrdp-with-WSL-2/)[，并且在Windows上使用远程桌面连接到localhost:3390]()[^1^](https://dhuyvett.github.io/Using-xrdp-with-WSL-2/)。

* [使用top或htop命令来查看进程的CPU和内存占用情况，看看是否有资源不足或竞争的情况。]()[^1^](https://bing.com/search?q=%E8%BF%9B%E7%A8%8B%E5%90%AF%E5%8A%A8%E6%85%A2)
* [使用strace或ltrace命令来跟踪进程的系统调用或库函数调用，看看是否有异常或耗时的操作。](https://blog.csdn.net/liyu355/article/details/89735273)[^2^](https://blog.csdn.net/liyu355/article/details/89735273)[^3^](https://www.zhihu.com/question/339198302)
* 使用perf或xperf工具来分析进程的性能瓶颈，看看是否有优化的空间。
* 使用gdb或lldb工具来调试进程的运行状态，看看是否有错误或死锁的情况。
