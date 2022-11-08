package image

import (
	"context"
	"fmt"
	"io"
	"os"

	"github.com/docker/docker/api/types"
	"github.com/docker/docker/client"
)

type ImageService struct {
	cli *client.Client
}

func InitService(cli *client.Client) *ImageService {
	imgService := ImageService{
		cli: cli,
	}
	return &imgService
}
func (i *ImageService) PullImage(img string) (result string, err error) {
	ctx := context.Background()
	out, err := i.cli.ImagePull(ctx, img, types.ImagePullOptions{})
	if err != nil {
		result = "镜像拉取失败\n" + err.Error()
		fmt.Println(result, err)
		return result, err
	}
	io.Copy(os.Stdout, out)
	result = "镜像拉取成功"
	return result, err
}
