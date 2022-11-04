package main

import (
	"context"
	"io"
	"log"
	"os"

	"github.com/docker/docker/api/types"
	"github.com/docker/docker/client"
)

// const (
// 	nilObjPath      = dbus.ObjectPath("/")
// 	dbusServiceName = "com.bluesky.daemon.test"
// 	dbusPath        = "/com/bluesky/daemon/test"
// 	dbusInterface   = "com.bluesky.daemon.test"
// )

// type Manager struct {
// 	service    *dbusutil.Service
// 	sysSigLoop *dbusutil.SignalLoop
// }

// func (*Manager) GetInterfaceName() (interfacename string) {
// 	return dbusInterface
// }

// func (v *Manager) GetExportedMethods() dbusutil.ExportedMethods {
// 	return dbusutil.ExportedMethods{
// 		{
// 			Name:   "GetInterfaceName",
// 			Fn:     v.GetInterfaceName,
// 			InArgs: []string{"interfacename"},
// 		},
// 	}
// }

var (
	// cli, err = client.NewClientWithOpts(client.WithHost("tcp://localhost:12375"))

	cli, err      = client.NewClientWithOpts(client.WithAPIVersionNegotiation(), client.WithHost("tcp://localhost:12375"))
	imageName     = "docker.io/busybox"
	containerID   = ""
	containerName = "busybox-test"
)

func main() {
	// service := dbusutil.NewSessionService()
	// e := &Manager{}
	// service.Export(e)
	// service.RequestName(dbusServiceName)
	pullImage()
}

// 拉取镜像
func pullImage() {
	ctx := context.Background()

	reader, err := cli.ImagePull(ctx, imageName, types.ImagePullOptions{})
	if err != nil {
		log.Fatal("pull image error", err)
	}

	io.Copy(os.Stdout, reader)
}
