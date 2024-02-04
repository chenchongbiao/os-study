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
git clone git@github.com:ohmyzsh/ohmyzsh.git .oh-my-zsh
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

## z-shell/zi

z-shell/zi是一个基于Zsh的开源社区项目，它提供了一个强大的插件管理器，可以让你轻松地安装、更新、卸载和管理Zsh的插件和代码片段。它也支持一些高级功能，如异步加载、编译、钩子、补全、主题等。

设置安装位置并创建目录：

```bash
typeset -Ag ZI
typeset -gx ZI[HOME_DIR]="${HOME}/.zi" ZI[BIN_DIR]="${ZI[HOME_DIR]}/bin"
command mkdir -p "$ZI[BIN_DIR]"
```

克隆仓库

```bash
command git clone https://github.com/z-shell/zi.git "$ZI[BIN_DIR]"
```

要启用 Zi，请从先前设置的目录中获取 zi.zsh ，并将以下代码段放入 .zshrc 文件中：

```bash
typeset -A ZI
ZI[BIN_DIR]="${HOME}/.zi/bin"
source "${ZI[BIN_DIR]}/zi.zsh"

# 启用 Zi 补全
autoload -Uz _zi
(( ${+_comps} )) && _comps[zi]=_zi
```

要加载 Oh-My-Zsh 和 Prezto 插件，请使用 snippet 功能。片段是由 curl 、 wget 等下载的单个文件，正在执行下载工具的自动检测，直接从 URL 进行：

```bash
zi snippet 'https://github.com/robbyrussell/oh-my-zsh/raw/master/plugins/git/git.plugin.zsh'
zi snippet 'https://github.com/sorin-ionescu/prezto/blob/master/modules/helper/init.zsh'
```

对于 Oh-My-Zsh 和 Prezto，您可以使用 OMZ:: 和 PZT:: 简写：

```bash
zi snippet OMZ::plugins/git/git.plugin.zsh
zi snippet PZT::modules/helper/init.zsh
```

在 ~/.zshrc 添加

```bash
zi light-mode for \
  zdharma/fast-syntax-highlighting \
  zsh-users/zsh-autosuggestions \
  ohmyzsh/oh-my-zsh

ZSH_THEME="ys"
source $ZSH/oh-my-zsh.sh
```

## zinit

[Zinit](https://github.com/zdharma-continuum/zinit) 是一个灵活快速的 Zshell 插件管理器

自动安装

```bash
bash -c "$(curl --fail --show-error --silent --location https://raw.githubusercontent.com/zdharma-continuum/zinit/HEAD/scripts/install.sh)"
```

安装并重新加载 shell 后，通过以下方式编译 Zinit：

```bash
zinit self-update
```

`vim ~/.zshrc`

添加插件

```bash
zinit light-mode for \
        zsh-users/zsh-autosuggestions \
        zdharma-continuum/fast-syntax-highlighting
```

添加主题

```bash
zi ice depth=1; zi light romkatv/powerlevel10k
```

根据提示选择配置

# 参考

[ohmyzsh-wiki](https://github.com/ohmyzsh/ohmyzsh/wiki/Installing-ZSH)

[z-shell](https://wiki.zshell.dev/zh-Hans/docs/getting_started/installation)

[powerlevel10k](https://github.com/romkatv/powerlevel10k)
