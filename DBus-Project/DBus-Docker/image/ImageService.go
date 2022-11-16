package image

import (
	"context"
	"encoding/base64"
	"encoding/json"
	"fmt"
	"io"
	"log"
	"os"

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
	dbusPath        = "/com/bluesky/docker/Image"
	dbusServiceName = "com.bluesky.docker.Image"
	dbusInterface   = dbusServiceName
)

type Image struct {
	service *dbusutil.Service
	cli     *client.Client
}

func (image *Image) GetInterfaceName() string {
	return dbusServiceName
}

func NewImage(service *dbusutil.Service, cli *client.Client) *Image {
	image := Image{
		service: service,
		cli:     cli,
	}
	err := service.Export(dbusPath, &image)
	if err != nil {
		fmt.Println(err)
	}

	err = service.RequestName(dbusServiceName)
	if err != nil {
		fmt.Println(err)
	}
	return &image
}
func (image *Image) PullImage(img string) (busErr *dbus.Error) {
	ctx := context.Background()
	out, err := image.cli.ImagePull(ctx, img, types.ImagePullOptions{})
	if err != nil {
		log.Fatal("镜像拉取失败 ", err)
		return nil
	}
	io.Copy(os.Stdout, out)
	fmt.Println("镜像拉取成功")
	return nil
}

func (image *Image) PullPrivateImage(img, user, password string) (busErr *dbus.Error) {
	ctx := context.Background()
	authConfig := types.AuthConfig{
		Username: user,
		Password: password,
	}
	encodedJson, _ := json.Marshal(authConfig)
	authStr := base64.URLEncoding.EncodeToString(encodedJson)
	out, err := image.cli.ImagePull(ctx, img, types.ImagePullOptions{RegistryAuth: authStr})
	out.Close()
	if err != nil {
		log.Fatal("私有镜像拉取失败 ", err)
		return nil
	}
	io.Copy(os.Stdout, out)
	// result = "镜像拉取成功"
	fmt.Println("私有镜像拉取成功")
	return nil
}

func (image *Image) GetImageList() (result string, busErr *dbus.Error) {
	ctx := context.Background()
	images, err := image.cli.ImageList(ctx, types.ImageListOptions{All: true})
	if err != nil {
		log.Fatal("镜像列表获取失败", err)
	}

	list, _ := json.Marshal(images)
	result = string(list)
	fmt.Println(result)
	return result, nil
}