package container

import (
	"context"
	"encoding/json"
	"fmt"

	"../config"
	"github.com/docker/docker/api/types"
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

type ContainerService struct {
	service *dbusutil.Service
	cli     *client.Client
}

func (c *ContainerService) GetInterfaceName() string {
	return dbusServiceName
}

func NewContainer(service *dbusutil.Service, cli *client.Client) *ContainerService {
	containerService := ContainerService{
		service: service,
		cli:     cli,
	}
	err := service.Export(dbusPath, &containerService)
	if err != nil {
		fmt.Println(err)
	}

	err = service.RequestName(dbusServiceName)
	if err != nil {
		fmt.Println("NewContainer", err)
	}
	return &containerService
}

func (c *ContainerService) GetContainerList() (result string, code int, busErr *dbus.Error) {
	ctx := context.Background()
	containers, err := c.cli.ContainerList(ctx, types.ContainerListOptions{All: true})
	if err != nil {
		fmt.Println("GetContainerList", err)
		result = "获取容器列表失败"
		code = config.Fail_code
		return result, code, nil
	}

	// defer out.Close()
	// io.Copy(os.Stdout, out)
	list, _ := json.Marshal(containers)
	result = string(list)
	code = config.Success_code
	return result, code, nil
}
