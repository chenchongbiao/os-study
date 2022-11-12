package main

import (
	"fmt"

	"./container"
	"./image"
	"github.com/docker/docker/client"
	"github.com/linuxdeepin/go-lib/dbusutil"
)

/*
暴露端口
str="/usr/bin/dockerd -H tcp://localhost:2375 -H unix:///var/run/docker.sock "
sudo sed -i "s@/usr/bin/dockerd@$str@" /usr/lib/systemd/system/docker.service
sudo systemctl daemon-reload && systemctl restart docker

将当前用户加入到docker用户组
sudo usermod -aG docker ${USER} & sudo systemctl restart docker
*/

var (
	cli, err = client.NewClientWithOpts(client.WithAPIVersionNegotiation(), client.WithHost("tcp://localhost:2375"))

	imageName     = "docker.io/busybox"
	containerID   = ""
	containerName = "busybox-test"
)

func main() {
	service, err := dbusutil.NewSessionService()
	img := image.NewImage(service, cli)
	con := container.NewContainer(service)
	fmt.Println(img, err)
	fmt.Println(con, err)
	service.Wait()
}
