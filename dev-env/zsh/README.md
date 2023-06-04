# 介绍

zsh是一个用于UNIX系统的命令解释器，或者说是一个 shell，因为它包装了你使用的命令。zsh是一个POSIX兼容的shell，也是Bourne shell（sh）和bash的一个流行的替代品。它的主要特点是注重用户的高度定制，这促使了一个活跃的开发者社区为zsh创建了各种扩展，包括自定义的、更有信息量的提示符状态行，以及与系统服务的集成。

# 安装

```bash
sudo apt-get install -y zsh
```

选择zsh作为默认shell

```bash
chsh -s /usr/bin/zsh
```

## 主题

oh-my-zsh是一个开源的、社区驱动的框架，用于管理你的zsh配置。它包含了300多个可选的插件（rails, git, macOS, hub, docker, homebrew, node, php, python等）和140多个主题。

需要借助git

```
sudo apt install git
```

```bash
git clone git@github.com:ohmyzsh/ohmyzsh.git
sh ohmyzsh/tools/install.sh
```

修改主题

```bash
vim ~/.zshrc
```

找到ZSH_THEME修改成想要的主题可以通过 `ls ~/.oh-my-zsh/themes`查看

```bash
ZSH_THEME="ys"
```

如果希望root也使用可以将 `export ZSH="$HOME/.oh-my-zsh"` 修改$HOME修改成当前用户的home目录的绝对路径如 `/home/bluesky` 并将这个.zshrc文件拷贝到root用户下。

```bash
sudo cp ~/.zshrc /root
sudo chsh -s /usr/bin/zsh
```

## 插件

zsh的插件是一些可以为你的shell提供额外功能和便利的扩展。你可以通过使用oh-my-zsh框架来启用和管理zsh的插件。

### 自动补全zsh-autosuggestions

```bash
git clone https://github.com/zsh-users/zsh-autosuggestions $ZSH_CUSTOM/plugins/zsh-autosuggestions
```

### **语法高亮插件 zsh-syntax-highlighting**

```bash
git clone https://github.com/zsh-users/zsh-syntax-highlighting.git $ZSH_CUSTOM/plugins/zsh-syntax-highlighting
```

### **自动跳转插件 autojump**

```bash
git clone https://github.com/joelthelion/autojump.git
cd autojump
./install.py
```

根据提示在.zshrc加入

```bash
vim ~/.zshrc
[[ -s /home/bluesky/.autojump/etc/profile.d/autojump.sh ]] && source /home/bluesky/.autojump/etc/profile.d/autojump.sh
```

## 启用插件

```bash
vim ~/.zshrc  
# 在plugins后括号里添加安装的插件名字
plugins=( git
          autojump
          zsh-autosuggestions
          zsh-syntax-highlighting
         )
# 最后刷新
source ~/.zshrc
```

# 参考

[ohmyzsh-wiki](https://github.com/ohmyzsh/ohmyzsh/wiki/Installing-ZSH)