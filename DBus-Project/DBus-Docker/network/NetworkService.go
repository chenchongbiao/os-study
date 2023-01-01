package network

import (
	"context"
	"encoding/json"
	"fmt"
	"log"

	"github.com/docker/docker/api/types"
	"github.com/docker/docker/client"
	"github.com/godbus/dbus"
	"github.com/linuxdeepin/go-lib/dbusutil"
)

const (
	dbusPath        = "/com/bluesky/docker/Network"
	dbusServiceName = "com.bluesky.docker.Network"
	dbusInterface   = dbusServiceName
)

type Network struct {
	service *dbusutil.Service
	cli     *client.Client
}

func (net *Network) GetInterfaceName() string {
	return dbusServiceName
}

func NewNetwork(service *dbusutil.Service, cli *client.Client) *Network {
	network := Network{
		service: service,
		cli:     cli,
	}
	err := service.Export(dbusPath, &network)
	if err != nil {
		fmt.Println(err)
	}

	err = service.RequestName(dbusServiceName)
	if err != nil {
		fmt.Println(err)
	}
	return &network
}

func (net *Network) GetNetworkList() (result string, busErr *dbus.Error) {
	ctx := context.Background()
	networks, err := net.cli.NetworkList(ctx, types.NetworkListOptions{})
	if err != nil {
		log.Fatal("获取网络列表失败", err)
	}

	list, _ := json.Marshal(networks)
	result = string(list)
	fmt.Println(result)
	return result, nil
}
