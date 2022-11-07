package main

import (
	"context"
	"fmt"

	"./container"
	"./image"
	"github.com/docker/docker/client"
	"github.com/linuxdeepin/go-lib/dbusutil"
)

/*
str="/usr/bin/dockerd -H tcp://localhost:2375 -H unix:///var/run/docker.sock "
sudo sed -i "s@/usr/bin/dockerd@$str@" /usr/lib/systemd/system/docker.service
sudo systemctl daemon-reload && systemctl restart docker
*/

var (
	cli, err = client.NewClientWithOpts(client.WithAPIVersionNegotiation(), client.WithHost("tcp://localhost:2375"))

	imageName     = "docker.io/busybox"
	containerID   = ""
	containerName = "busybox-test"
)

func main() {
	ctx := context.Background()
	service, err := dbusutil.NewSessionService()
	img := image.NewImage(service, cli, ctx)
	con := container.NewContainer(service)
	fmt.Println(img, err)
	fmt.Println(con, err)
	service.Wait()
}
