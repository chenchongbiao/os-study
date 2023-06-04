# 介绍

Stow是一个符号链接管理器，它可以将文件系统上不同目录中的软件包或数据链接到同一个位置。这对于管理从源代码构建的软件的系统级和用户级安装非常有用，也可以用于更有控制性地管理用户主目录中的配置文件，特别是与版本控制系统结合使用。

# 安装

```bash
sudo apt install stow
```

```bash
# 查看版本号
stow --version
```

# 使用

以.zshrc为例

```bash
mkdir zsh
# 将.zshrc放入该文件夹中
mv ~/.zshrc zsh
stow zsh
```

可以在github上创建dotfiles仓库，在仓库下新建各种配置文件的目录，可以编写shell脚本来批量进行调用stow。
