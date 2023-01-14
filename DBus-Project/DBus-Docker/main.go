package main

import (
	"fmt"

	"./config"
	"./container"
	"./image"
	"./network"
	"github.com/docker/docker/client"
	"github.com/linuxdeepin/go-lib/dbusutil"
	_ "github.com/mattn/go-sqlite3"
)

/*
暴露端口
str="/usr/bin/dockerd -H tcp://localhost:2375 -H unix:///var/run/docker.sock "
sudo sed -i "s@/usr/bin/dockerd@$str@" /usr/lib/systemd/system/docker.service
sudo systemctl daemon-reload && systemctl restart docker

将登录用户加入到docker用户组中
sudo gpasswd -a $USER docker && newgrp docker
*/

var (
	cli, err = client.NewClientWithOpts(client.FromEnv, client.WithAPIVersionNegotiation())
)

func main() {
	service, err := dbusutil.NewSessionService()
	db, err := config.InitDatabase()
	if err != nil {
		fmt.Println("数据库初始化失败", err)
		return
	}

	img := image.NewImage(service, cli)
	fmt.Println("镜像服务启动成功", img)
	con := container.NewContainer(service, cli)
	fmt.Println("容器服务启动成功", con)
	net := network.NewNetwork(service, cli)
	fmt.Println("容器服务启动成功", net)
	service.Wait()
	db.Close()
}
