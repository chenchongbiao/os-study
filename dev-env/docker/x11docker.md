# 介绍

x11docker允许在Linux容器中运行图形桌面应用程序(和整个桌面)。


* [Docker](https://en.wikipedia.org/wiki/Docker_(software))、[podman](http://docs.podman.io/en/latest/) 、[nerdctl](https://github.com/containerd/nerdctl) 等容器工具允许在独立的容器环境中运行应用程序。
* Docker、podman、nerdctl 没有提供允许运行具有[图形用户界面](https://zh.wikipedia.org/wiki/%E5%9B%BE%E5%BD%A2%E7%94%A8%E6%88%B7%E7%95%8C%E9%9D%A2)的应用程序的[显示服务器](https://zh.wikipedia.org/wiki/%E8%A6%96%E7%AA%97%E7%B3%BB%E7%B5%B1#%E5%85%B6%E4%BB%96%E4%BD%9C%E6%A5%AD%E7%B3%BB%E7%B5%B1)。
* x11docker fills the gap. It runs an [X display server](https://en.wikipedia.org/wiki/X_Window_System) and provides it to containers.
  X servers can run from host or in a container of image [x11docker/xserver](https://github.com/mviereck/dockerfile-x11docker-xserver).
* x11docker 填补了这一空白。它运行一个[X 显示服务器](https://zh.wikipedia.org/wiki/X%E8%A6%96%E7%AA%97%E7%B3%BB%E7%B5%B1)并将其提供给容器。X 服务器可以在主机上运行，也可以在镜像 x11docker/xserver 的容器中运行。
* Additionally x11docker does some [security setup](https://github.com/mviereck/x11docker#security) to enhance container isolation and to avoid X security leaks.
  This allows a [sandbox](https://github.com/mviereck/x11docker#sandbox) environment that fairly well protects the host system from possibly malicious or buggy software.
* Additionally x11docker does some security setup to enhance container isolation and to avoid X security leaks.
  This allows a sandbox environment that fairly well protects the host system from possibly malicious or buggy software.

# 参考

[x11docker Gihub 仓库](https://github.com/mviereck/x11docker)
