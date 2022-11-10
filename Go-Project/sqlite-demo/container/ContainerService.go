package container

import (
	"context"
	"database/sql"
	"fmt"

	"github.com/docker/docker/api/types"
	"golang.org/x/vuln/client"
)

type ContainerService struct {
	cli             *client.Client
	containerMapper *ContainerMapper
}

func InitService(cli *client.Client, db *sql.DB) *ContainerMapper {
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
	for _, image := range containers {
		// var img_id string
		// var tags string
		// var size string
		// var create_time string
		// result := i.imgMapper.SelectImageByImgId(image.ID[7:]) // 根据镜像ID查找是否数据已有数据
		// if !result {
		// 	img_id = image.ID[7:]
		// 	tags = arrayToString(image.RepoTags)
		// 	size = formatImageSize(image.Size)
		// 	create_time = fotmatDate(image.Created)
		// 	tb := NewImageItem(img_id, tags, size, create_time)
		// 	i.imgMapper.Insert(tb)
		// }
	}
	result = "获取镜像列表成功"
	return result, err
}
