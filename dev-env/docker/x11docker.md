主机操作系统和映像的体系结构检查

Init和DBus

您可以使用xx启用此预定义用户

# 介绍

x11docker允许在Linux容器中运行图形桌面应用程序(和整个桌面)。

* [Docker](https://en.wikipedia.org/wiki/Docker_(software))、[podman](http://docs.podman.io/en/latest/) 、[nerdctl](https://github.com/containerd/nerdctl) 等容器工具允许在独立的容器环境中运行应用程序。
* Docker、podman、nerdctl 没有提供允许运行具有[图形用户界面](https://zh.wikipedia.org/wiki/%E5%9B%BE%E5%BD%A2%E7%94%A8%E6%88%B7%E7%95%8C%E9%9D%A2)的应用程序的[显示服务器](https://zh.wikipedia.org/wiki/%E8%A6%96%E7%AA%97%E7%B3%BB%E7%B5%B1#%E5%85%B6%E4%BB%96%E4%BD%9C%E6%A5%AD%E7%B3%BB%E7%B5%B1)。
* x11docker fills the gap. It runs an [X display server](https://en.wikipedia.org/wiki/X_Window_System) and provides it to containers.
  X servers can run from host or in a container of image [x11docker/xserver](https://github.com/mviereck/dockerfile-x11docker-xserver).
* x11docker 填补了这一空白。它运行一个[X 显示服务器](https://zh.wikipedia.org/wiki/X%E8%A6%96%E7%AA%97%E7%B3%BB%E7%B5%B1)并将其提供给容器。X 服务器可以在主机上运行，也可以在镜像 x11docker/xserver 的容器中运行。
* 此外，x11docker还进行了一些[安全设置](#安全设置)，以增强容器隔离并避免X安全泄漏。这样，沙盒环境就能很好地保护主机系统免受恶意软件或漏洞软件的侵害。

软件可以安装在一个可部署的映像中，其中包含一个基本的Linux系统。这有助于运行或部署由于依赖性问题而难以在多个系统上安装的软件。可以同时运行过时的版本或最新的开发版本。要处理的文件可以在主机和容器之间共享。

[x11docker wiki](https://github.com/mviereck/x11docker/wiki) 为 x11docker 的基本设置提供了一些操作指南。

## Docker Desktop 或 Docker Engine

Docker发布了一个名为 `Docker Desktop` 的版本，在 QEMU 虚拟机中运行 Docker 。x11docker 不支持此基于 VM 的版本。相反，将 x11docker 与使用主机内核运行容器的原生 "Docker Engine Server版本" 一起使用。

* 如果你从发行版的仓库中安装Docker，你会得到这个原生版本。
* 受支持的原生 Docker Engine 软件包名称大多为 `Docker.io` 或 `Docker ce`，与不受支持的基于VM的 `Docker desktop` 软件包相对。
* 如果你更喜欢 podman 而不是 Docker ，你不需要关心这个区别。

## TL;DR(简介)

快速开始

- [安装](#安装)x11docker时使用：

```bash
curl -fsSL https://raw.githubusercontent.com/mviereck/x11docker/master/x11docker | sudo bash -s -- --update
```

- 安装依赖项：
  - 拉取镜像 `x11docker/xserver` ，或者至少安装 `nxagent `或 `xpra `和 `xephyr`。
- 在容器中[运行]() GUI 时使用：

```bash
x11docker IMAGENAME [COMMAND]
```

- 添加选项：
  - `--desktop` 用于镜像中的桌面环境。
  - `--gpu` 用于硬件加速。

```shell
x11docker x11docker/xfce thunar
x11docker --desktop x11docker/xfce
x11docker --gpu x11docker/xfce glxgears
```

- 示例:

```shell
x11docker x11docker/xfce thunar
x11docker --desktop x11docker/xfce
x11docker --gpu x11docker/xfce glxgears
```

## 特色

- )))关注安全:
  - 通过运行额外的X服务器避免X安全漏洞。
  - 将容器功能限制在最低限度。
  - 容器用户和主机用户相同，以避免容器中的root用户。
- 低依赖:
  - 除了X和 `docker`、`podman` 或 `nerdctl` 之一之外，对主机没有强制依赖关系。建议：`nxagent` 和 `Xephyr`，或者镜像 `x11docker/xserver`。
  - 除了一些可选功能外，镜像内部没有依赖项。
- 一些可选功能，如GPU，声音，网络摄像头和打印机支持。
- 可以使用SSH、VNC或HTML5进行远程访问。
- 易于使用，实例:
  - `x11docker x11docker/fvwm xterm`
  - `x11docker --desktop --size 320x240 x11docker/lxde` （需要嵌套的X服务器 `Xephyr`）
    ![img](https://github.com/mviereck/x11docker/blob/screenshots/screenshot-retroterm.png?raw=true)![img](https://github.com/mviereck/x11docker/blob/screenshots/screenshot-lxde-small.png?raw=true)

## 支持的系统

x11docker 在 Linux 上运行，（有一些设置和限制）在 MS Windows 上运行。x11docker 不在macOS 上运行，除非在 Linux 虚拟机中运行。

# 终端语法

只需要输入 `x11docker IMAGENAME [COMMAND]`。

- 使用 `x11docker --help` 获取选项帮助。
  - 用于镜像中的桌面环境选项 `-d, --desktop`.
  - 用于互网接入选项  `-I, --network`.
  - 完全不使用 X 服务使用选项 `-t, --tty`.
  - 获取带有选项的交互式TTY `-i, --interactive`.
  - 请参阅带有选项的生成的容器后端命令 `--debug`.
- 如果启动失败，请参阅故障排除。

常规语法：

```bash
用法:
要在新的X服务器上运行容器：
  x11docker IMAGE
  x11docker [OPTIONS] IMAGE [COMMAND]
  x11docker [OPTIONS] -- IMAGE [COMMAND [ARG1 ARG2 ...]]
  x11docker [OPTIONS] -- CUSTOM_RUN_OPTIONS -- IMAGE [COMMAND [ARG1 ARG2 ...]]
在新的 X 服务器上运行主机应用程序:
  x11docker [OPTIONS] --backend=host COMMAND
  x11docker [OPTIONS] --backend=host -- COMMAND [ARG1 ARG2 ...]
  x11docker [OPTIONS] --backend=host -- -- COMMAND [ARG1 ARG2 ...] -- [ARG3]
只运行空的新X服务器:
  x11docker [OPTIONS] --xonly
```

# 选项

一些常用功能的描述选项。

* 其中一些选项依赖于主机和/或映像。比较 wiki:功能依赖项
* 对于常用的选项组合，您可以使用选项创建快捷方式 `--preset`.

## X 服务器和 Wayland 合成器的选择参考

如果没有指定X服务器选项，x11docker会根据安装的依赖项以及给定或缺失的选项 `--desktop`、`--gpu` 和 `--wayland` 自动选择一个。最推荐的是 `nxagent` 和 `Xephyr`。

* 所有可能的 X 服务器和 Wayland 选项概述。

  * 使用 X 的选项 `--xorg`。
  * 使用选项 `-t，--tty` 可以在完全不使用 X 的情况下运行。

## 桌面或无缝模式

x11docker 假设你希望以无缝模式运行单个应用程序，即常规桌面上的单个窗口。若要在镜像中运行桌面环境，请添加选项 `--desktop`。

- 选项 `--nxagent` 和 `--xpra` 支持无缝模式。作为后备，不安全的选项 `--hostdisplay` 是可能的。
- 除 `--hostdisplay` 外，所有 X 服务器选项都支持带 `--Desktop` 的桌面模式。如果可以，x11docker更推荐 `--xephyr` 和 `--nxagent`。
- 特殊情况：带有窗口管理器的单个应用程序（选项--wm）。
  - 如果既没有安装 `nxagent` 也没有安装 `xpra`，但 `x11docker` 找到了像 `Xephyr` 这样的桌面X服务器，它可以避免不安全的选项 `hostdisplay`，并使用窗口管理器运行 `Xephyr`。

## 联网

默认情况下，x11docker 禁用 `--Network=none` 容器的网络访问，因为它针对的是尽可能好的容器隔离。要允许 `internet` 访问，请设置选项 `-I` 或 `-network`。

## 容器中的共享文件夹、卷和用户家目录

正在运行的容器系统中的更改将丢失，创建的容器将被丢弃。对于持久数据存储，您可以共享主机目录或卷：

- 选项 `-m，--home` 在 `~/.local/share/x11docker/IMAGENAME` 中创建一个主机目录，该目录与容器共享并作为其 `HOME` 目录装入。容器主目录中的文件和用户配置更改将持续存在。x11docker 创建一个从 `~/.local/share/x11ocker` 到 `~/x11docker` 的软链接。
  - 可以使用 `--HOME=DIR` 为容器 `HOME` 指定另一个主机目录。
  - 可以使用 `--HOME=volume` 为容器 `HOME` 指定卷。
- 选项 `--share PATH` 在容器中的同一位置装载主机文件或文件夹。
  - 可以使用 `--share volume` 指定卷。
  - `--share PATH:ro` 限制为只读访问。
  - `/dev` 中的设备文件也受支持。
- `$HOME` 的特殊情况：
  - `--home=$HOME` 将使用主机用户家目录作为容器家目录。
  - `--share $HOME` 会将主机HOME符号链接为容器HOME的子文件夹。

请注意，如果 `HOME` 为空，x11docker 会将容器中的 `/etc/skel `中的文件复制到 `HOME`。这允许在图像中提供预定义的用户配置。

## GPU硬件加速

OpenGL 的硬件加速可以通过选项 `-g，--gpu` 来实现。

- 在大多数情况下，在主机上使用开源驱动程序时，这将开箱即用。否则，请查看 wiki:功能依赖关系。
- 对于驱动程序版本 <v470.X 和 Xwayland<v222.1.2，闭源 NVIDIA 驱动程序需要一些设置并支持较少的 x11docker X 服务器选项。

## 剪贴板

剪贴板共享可以使用选项 `-c，--Clipboard[=ARG]`。

- 可选参数 `superv` 和 `altv` 仅在按下 [SUPER][v] 或 [ALT][v] 键时向容器提供主机剪贴板内容。
- 可选参数 `oneway` 仅将剪贴板内容从容器传输到主机。

## 声音

通过选项 `-p、--pulseudio` 和 `--alsa` 可以发出声音。

- 对于带有 `--pulseudio` 的 `pulseudio-sound`，您需要主机上的 `pulseadio` 和镜像中的 `pulseaudio`（至少是 `pulseadio-client` 库）。比较 wiki:功能相关性。
- 对于带有 `--alsa` 的ALSA声音，您可能需要指定一个带有例如 `--alsa=Generic` 的声卡。使用 `aplay-l` 获取可用声卡的列表。

## 网络摄像头

主机上的网络摄像头可以通过选项 `--webcam`。

- 如果镜像中的网络摄像头应用程序失败，请在镜像中安装--gpu依赖项。比较wiki:功能相关性。
- `guvcview` 需要 `--pulseudio` 或 `--alsa`。
- `cheese` 和 [`gnome-ring`](https://ring.cx/) 需要 `--init=systemd`。

## 打印机

主机上的打印机可以通过选项 `--printer` 提供给容器。

- 它需要主机上的 `cups`，这是大多数 Linux 发行版的默认打印机服务器。
- 容器需要镜像中的 `cups` 客户端库。比较wiki:功能相关性。

## 语言区域设置

x11docker提供了选项 `--lang`，用于灵活的语言区域设置。

- --lang 没有参数的 `LANG` 将容器中的 `LANG` 设置为和主机上的相同。与 `--lang=$LANG` 相同
- x11docker 将在容器启动时检查镜像中是否已经存在所需的区域设置并启用它。
- 如果 x11docker 找不到区域设置，它会在容器启动时创建它。这需要一些镜像中的区域设置包。比较wiki:功能相关性。
- 示例：`--lang=de` 表示德语，`--lang=zh_CN` 表示中文，`--lang=ru` 表示俄语，`--lang=$LANG` 表示您的主机区域设置。
- 为了支持中文、日语和韩语字符，请在镜像中安装类似arphic uming字体的字体。
- 通过一些容器设置，可以使用 `fcitx-pinyin` 等键盘输入法。参考 [#269](https://github.com/mviereck/x11docker/issues/269#issuecomment-667124421)。

## Wayland

要运行 `Wayland` 而不是 X 服务器，x11docker 提供了选项 `--Wayland`、`--weston`、`--kwin` 和 `--hostwayland`。想了解更多信息，请访问wiki：Wayland选项说明。

- 选项 `--wayland` 自动设置wayland环境。它涉及选项 `--desktop`。
- 选项 `--weston` 和 `--kwin` 运行Wayland合成器 `weston` 或 `kwin_wayland`。
- 选项 `--hostwayland` 可以在主机Wayland桌面上无缝运行应用程序，如Gnome 3、KDE 5和Sway。
- 示例：Wayland上的 `xfce4-terminal`：`x11docker --wayland x11docker/xfce xfce4-terminal`

## 系统初始化

x11docke r支持多个init系统作为容器中的PID 1，并带有选项 `--init`。容器中的初始化解决了僵尸收割问题。默认情况下，x11docker 在 `/usr/bin/docker-init` 中使用tini。还提供 `systemd`、`SysVinit`、`runit`、`OpenRC` 和 `s6-overlay`。`elogind` 也得到了支持。看看Docker中的wiki:Init系统。

## DBus

一些桌面环境和应用程序需要一个正在运行的 DBus 系统守护进程和 / 或 DBus 用户会话。DBus 选项需要镜像中提供 `dbus`。

- 使用 `--dbus` 来运行dbus用户会话守护进程。
- DBus 系统守护进程将使用 init systems `systemd`、`openrc`、`runit` 和 `sysvinit`（选项 `--init`）自动启动。
  - 在没有高级init系统的情况下，也可以使用 `--dbus=system` 运行DBus系统守护进程。但是，这在某些情况下会造成麻烦，一般不建议这样做。
- 使用 `--hostdbus` 连接到主机DBus用户会话。
- 使用 `--share /run/dbus/system_bus_socket` 共享主机 DBus 系统套接字。

## 容器运行时

根据 OCI 运行时规范，可以运行具有不同后端的容器。Docker的默认运行时是runc。您可以使用选项 `--runtime=RUNTIME` 指定另一个。x11docker 已知并支持的容器运行时有：

- runc:Docker 默认值。
- nvidia：专门的 runc 分支，支持 nvidia/nvidia-docker 镜像。
- crun：具有相同功能的 runc 的快速、轻量级替代品。
- oci：在 [#205](https://github.com/mviereck/x11docker/issues/205) 中报告了运行时，没有找到任何文档。由x11docker 类 runc 处理。
- sysbox-runtime: 基于runc，旨在增强容器隔离性。支持尚处于试验阶段。需要Sybox>=0.5.0和内核版本>=5.12。

使用不同的运行时对rootful Docker进行了很好的测试，但对其他后端设置没有测试。

示例：/etc/docker/daemon.json中可能的运行时配置：

```json
{
  "default-runtime": "runc",
  "runtimes": {
    "crun": {
      "path": "/usr/local/bin/crun",
      "runtimeArgs": []
    },
    "nvidia": {
      "path": "nvidia-container-runtime",
      "runtimeArgs": []
    },
    "sysbox-runc": {
      "path": "/usr/bin/sysbox-runc"
    }
  }
}
```

## docker 以外的后端

x11docker 支持容器工具 Docker、podman 和 nerdctl，并在 rootful 和 rootless mode 模式下选择 `--backend=BACKEND`。`--backend` 支持的参数: `docker` `podman` `nerdctl` `host`

容器后端：

- 默认情况下，x11docker尝试运行docker。
  - 要将默认的 `--backend=docker` 更改为另一个类似于 `--backend=podman` 的文件，请为 `--preset`创建一个默认文件。
- 建议用于 rootful 容器后端：`docker` 或 `podman`
- 推荐用于 rootless 容器后端：`podman`
  - 只有 `podman` 允许选项 `--home`处于无根模式。
  - 只有 `podman` 提供了在rootless模式下有用的文件所有权选项 `--share` 。
- `--backend=nerdctl` 还处于实验阶段。它支持有根和无根模式。`nerdctl` 正处于重度开发阶段。

其他实际上没有容器的受支持后端：

- `--backend=host` 在新的 X 服务器上运行主机应用程序。不涉及集装箱化。

## 预配置 --preset

对于经常使用的选项组合，您可能希望使用选项 `--preset FILENAME` 以具有命令快捷方式。`FILENAME` 是 `~/.config/x11docker/preset` 或 `/etc/x11dockr/preset` 中的一个文件，其中包含一些 x11docker 选项。

`multimedia` 示例：创建一个文件 `~/.config/x11docker/preset/metrimedia`：

```bash
--gpu
--webcam
--printer
--pulseaudio
--clipboard
--share ~/Videos
--share ~/Music
```

像这样使用：`x11docker --preset=multimedia jess/vlc`

深度桌面示例：代替长命令

```bash
x11docker --desktop --init=systemd --gpu --pulseaudio --home -- --cap-add=IPC_LOCK -- x11docker/deepin
```

你可以创建一个包含所需选项甚至图像名称的文件 `~/.config/x11docker/preset/deepin`：

```bash
--desktop 
--init=systemd
--gpu
--pulseaudio
--home
-- 
--cap-add=IPC_LOCK
-- 
x11docker/deepin
```

使用：`x11docker--preset=deepin`运行

## 所有 x11docker sessions 会话的默认预设

你可以创建一个应用于所有x11docker会话的默认预设文件。您可以将其视为 x11docker 的配置文件。

示例：要始终使用 podman 而不是 docker，请在 `~/.config/x11docker/preset` 或 `/etc/x11dockr/preset` 中创建一个默认名称的文件，内容如下：

```bash
--backend=podman
```

这将导致 x11docker 始终使用 podman 而不是 docker，除非 x11dockr 命令中另有指定。

同样，可以指定其他和更多选项作为默认选项，例如 `--homebasedir=/my/containerhome/path`。请注意，本地用户默认文件将取代系统范围内的默认文件。

# 安全

x11docker 的作用是运行容器化的 GUI 应用程序，同时保留和改进容器隔离。核心概念是：

- 运行第二台X服务器以避免X安全漏洞。
  - 这与共享display:0的主机X套接字的广泛解决方案相反，从而打破了容器隔离，允许密钥记录和远程主机控制。（不过，x11docker提供了回退选项--hostdisplay）。
  - 身份验证使用 MIT-MAGIC-COOKIE 完成，与文件 `~/.Xauthority` 分开存储。
- 创建类似于主机用户的容器用户，以避免在容器中使用root。
  - 你也可以用 `--user=USERNAME` 指定另一个用户，或者用 `--user=RUID:GID` 指定一个不存在的用户。
  - 禁用可能的 root 密码并删除/etc/sudoers中的条目。
  - 若要使用映像中指定的 `USER`，请设置选项 `--USER=RETAIN`。x11docker 在这种情况下不会更改容器的 `/etc/passwd` 或 `/etc/sudoers`。选项 `--home` 将不可用。
- 将容器功能降至最低。
  - 设置 run 选项 `--cap-drop=ALL` 以放弃所有功能。大多数应用程序都不需要它们。
  - 设置 run 选项 `--security-opt=no-new-privileges`。
  - 可以使用 x11docker 选项 `--cap-default` 禁用这些限制，也可以使用 `--sudouser`、`--newprivileges` 减少这些限制。

也就是说，默认的 docker 功能和 seccomp/SELinux/appermor 配置文件设置得很好，可以保护主机系统。尽管如此，x11docker还是遵循了最小特权的原则。容器不应该具有其工作所不需要的功能或特权。

## 安全弱点

- x11docker 容器可能的 SELinux 限制已降级，带有 run 选项 `--security-opt label=type:container_runtime_t` 以允许访问新的 X unix套接字。更严格的解决方案是可取的。比较：SELinux 和 Docker：允许访问 /tmp/.X11-unix 中的 X unix 套接字
- 可能的用户命名空间重新映射设置被禁用，以允许选项 `--home` 和 `--share` 而不存在文件所有权问题。
  - 这不是一个问题，因为 x11docker 已经避免了容器中的根目录。
  - 异常：没有为 `--user=RETAIN` 禁用用户命名空间重新映射。
- x11docker 提供了几种不同的X服务器选项。每个涉及的 X 服务器可能都有各自的漏洞。x11docker 只涵盖由 X11 协议设计引起的众所周知的 X 安全漏洞。
  - 如果镜像 x11docker/xserver 可用，则会为大多数受支持的 X 服务器设置额外的安全层。如果可用，它将在大多数情况下自动使用。使用选项 `--xc=yes` 强制使用它。

## 降低容器隔离的选项

x11docker 在终端中显示警告消息，如果选择了降低容器隔离的选项。请注意，x11docker 不检查自定义 DOCKER_UN_OPTIONS。

最重要的是：

- `--hostdisplay` 共享 display:0 的主机 X 套接字，而不是运行第二台 X 服务器。
  - 提供所谓的不受信任的 cookie 可以减少滥用的风险，但不要依赖于此。
  - 如果另外使用 `--gpu` 或 `--clipboard`，选项 `--ipc=host` 和可信 cookie 将被启用，并且不会留下任何针对X安全泄漏的保护。
  - 如果您不关心容器隔离，`x11docker --hostdisplay --gpu` 是一个不安全但非常快速的设置，没有任何开销。
- `--gpu` 允许访问gpu硬件。这可能被滥用以从主机获取窗口内容（palinopsia错误），并使 GPU rootkit（如键盘记录器）成为可能。
- `--pulseudio` 和 `--alsa` 允许捕获来自主机的音频输出和麦克风输入。

降低安全性但不需要常规使用的特殊选项：

- `--sudouser` 允许 `su` 和 `sudo` 使用 `x11docker` 作为容器用户的密码。如果某个应用程序以某种方式脱离容器，它可能会损害您的主机系统。允许x11docker放弃的许多容器功能。
- `--cap-default` 禁用 x11docker 的容器安全强化，并返回到由后端docker、podman或nerdctl提供的默认容器功能。如果某个应用程序以某种方式脱离容器，它可能会损害您的主机系统。
- `--init=systemd|sysvinit|openrc|runit` 允许x11docker放弃的一些容器功能 `--init=systemd` 还共享对 `/sys/fs/cgroup` 的访问权限。某些进程将在容器中以 root 身份运行。如果根进程以某种方式脱离容器，它可能会损害您的主机系统。允许x11docker放弃的许多容器功能。
- `--hostdbus` 允许通过DBus与主机应用程序进行通信。

## 沙箱

x11docker 增强的容器隔离允许将容器用作沙箱，可以很好地保护主机系统免受可能的恶意或有缺陷的软件的攻击。尽管如此，没有任何沙箱解决方案可以提供完美的安全保护，Docker即使有x11docker的增强安全设置也不例外。

使用 x11docker 作为沙箱并不是为了运行明显恶意的软件。而是将其用作：

- 兼容性环境，用于运行由于依赖性问题而难以或无法在主机上安装的软件。
- 开发环境中要收集库、编译器等，保持主机整洁。
- 开发环境，以减轻意外/错误行为造成的损害。
- 最坏情况下可能是恶意软件的安全层。示例：启用 javascript 的互联网浏览器，或使用 MS Windows 应用程序的 wine。

x11docker 已经限制了进程功能。您还可以使用选项 `--limit` 来限制对 CPU 和 RAM 的访问。默认情况下，限制为50%的可用 CPU 和50%的当前可用RAM。另一个数量可以用 `--limit=FACTOR` 指定，其中FACTOR大于零且小于或等于一。

要了解更多自定义微调，请查看[Docker文档：限制容器的资源。](https://docs.docker.com/config/containers/resource_constraints)

警告：没有任何限制可以防止容器溢出存储容器的硬盘或共享文件夹。

## 安全性和功能检查

要检查容器隔离和一些功能选项，请使用镜像 `x11docker/check` 并尝试使用几个选项。

- `x11docker --hostdisplay --gpu x11docker/check` 是一个不安全的设置。它很好地展示了常见的X安全漏洞。
- 添加诸如 `--pulseaudio --alsa --webcam --clipboard --printer` 类的选项来检查它们的功能。

# 安装

请注意，x11docker 只是一个没有库依赖关系的bash脚本。基本上，它只是X服务器和容器后端docker、podman 和 nerdctl 的包装器。要允许高级使用 x11docker 功能，请参阅“依赖关系”一章。

## 从分发存储库安装

x11docker在某些发行版中作为软件包提供。

稳定版本：

![img](https://camo.githubusercontent.com/7e131b2c27d233d6962c915cdfc50722bb21c98816566f480c5657e5c7b00abe/68747470733a2f2f7265706f6c6f67792e6f72672f62616467652f766572746963616c2d616c6c7265706f732f783131646f636b65722e737667)

最新git master/beta版本：

![img](https://camo.githubusercontent.com/96be21f3d01260c93deae61144868f0e8e237bb39b1948e7b5f2bfa2a853f84a/68747470733a2f2f7265706f6c6f67792e6f72672f62616467652f76657273696f6e2d666f722d7265706f2f6175722f783131646f636b65722e7376673f616c6c6f775f69676e6f7265643d31)

非常感谢那些决定提供这些软件包的维护人员！在wiki中有一些关于打包x11docker的提示。

## 手动安装

### 安装选项

作为 root 用户，您可以在系统目录中安装、更新和删除 x11docker，以便在系统范围内可用：

- x11docker --install：从当前目录安装x11dockr。（从提取的zip文件或克隆的git存储库进行安装很有用。）
- x11docker --update：从github下载并安装最新版本。
- x11docker --update-master：从github下载并安装最新的master版本。
- x11docker --remove：删除 x11dockr 安装的所有文件。
  - 注意：这不会删除 `~/.local/share/x11docker`，因为它存储选项 `--home` 的持久文件。
- x11docker --remove-oldprefix：在版本7.6.0之前，x11dockr 将自己安装到 `/usr/bin` 中。现在它安装到 `/usr/local/bin `中。使用 `--remove-oldprefix `删除 `/usr/bin` 安装。

要查看当前和即将更新的版本之间的差异，您可以为 `--update` 和 `--updatemaster` 使用可选的参数diff。示例：`x11docker --update-master=diff` 将在不安装的情况下向您显示从当前安装到最新master/beta版本的代码更改。

### 已安装的文件

安装的作用（仅供参考）：

- 将脚本 `x11docker` 复制到 `/usr/local/bin`。
- 使用 `xdg-icon-resource` 在 `/usr/share/icons` 下安装图标 `x11docker.png`。
- 将文档 `README.md`、`CHANGELOG.md` 和 `LICENSE.txt` 复制到 `/usr/local/share/doc/x11docker`。
- 将 x11docker 的手册页存储在 `/usr/local/share/man/man1/x11docker.1.gz` 中。

### 首次安装的最简便方式：

对于使用 `sudo` 的系统：

```bash
curl -fsSL https://raw.githubusercontent.com/mviereck/x11docker/master/x11docker | sudo bash -s -- --update
```

直接使用 root：

```
curl -fsSL https://raw.githubusercontent.com/mviereck/x11docker/master/x11docker | bash -s -- --update
```

### 最小安装

您可以任意位置运行使用 `bash x11docker` 或 `./x11docker`。对于最低限度的系统范围安装，请使用 `chmod +x x11docker` 使 x11dockr可执行，并将其移动到 `/usr/local/bin`（或PATH中的其他位置）。脚本 `x11docker` 本身之外的其他文件不是必不可少的。

### 在MS Windows上安装

* [WSL (Windows subsystem for Linux)](https://docs.microsoft.com/en-us/windows/wsl/about)
* [Cygwin](https://www.cygwin.com/)
* [MSYS2](https://www.msys2.org/)

有关更多信息，请访问 [wiki:x11docker on MS Windows](https://github.com/mviereck/x11docker/wiki/x11docker-on-MS-Windows)。

### 卸载

您可以使用 `x11docker --remove` 移除x11docker。这将删除上面列出的文件。它还将删除 `~/.cache/x11docker` 并停止所有正在运行的 `x11docker` 容器。x11docker不会删除：

- 用于持久数据存储的文件和文件夹，带有选项 `--home`。这些是：
  - 在 `~/.local/share/x11docker` 中存储持久数据。
  - 指向那里的Softlink `~/x11docker`。
- 你可能自己为 x11docker 创建的文件夹：
  - `~/.local/share/x11docker`
  - `~/.config/x11docker`

## 依赖

x11docker 可以与标准系统实用程序一起运行，而无需额外依赖主机或镜像。

- 作为核心，它只需要 `bash` 和 `docker`、`podman` 或 `nerdctl` 中的一个就可以在 X 上运行容器。
- x11docker还需要一个X服务器。x11docker可以自动使用镜像 `x11docker/xserver`，该服务器提供了大多数可选的 x11dockr 依赖项以及几个 X 服务器和 Wayland 合成器，因此您不需要在主机上安装它们。

  - 如果您喜欢在主机上安装依赖项：
    - 推荐的基本命令是: `nxagent` `Xephyr` `weston` `Xwayland` `xdotool` `xauth` `xinit` `xclip` `xhost` `xrandr` `xdpyinfo`。其中一些可能已经安装
    - 请参阅 [wiki: Dependencies - Recommended base](https://github.com/mviereck/x11docker/wiki/Dependencies#recommended-base) 以获取与您的分发相匹配的程序包列表。

镜像中的依赖项：

某些功能选项对主机和/或镜像有额外的依赖关系。这尤其影响选项 `--gpu`、`--printer` 和 `--pulseudio`。

参阅 [wiki: feature dependencies](https://github.com/mviereck/x11docker/wiki/Dependencies#dependencies-of-feature-options)

# 故障排除

要进行故障排除，请在终端中运行 `x11docker`。x11docker 在出现不安全、丢失或出错时显示警告。此外，如果选项不起作用并且使用了回退，它还会显示注释。它可能会提示解决一些问题。

## 核心检查

1. 确保您的 x11docker 版本是 `x11docker --update`（最新版本）或 `x11dockr --update-master`（最新测试版）的最新版本。
2. 仔细阅读常规x11docker消息。通常，他们已经给出了该做什么的提示。

- 使用选项 `-D，--debug` 可以查看一些内部消息。
- 使用选项 `-v，--verbose` 可以查看完整的日志文件输出。
- 您可以在 `~/.cache/x11docker/x11docker.log` 中找到最新调度的日志文件。

3. 请尝试其他X服务器选项。

- 某些应用程序因回退选项 `--hostdisplay` 而失败。添加 `--clipboard` 以禁用 `--hostdisplay` 的一些安全限制。
- 如果没有帮助，请安装其他 X 服务器。最稳定可靠的选项是 `--xephyr`。

## 特权检查

某些应用程序需要比x11docker默认情况下提供的更多权限或功能。一种尝试是允许多个权限，直到设置工作为止。而不是减少特权来找出真正需要的。（请注意 `--` 在以下命令中，不要错过它们）。

1. 添加权限：

- 尝试 `x11docker --cap-default IMAGENAME`
- 尝试 `x11docker --cap-default --ipc=host --network=host IMAGENAME`
- 尝试 `x11docker --cap-default --ipc=host --network=host --share /run/udev/data:ro -- --cap-add ALL --security-opt seccomp=unconfined --security-opt apparmor=unconfined --privileged -- IMAGENAME`

2. 减少特权：

- 按以下顺序逐个删除选项：`--privileged` `--security opt apparmor=unconfined` `--securitys opt seccomp=unconfine` `--cap add ALL--share/run/udev/data:ro` `--network=host` `--ipc=host` `--cap default`。只保留保持设置正常工作所需的选项。
- 选项 `--cap-default`可能已经足够了。它允许默认的容器功能，就像 docker|podman|nerdctl 在自己身上所做的那样。
  - 如果您愿意，可以在这里停止调试和减少。
  - 然后尝试减少：`x11docker --newprivileges -- --cap-add=SETPCAP --cap-add=MKNOD --cap-add=AUDIT_WRITE --cap-add=CHOWN --cap-add=NET_RAW --cap-add=DAC_OVERRIDE --cap-add=FOWNER --cap-add=FSETID --cap-add=KILL --cap-add=SETGID --cap-add=SETUID --cap-add=NET_BIND_SERVICE --cap-add=SYS_CHROOT --cap-add=SETFCAP -- IMAGENAME`
- `--cap-add ALL` 不应被视为一种解决方案。
  - 从以下命令中删除功能以查找您需要的功能：`x11docker --cap-default -- --cap-add=SYS_MODULE --cap-add=SYS_RAWIO --cap-add=SYS_PACCT --cap-add=SYS_ADMIN --cap-add=SYS_NICE --cap-add=SYS_RESOURCE --cap-add=SYS_TIME --cap-add=SYS_TTY_CONFIG --cap-add=AUDIT_CONTROL --cap-add=MAC_OVERRIDE --cap-add=MAC_ADMIN --cap-add=NET_ADMIN --cap-add=SYSLOG --cap-add=DAC_READ_SEARCH --cap-add=LINUX_IMMUTABLE --cap-add=NET_BROADCAST --cap-add=IPC_LOCK --cap-add=IPC_OWNER --cap-add=SYS_PTRACE --cap-add=SYS_BOOT --cap-add=LEASE --cap-add=WAKE_ALARM --cap-add=BLOCK_SUSPEND --cap-add=AUDIT_READ -- IMAGENAME`
  - 其中许多功能相当危险，不应允许用于容器。尤其值得一提的是 `SYS_ADMIN`。
- 选项  `--privileged` 不应被视为一种解决方案。基本上，它允许容器应用程序任意访问主机。
  - 您可能需要在 `/dev`、中共享一个设备文件，例如 `--share /dev/vboxdrv`。
- `--ipc=host` 和 `--network=host` 大大减少了容器隔离。更好的解决方案是可取的。

3. 打开票证，询问如何优化权限设置的可能性。

## 其他检查

**1.** 容器用户：默认情况下，x11docker设置一个类似于主机用户的无特权容器用户。

* 镜像可能具有 `USER` 规范，并且是为该用户设计的.
  * 使用 docker 检查图像中的 `USER` 规范 `docker inspect --format '{{.Config.User}}' IMAGENAME`
  * 你可以使用 `--user=RETAIN` 启用此预定义用户
* 容器可能需要一个 root 用户。尝试使用 `--user=root` ，或者添加 `--cap-default`。

**2.** Init和DBus

* 少数应用程序需要 DBus 用户守护进程。在镜像中安装 `dbus`，然后尝试选项 `--dbus`。
* 一些应用程序需要 systemd 和 / 或正在运行的 DBus 系统守护进程。在镜像中安装 `systemd`，然后尝试选项 `--init=systemd`。

**3.** 主机操作系统和镜像的体系结构检查

* 该镜像可能不是为主机操作系统的体系结构而构建的。
  （例如，镜像是为amd64构建的，但您的操作系统运行在arm上，例如RaspBerry PI）。
  如果不匹配，容器将意外退出&x11docker可能发出错误 `dockerrc(): Did not receive PID of PID1 in container`。
  * 可以使用 `docker inspect --format {{.Architecture}} IMAGENAME` 检查镜像架构
  * 可以使用 `uname -m` 检查主机体系结构。
  * 有关更多信息和多架构设置，请查看 [wiki: Multi-arch setups with QEMU](https://github.com/mviereck/x11docker/wiki/Multiarch-setups-with-QEMU).

# 参考

[x11docker Gihub 仓库](https://github.com/mviereck/x11docker)
