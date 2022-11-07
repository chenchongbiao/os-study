package image

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
	dbusPath        = "/com/bluesky/daemon/mdocker/Image"
	dbusServiceName = "com.bluesky.daemon.mdocker.Image"
	dbusInterface   = dbusServiceName
)

var (
	cli, err = client.NewClientWithOpts(client.WithAPIVersionNegotiation(), client.WithHost("tcp://localhost:2375"))

	// imageName     = "docker.io/busybox"
	// containerID   = ""
	// containerName = "busybox-test"
)

type Image struct {
	service *dbusutil.Service
}

func (image *Image) GetInterfaceName() string {
	return dbusServiceName
}

func NewImage(service *dbusutil.Service) *Image {
	image := Image{
		service: service,
	}
	err = service.Export(dbusPath, &image)
	if err != nil {
		fmt.Println(err)
	}

	err = service.RequestName(dbusServiceName)
	if err != nil {
		fmt.Println(err)
	}
	return &image
}

func (image *Image) Pull() (result string, err *dbus.Error) {
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
