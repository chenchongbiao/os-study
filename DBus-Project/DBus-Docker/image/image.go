package image

import (
	"bytes"
	"context"
	"encoding/base64"
	"encoding/json"
	"fmt"
	"log"

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

var (
// cli, err = client.NewClientWithOpts(client.WithAPIVersionNegotiation(), client.WithHost("tcp://localhost:2375"))
)

type Image struct {
	service *dbusutil.Service
	cli     *client.Client
	ctx     context.Context
}

func (image *Image) GetInterfaceName() string {
	return dbusServiceName
}

func NewImage(service *dbusutil.Service, cli *client.Client, ctx context.Context) *Image {
	image := Image{
		service: service,
		cli:     cli,
		ctx:     ctx,
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

func (image *Image) Pull(img, user, password string) (result string, busErr *dbus.Error) {
	authConfig := types.AuthConfig{
		Username: user,
		Password: password,
	}
	encodedJson, _ := json.Marshal(authConfig)
	authStr := base64.URLEncoding.EncodeToString(encodedJson)
	reader, err := image.cli.ImagePull(image.ctx, img, types.ImagePullOptions{RegistryAuth: authStr})
	reader.Close()
	if err != nil {
		log.Fatal("镜像拉取失败 ", err.Error())
	}
	buf := new(bytes.Buffer)
	_, _ = buf.ReadFrom(reader)
	result = buf.String()
	// result = "1111"
	return result, nil
}
