package image

import (
	"context"
	"encoding/base64"
	"encoding/json"
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

func (i *ImageService) PullPrivateImage(img, user, password string) (result string, err error) {
	ctx := context.Background()
	authConfig := types.AuthConfig{
		Username: user,
		Password: password,
	}
	encodedJson, _ := json.Marshal(authConfig)
	authStr := base64.URLEncoding.EncodeToString(encodedJson)
	out, err := i.cli.ImagePull(ctx, img, types.ImagePullOptions{RegistryAuth: authStr})
	out.Close()
	if err != nil {
		result = "镜像拉取失败\n" + err.Error()
		fmt.Println(result, err)
	}
	io.Copy(os.Stdout, out)
	result = "镜像拉取成功"
	return result, err
}

func (i *ImageService) GetImageList() (result string, err error) {
	ctx := context.Background()
	images, err := i.cli.ImageList(ctx, types.ImageListOptions{All: true})
	if err != nil {
		fmt.Println(err)
		result = "获取镜像列表失败"
		return
	}
	for _, image := range images {
		// fmt.Println(image)
		fmt.Println("ID", image.ID[7:19])
		fmt.Println("Tags", image.RepoTags)
		fmt.Println("Sizev", image.Size)         // 字节转换
		fmt.Println("CreateTime", image.Created) // 时间戳
		break
	}
	result = "获取镜像列表成功"
	return result, err
}
