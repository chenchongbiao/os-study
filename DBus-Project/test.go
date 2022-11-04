package main

import (
	"fmt"

	"github.com/linuxdeepin/go-lib/dbusutil"
)

const (
	dbusServiceName = "com.bluesky.daemon.Search"
	dbusPath        = "/com/bluesky/daemon/Search"
	dbusInterface   = "com.bluesky.daemon.Search"
)

type Manager struct {
	service    *dbusutil.Service
	writeStart bool
	writeEnd   chan bool
}

func newManager(service *dbusutil.Service) *Manager {
	m := Manager{
		service: service,
	}

	m.writeStart = false

	return &m
}

func (*Manager) GetInterfaceName() (interfacename string) {
	return dbusInterface
}

func (v *Manager) GetExportedMethods() dbusutil.ExportedMethods {
	v.service.DelayAutoQuit()
	return dbusutil.ExportedMethods{
		{
			Name:    "Add",
			Fn:      v.GetInterfaceName,
			OutArgs: []string{"interfacename"},
		},
	}
}

func main() {
	service, err := dbusutil.NewSessionService()
	if err != nil {
		fmt.Println(err)
	}
	m := newManager(service)

	serverObj, err := service.NewServerObject(dbusPath, m)
	if err != nil {
		fmt.Println(err)
	}

	err = serverObj.SetWriteCallback(m, "Enabled", m.writeEnd)
	if err != nil {
		fmt.Println(err)
	}
	err = serverObj.Export()
	if err != nil {
		fmt.Println(err)
	}

	err = service.RequestName(dbusServiceName)
	if err != nil {
		return err
	}

	service.Wait()
}

// 拉取镜像
// func pullImage() {
// 	ctx := context.Background()

// 	reader, err := cli.ImagePull(ctx, imageName, types.ImagePullOptions{})
// 	if err != nil {
// 		log.Fatal("pull image error", err)
// 	}

// 	io.Copy(os.Stdout, reader)
// }
