package container

type ContainerModel struct {
	Name   string // 容器名
	Status int    // 状态
	Image  string // 镜像
	Port   string // 端口
	Ip     string // IP地址
}
