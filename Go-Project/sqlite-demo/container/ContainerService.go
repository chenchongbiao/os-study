package container

import (
	"context"
	"database/sql"
	"encoding/json"
	"fmt"
	"strings"

	"github.com/docker/docker/api/types"
	"github.com/docker/docker/client"
)

type ContainerService struct {
	cli             *client.Client
	containerMapper *ContainerMapper
}

func InitService(cli *client.Client, db *sql.DB) *ContainerService {
	containerMapper, _ := InitDB(db)
	containerService := ContainerService{
		cli:             cli,
		containerMapper: containerMapper,
	}
	return &containerService
}

func (c *ContainerService) GetContainerList() (result string, err error) {
	ctx := context.Background()
	containers, err := c.cli.ContainerList(ctx, types.ContainerListOptions{All: true})
	if err != nil {
		fmt.Println("GetContainerList", err)
		result = "获取容器列表失败"
		return
	}
	for _, container := range containers {
		var container_id string
		var name string
		var state string
		var image string
		var port string
		var command string
		result := c.containerMapper.SelectContainerByImgId(container.ID) // 根据容器ID查找是否数据已有数据
		if !result {
			container_id = container.ID
			name = strings.Join(container.Names, "")[1:]
			state = container.State
			image = container.Image
			portsStr, _ := json.Marshal(container.Ports)
			port = string(portsStr)
			command = container.Command
			tb := NewContainerItem(container_id, name, state, image, port, command)
			c.containerMapper.Insert(tb)
		}
	}
	result = "获取镜像列表成功"
	return result, err
}
