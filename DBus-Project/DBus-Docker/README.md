# 记录

将使用的clone后，运行代码出现use exports (variable of type "github.com/docker/go-connections/nat".PortSet) as type "github.com/docker/docker/vendor/github.com/docker/go-connections/nat".PortSet in struct literal

因为在docker的源代码下vendor目录嵌套了目录，将vendor/github.com/docker/go-connections重命名或者删除掉。
