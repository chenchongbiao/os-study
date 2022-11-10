package container

type ContainerModel struct {
	ContaierID string // 容器ID
	Name       string // 容器名
	State      string // 状态
	Image      string // 镜像
	Port       string // 端口
	Command    string // 启动命令
}
