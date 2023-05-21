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

## 安装

以deepinv23-beta为例

1.先下载v23-beta的镜像。

2.使用解压工具将iso文件解压成文件夹。

3.找到filesystem.squashfs文件

3.下载squashfs-tools工具[https://github.com/plougher/squashfs-tools](https://github.com/plougher/squashfs-tools)

```bash
# 下载源码进入目录
cd squashfs-tools
sudo make && sudo make install
```

或者通过squashfs-tools进行安装

4.使用unsquashfs命令将filesystem.squashfs文件解压到一个目录

```bash
sudo unsquashfs -d mydir filesystem.squashfs
```

5.使用tar命令将解压后的目录打包成一个tar文件

```bash
sudo tar -cf mytar.tar mydir
```

6.将tar导入

```bash

```

# 参考

[在wsl中安装并运行deepin](https://blog.csdn.net/sinat_14817045/article/details/124286821)

[解决WIN10 WSL安装报错](https://www.bilibili.com/read/cv21175889/)
