package image

import (
	"context"
	"database/sql"
	"encoding/base64"
	"encoding/json"
	"fmt"
	"io"
	"os"
	"time"

	"github.com/docker/docker/api/types"
	"github.com/docker/docker/client"
)

const (
	B  = 1
	KB = 1000
	MB = 1000 * 1000
	GB = 1000 * 1000 * 1000
	TB = 1000 * 1000 * 1000 * 1000
	EB = 1000 * 1000 * 1000 * 1000 * 1000
)

type ImageService struct {
	cli       *client.Client
	imgMapper *ImageMapper
}

func InitService(cli *client.Client, db *sql.DB) *ImageService {
	imgMapper, _ := InitDB(db)
	imgService := ImageService{
		cli:       cli,
		imgMapper: imgMapper,
	}
	return &imgService
}

func (i *ImageService) PullImage(img string) (result string, err error) {
	ctx := context.Background()
	out, err := i.cli.ImagePull(ctx, img, types.ImagePullOptions{})
	i.GetImageList() // 更新镜像列表
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
		var img_id string
		var tags string
		var size string
		var create_time string
		result := i.imgMapper.SelectImageByImgId(image.ID[7:]) // 根据镜像ID查找是否数据已有数据
		if !result {
			img_id = image.ID[7:]
			tags = arrayToString(image.RepoTags)
			size = formatImageSize(image.Size)
			create_time = fotmatDate(image.Created)
			tb := NewImageItem(img_id, tags, size, create_time)
			i.imgMapper.Insert(tb)
		}
		// break
	}
	result = "获取镜像列表成功"
	return result, err
}

func (i *ImageService) GetContainersList() {
	containers, err := i.cli.ContainerList(context.Background(), types.ContainerListOptions{All: true})
	if err != nil {
		panic(err)
	}

	for _, container := range containers {
		fmt.Printf("%s %s\n", container.ID[:10], container.Image)
	}

	cbytes, _ := json.Marshal(containers)
	fmt.Println(string(cbytes))
}

func formatImageSize(dockerSize int64) (size string) {
	if dockerSize < KB {
		return fmt.Sprintf("%.2fB", float64(dockerSize)/float64(B))
	} else if dockerSize < (MB) {
		return fmt.Sprintf("%.2fKB", float64(dockerSize)/float64(KB))
	} else if dockerSize < (GB) {
		return fmt.Sprintf("%.2fMB", float64(dockerSize)/float64(MB))
	} else if dockerSize < (TB) {
		return fmt.Sprintf("%.2fGB", float64(dockerSize)/float64(GB))
	} else if dockerSize < (EB) {
		return fmt.Sprintf("%.2fTB", float64(dockerSize)/float64(TB))
	} else {
		return fmt.Sprintf("%.2fEB", float64(dockerSize)/float64(EB))
	}
}

func fotmatDate(timeStamp int64) (date string) {
	const baseFormat = "2006-01-02"
	t := time.Unix(timeStamp, 0)
	return t.Format(baseFormat)
}

func arrayToString(arr []string) string {
	var result string
	for _, i := range arr { //遍历数组将元素追加成字符串
		result += i + " "
	}
	return result
}
