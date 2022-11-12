package container

import (
	"fmt"
	"log"

	"github.com/docker/docker/client"
	"github.com/godbus/dbus"
	"github.com/linuxdeepin/go-lib/dbusutil"
)

/*
str="/usr/bin/dockerd -H tcp://localhost:2375 -H unix:///var/run/docker.sock "
sudo sed -i "s@/usr/bin/dockerd@$str@" /usr/lib/systemd/system/docker.service
sudo systemctl daemon-reload && systemctl restart docker
*/
const (
	dbusPath        = "/com/bluesky/docker/Container"
	dbusServiceName = "com.bluesky.docker.Container"
	dbusInterface   = dbusServiceName
)

var (
	cli, err = client.NewClientWithOpts(client.WithAPIVersionNegotiation(), client.WithHost("tcp://localhost:2375"))
	// imageName     = "docker.io/busybox"
	// containerID   = ""
	// containerName = "busybox-test"
)

type Container struct {
	service *dbusutil.Service
}

func (container *Container) GetInterfaceName() string {
	return dbusServiceName
}

func NewContainer(service *dbusutil.Service) *Container {
	container := Container{
		service: service,
	}
	err = service.Export(dbusPath, &container)
	if err != nil {
		fmt.Println(err)
	}

	err = service.RequestName(dbusServiceName)
	if err != nil {
		fmt.Println("NewContainer", err)
	}
	return &container
}

func (container *Container) List() (result string, err *dbus.Error) {
	// out, err := cli.ImagePull(image.Context, image.ImageName, image.ImagePullOptions)
	if err != nil {
		log.Fatal("image pull error ", err.Error())
	}
	// defer out.Close()
	// io.Copy(os.Stdout, out)
	result = "1111"
	err = nil
	return result, err
}
