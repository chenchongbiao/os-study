package container

import (
	"context"
	"encoding/json"
	"fmt"
	"log"
	"time"

	"github.com/docker/docker/api/types"
	containers "github.com/docker/docker/api/types/container"
	"github.com/docker/docker/api/types/filters"
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

func (c *ContainerService) GetContainerList() (result string, busErr *dbus.Error) {
	ctx := context.Background()
	containers, err := c.cli.ContainerList(ctx, types.ContainerListOptions{All: true})
	if err != nil {
		log.Fatal("获取容器列表失败", err)
		result = "获取容器列表失败"
		return result, nil
	}

	// defer out.Close()
	// io.Copy(os.Stdout, out)
	list, _ := json.Marshal(containers)
	result = string(list)
	fmt.Println("容器列表获取成功")
	return result, nil
}

func (c *ContainerService) StopContainer(containerID string) (busErr *dbus.Error) {
	ctx := context.Background()

	timeout := int(time.Minute)
	err := c.cli.ContainerStop(ctx, containerID, containers.StopOptions{Timeout: &timeout})
	if err != nil {
		log.Fatal("容器停止失败 ", err.Error())
		return nil
	}
	fmt.Println("容器停止成功")
	return nil
}

func (c *ContainerService) StartContainer(containerID string) (busErr *dbus.Error) {
	ctx := context.Background()

	err := c.cli.ContainerStart(ctx, containerID, types.ContainerStartOptions{})
	if err != nil {
		log.Fatal("容器启动失败 ", err.Error())
		return nil
	}
	fmt.Println("容器启动成功")
	return nil
}

func (c *ContainerService) ReStartContainer(containerID string) (busErr *dbus.Error) {
	ctx := context.Background()

	timeout := int(time.Minute)
	err := c.cli.ContainerStop(ctx, containerID, containers.StopOptions{Timeout: &timeout})
	if err != nil {
		log.Fatal("容器停止失败 ", err.Error())
		return nil
	}
	fmt.Println("容器停止成功")
	err = c.cli.ContainerStart(ctx, containerID, types.ContainerStartOptions{})
	if err != nil {
		log.Fatal("容器重启失败 ", err.Error())
		return nil
	}
	fmt.Println("容器重启成功")
	return nil
}

func (c *ContainerService) SearchContainerListByName(containerName string) (result string, busErr *dbus.Error) {
	ctx := context.Background()
	filter := filters.NewArgs()
	filter.Add("name", containerName)

	containers, err := c.cli.ContainerList(ctx, types.ContainerListOptions{Filters: filter})

	if err != nil {
		log.Fatal("获取容器列表失败", err)
		result = "获取容器列表失败"
		return result, nil
	}

	fmt.Println(containers)
	list, _ := json.Marshal(containers)
	result = string(list)
	fmt.Println("容器列表获取成功")
	return result, nil
}
