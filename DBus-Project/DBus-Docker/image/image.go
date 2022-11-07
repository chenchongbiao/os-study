package image

import (
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
	DbusPath        = "/com/bluesky/daemon/mdocker"
	DbusServiceName = "com.bluesky.daemon.mdocker"
	DbusInterface   = DbusServiceName
)

var (
	cli, err = client.NewClientWithOpts(client.WithAPIVersionNegotiation(), client.WithHost("tcp://localhost:2375"))

	// imageName     = "docker.io/busybox"
	// containerID   = ""
	// containerName = "busybox-test"
)

type Image struct {
	// methods *struct {
	// 	Pull func() `out:"result"`
	// }
}

func (image *Image) GetInterfaceName() string {
	return DbusInterface
}

func NewImage(service *dbusutil.Service) *Image {
	image := Image{}
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
