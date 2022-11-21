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
	"github.com/docker/docker/api/types/mount"
	"github.com/docker/docker/api/types/network"
	"github.com/docker/docker/client"
	"github.com/docker/go-connections/nat"
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

func (c *ContainerService) CreateContainer(cmd []string, volume map[string]string) (busErr *dbus.Error) {
	// name, image, workDir string, cmd []string, volumes map[string]string, ports nat.PortSet
	fmt.Println("cmd", cmd)
	fmt.Println("volume", volume)
	ctx := context.Background()
	volumes := map[string]string{
		// "/home/bluesky/Desktop/name1": "/home/bluesky/Desktop/name2",
		"/home/bluesky/Desktop/name1": "/home/bluesky/Desktop/name1p",
	}
	// 文件挂载
	m := make([]mount.Mount, 0, len(volumes))
	for k, v := range volumes {
		m = append(m, mount.Mount{
			Type:   mount.TypeBind,
			Source: k,
			Target: v,
		})
	}

	exports := make(nat.PortSet)
	netPort := make(nat.PortMap)
	srcPort := "8080"
	// 网络端口映射
	natPort, _ := nat.NewPort("tcp", srcPort)
	exports[natPort] = struct{}{}
	dstPort := "8081"
	portList := make([]nat.PortBinding, 0, 1)
	portList = append(portList, nat.PortBinding{HostIP: "0.0.0.0", HostPort: dstPort})
	netPort[natPort] = portList

	resp, err := c.cli.ContainerCreate(ctx,
		// &containers.Config{
		// 	Image: "ubuntu:20.04",
		// 	ExposedPorts: nat.PortSet{
		// 		"8080/tcp": {},
		// 	},
		// },
		&containers.Config{
			Image:        "ubuntu:20.04",
			ExposedPorts: exports,
			Cmd:          []string{"bash"},
			Tty:          true,
		},
		&containers.HostConfig{
			// PortBindings: nat.PortMap{
			// 	"8080/tcp": []nat.PortBinding{
			// 		{
			// 			// 映射本地端口;
			// 			//HostPort给0默认随机选择一个空闲的端口
			// 			HostIP:   "",
			// 			HostPort: "8081",
			// 		},
			// 	},
			// },
			PortBindings: netPort,
			Mounts:       m,
			// Links: []string{"no-such-container"},
		},
		&network.NetworkingConfig{
			EndpointsConfig: map[string]*network.EndpointSettings{
				"bridge": {},
			},
		},
		nil,
		"test1")
	if err != nil {
		log.Fatal("容器创建失败", err)
		return nil
	}
	if err = c.cli.ContainerStart(ctx, resp.ID, types.ContainerStartOptions{}); err != nil {
		log.Fatal("容器启动失败", err)
		return nil
	}
	return nil
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

func (c *ContainerService) RestartContainer(containerID string) (busErr *dbus.Error) {
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

	list, _ := json.Marshal(containers)
	result = string(list)
	fmt.Println("容器列表获取成功")
	fmt.Println(containers)
	return result, nil
}

func (c *ContainerService) SearchContainerById(containerId string) (result string, busErr *dbus.Error) {
	ctx := context.Background()
	filter := filters.NewArgs()
	filter.Add("id", containerId)

	container, err := c.cli.ContainerList(ctx, types.ContainerListOptions{Filters: filter})

	if err != nil {
		log.Fatal("获取容器数据失败", err)
		return result, nil
	}

	list, _ := json.Marshal(container)
	result = string(list)
	fmt.Printf("获取容器数据成功%#v", container)
	return result, nil
}
